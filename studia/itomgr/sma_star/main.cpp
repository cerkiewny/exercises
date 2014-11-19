#include<fstream>
#include<iostream>
#include<set>

using namespace std;


int main(){
    int nnodes, nexit;
    ifstream in("in");
    set<int> exits;
    in >> nnodes;

    for(int i = nnodes; i > 0; i--){
        int cost;
        in >> cost;
        cout << cost << endl;
    }
    in >> nexit;
    for(int i = nexit; i > 0; i--){
        int exit;
        in >> exit;
        exits.insert(exit);
    }
    int fun;
    cin >> fun;
    if(exits.find(fun) == exits.end()){
    }


    
}
