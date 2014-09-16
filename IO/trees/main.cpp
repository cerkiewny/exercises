#include<iostream>
#include<stack>
#include<string>
#include<sstream>

using namespace std;

int nums[2501];

int maxi = 1;

struct node{
    int num;
    int parent;
    int lv;
    bool going_right;
};

int main(){

    int num = 0;

    cin >> num;
    stringstream output1;
    stringstream output2;

    for(int i = 0; i < num; i++){
        cin >> nums[i];
        if(nums[i] > 2501){
            cout << "NIE" << endl;
            return 0;
        }
    }

    stack<node> sn;


    node cur;
    cur.num = 1;
    cur.lv = 0;
    cur.parent = 0;
    cur.going_right = false;

    output2 << "0 ";
    output1 << "(";
    sn.push(cur);
    if(num == 1 && nums[0] == 0){
        output1 <<  ")";
        cout << output2.str() << "\n" << output1.str() << endl;
        return 0;
    }
    for(int i = 0; i < num; i++){
        cur = sn.top();
        if(nums[i] <= cur.lv){
            cout << "NIE" << endl;
            return 0;
        }
        while(cur.lv != nums[i]){
            cur.lv = cur.lv + 1;
            maxi++;
            cur.parent = cur.num;
            cur.num = maxi;
            cur.going_right = false;
            output2 << cur.parent << " ";
            output1 <<  "(";
            sn.push(cur);
        }
        sn.pop();
        output1 <<  ")";
        while(sn.top().going_right == true){
            sn.pop();
            output1 <<  ")";
            if(sn.empty() && i != (num - 1)){
                cout << "NIE" << endl;
                return 0;
            }
            else if (sn.empty()){
                cout << output2.str() << "\n" << output1.str() << endl;
                return 0;
            }
        }
        sn.top().going_right = true;
    }
    if(sn.size() == 1 && sn.top().going_right == false){
        output2 <<  ")";
        cout << output2.str() << "\n" << output1.str() << endl;
    }
    else{
        cout << "NIE" << endl;
        return 0;
    }
}
