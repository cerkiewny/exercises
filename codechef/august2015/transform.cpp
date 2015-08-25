#include<vector>
#include<iostream>

using namespace std;
int main(){
  int ncases;
  cin >> ncases;

  for (int i =0 ; i  < ncases; i++){
    string curs;
    cin >> curs;
    vector<char> ops;
    for(int i = 0; i < curs.size(); i++){
      char cur = curs[i];
      if(cur == '('){
        ops.push_back(cur);
      } else if (cur == ')'){
        while(ops.back() != '(' && ops.size() > 0){
          cout << ops.back();
          ops.pop_back();
        }
        ops.pop_back();
      } else if ( cur >= 'a' && cur <= 'z'){
        cout << cur;
        if(ops.back() != '('){
          cout << ops.back();
          ops.pop_back();
        }
      } else {
        ops.push_back(cur);
      }
    }
    cout << endl;
  }
  
}
