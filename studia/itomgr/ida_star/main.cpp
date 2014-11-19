#include<fstream>
#include<iostream>
#include<set>
#include<map>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

stack<int> rp; 
vector<int> costs(100);
map<pair<int,int> ,int> paths;
set<int> exits;
inline int h(int i){
    return costs[i];
}

bool is_goal(int i){
    if(exits.find(i) != exits.end()){
        return true;
    }
    return false;
}


int cost(int a, int b){
    if(a > b){
        swap(a,b);
    }
    pair<int, int> temp;
    temp.first = a;
    temp.second = b;
    if(paths.find(temp) != paths.end()){
        return paths[temp];
    }
    return 100000;

}
int idasearch(int node, int g, int bound){
    int f;
    cout << node << endl;
    f = g + h(node);
    if ( f > bound){
        return f;
    }
    if(is_goal(node)){
        rp.push(node);
        return 0;
    }
    int min = 100000;
    for( auto i = paths.begin(); i != paths.end(); i++){

        int t = 100000;
        if( i->first.first == node){
            t = idasearch(i->first.second, g + i->second, bound);
        }
//        if( i->first.second == node){
//            t = idasearch(i->first.first, g + i->second, bound);
//        }
        if( t == 0){
            rp.push(node);
            return 0;
        }
        if(t < min){
            min = t;
        }
    }
    return min;
}


void ida_star(){
    int bound;
    bound = h(0);
    while(1){
       int t;
       t = idasearch(0, 0, bound);
       if ( t == 0){
        return;
       }
       if (t > 10000){
           return;
       }
       bound = t;
    }
}


int main(){
    int nnodes, nexit;
    ifstream in("in");
    in >> nnodes;

    for(int i = 0; i < nnodes; i++){
        int cost;
        in >> cost;
        costs[i] = cost;
    }
    in >> nexit;
    for(int i = nexit; i > 0; i--){
        int exit;
        in >> exit;
        exits.insert(exit);
    }
    int npaths;
    in >> npaths;
    for(int i = npaths; i > 0; i--){
        int a, b, cost;

        in >> a >> b >> cost;

//      if(a > b){
//          swap(a,b);
//      }
        pair<int, int> temp;
        temp.first = a;
        temp.second = b;
        paths[temp] = cost;
    }
    ida_star();
    cout << "PATH:" << endl;
    while(!rp.empty()){
        cout << rp.top() << endl;
        rp.pop();
    }
    
}
