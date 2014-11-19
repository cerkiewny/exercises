#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct node{
    double weight;
    int acc;
    int ornum;
};

bool cmp(const node &a, const node &b){

    if(a.weight == b.weight){
        return a.ornum < b.ornum;
    }
    else
        return a.weight < b.weight;
}

int main(){
    int nnumbs;

    cin >> nnumbs;
    vector<node> res;
    for (int i=0; i < nnumbs; i++) {
        int a, b;
        cin >> a;
        cin >> b;
        node tmp;
        tmp.weight = (double) a / (2 << b );
        tmp.acc = b;
        tmp.ornum = a;
        res.push_back(tmp);
    }
    sort(res.begin(), res.end(), cmp);
    for (vector<node>::iterator i = res.begin(); i < res.end(); i++) {
        cout << i->ornum << " " << i->acc << endl;
    }
}
