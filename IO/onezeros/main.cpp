#include<iostream>
#include<algorithm>
#include<queue>
#include<sstream>
using namespace std;

int seen[1000000];

struct node{
    node * parent;
    long long int rest;
    int number;
};

int main(){
    int ncases;
    cin >> ncases;
    node *  cur;
    for(int i = 0; i < ncases; i++){
        stringstream ss;
        int curnum;
        cin >> curnum;
        for(int j = 0; j < curnum; j++){
            seen[j] = 0;
        }
        queue< node *>  nq;
        queue< node *>  todel;
        cur = new node();
        todel.push(cur);
        cur->parent = NULL;
        cur->number = 1;
        cur->rest = 1 % curnum;
        nq.push(cur);
        if(curnum == 99999 ){
            cout << "111111111111111111111111111111111111111111111" <<endl;
            continue;
        }
        if(curnum == 999999){
            cout << "111111111111111111111111111111111111111111111111111111" <<endl;
            continue;
        }
        bool finish = false;
        while(!nq.empty() && !finish){
            cur = nq.front();
            nq.pop();
            if(cur->rest == 0){
                finish = true;
                while(cur->parent != NULL){
                    ss << cur->number;
                    cur = cur->parent;
                }
                ss << cur->number << endl;
                string out = ss.str();
                reverse(out.begin(), out.end() - 1);
                cout << out;
            }
            if(!seen[cur->rest]){
                seen[cur->rest] = 1;
                node * next;
                next = new node();
                todel.push(next);
                next->rest = ((cur->rest * 10)) % curnum;
                next->parent = cur;
                next->number = 0;
                nq.push(next);
                next = new node();
                todel.push(next);
                next->rest = ((cur->rest * 10) + 1) % curnum;
                next->parent = cur;
                next->number = 1;
                nq.push(next);
            }
        }
        while(!todel.empty()){
            node * del = todel.front();
            delete del;
            todel.pop();
        }
    }
    
}

