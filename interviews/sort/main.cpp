// I will need a hashmaps 
#include<map>
// io library
#include<iostream>
// heap realated algorithms
#include<algorithm>
// reading the file stream
#include<fstream>
// vector for storage of results
#include<vector>

// deifnition of sort number
#define SORT_VAL 20

// comperison of stored string representations
struct Comp
{
    bool operator()(const std::pair<std::string,int> &s1, const std::pair<std::string,int> &s2)
    {
        // here wea re dealing with the same number of reps of different strings
        // we will always return the first in lexical order
    //    if(s1.second==s2.second){
  //          return s1.first < s2.first;
//        }
        return s1.second > s2.second;
    }
};

int main(int argc, char * argv[]){
    // lets get the std classes into a function without polluting ::
    using namespace std;    
    
    // do we have 2 params?

    if(argc < 2){
        cout << "No file for scaning\n";
    }
    
    // the 0 param is program name the 1st is the filename
    // potentaially getopt logic could be added here.
    ifstream in(argv[1] ,ifstream::in);

    //density of strings hashmap to have constant insert time
    map<string, int> dens;
    while(in.good()){
        string temp;
        in >> temp;
        //remove all none alphanumeric chars
        temp.erase(std::remove_if(temp.begin(), temp.end(),
            [](char c) { return !( std::isalnum(c)); } ),
                temp.end());
        // cout << temp << endl;
        // if the string have been seen increase number of occurances
        if(dens.find(temp) != dens.end()){
            dens[temp]++;
        }
        // if not lets insert the key
        else{
            dens.insert(pair<string, int>(temp, 1));
        }
    }

    int inserted = 0;
    int cur_min = 0;
    // preparing of storage for result
    vector<pair<string, int> > v;
    v.clear();
    // for every value in the map stored we want to store it in the results
    // if it is not bigger than a smallest element there is no point of adding it
    for(map<string,int>::const_iterator i = dens.begin(); i != dens.end(); i++){
        // lets make sure the string is not empty
        if(i->first == "") continue;
        // not yet added SORT_VAL number of entries lets just keep on pushing
        if(inserted < SORT_VAL){
            v.push_back(*i);
            make_heap(v.begin(), v.end(), Comp());
        }
        else if(i->second > v.front().second){
            // we found new value bigger than minimum lets add it
            pop_heap (v.begin(),v.end(), Comp());
            v.pop_back();
            v.push_back(*i);
            push_heap (v.begin(),v.end(), Comp());
        }
        /**
        //debuging info of heap being pushed by min values;
        for(vector<pair<string, int> >::iterator i = v.begin(); i != v.end(); i++){
            cout << i->first << " " << i->second << " ";
        }
        cout << endl;
        **/
        inserted++;
    }
    // lets sort the results now
    sort_heap (v.begin(),v.end(), Comp());

    //results are sorted lets print them out
    for(vector<pair<string, int> >::iterator i = v.begin(); i != v.end(); i++){
        cout << "\t"<< i->second << " " << i->first << endl;
    }

}
