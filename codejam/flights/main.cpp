#include<fstream>
#include<cstring>
#include<list>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;

struct route{
   int from;
   int to;
};

bool available[50];

int cities[50];

void update_available(int last, list<route> &routes){
    available[last] = false;
    list<route>::const_iterator iterator;
    for (iterator = routes.begin(); iterator != routes.end(); ++iterator) {
            if(iterator->from == last){
                available[iterator->to] = true;
            }
    }

}

int smallest(int num){
    int minim = 1000000000;
    int ret = 0;
    for(int i = 0; i < num; i ++){
        if(minim > cities[num]){
            minim = cities[num];
            ret = num;
        }
    }
    return ret;
}

int smallest_available(int num){
    int minim = 1000000000;
    int ret = 0;
    for(int i = 0; i < num; i ++){
        if(available[i] == true && minim > cities[num]){
            minim = cities[num];
            ret = num;
        }
    }
    return ret;
}

int main(int argc, char**argv)
{
 ifstream in;
 ofstream out;
 long a,b;
 in.open("in");
 out.open("out");
 int ncases;
 in >> ncases;
 bool end = false;
 int ret;
 for(int i = 0; i < ncases; i++){
    cout << "Case #" << i + 1<< ": ";
    ret = 0;
    in >> a;
    in >> b;
    memset(available, 0, sizeof(available));
    list<route> routes = list<route>();
    for(int j = 0; j < a; j++){
        in >> cities[j];
    }
    for(int j = 0; j < b; j++){
        route a;
        in >> a.from;
        in >> a.to;
        routes.push_back(a);
    }
    cout << cities[smallest(a)];
    update_available(smallest(a), routes); 
    for(int j = 0; j < a - 1; j++){
        cout << cities[smallest_available(a)];
        update_available(smallest_available(a), routes); 
    }
    cout<< endl;
    

 }
}


