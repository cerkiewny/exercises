#include<iostream>
#include<vector>

using namespace std;

int eucl(int a, int b){

  while(a > 0){
    if (b >= a){
      b = b - a;
    } else {
      swap(a,b);
    }
  }
  return b;
}


int main(){
  int ncases;

  cin >> ncases;
  for(int i =0; i < ncases; i++){
    int n;
    
    cin >> n;
    vector<int> vals;
    int res;
    for(int j = 0; j < n; j++){
      int tmp;
      cin >> tmp;
      vals.push_back(tmp);
    }
    res = vals[0];
    for(int j = 0; j < n; j++){
      res = eucl(vals[j], res);
    }
    for(int j = 0; j < n; j++){
      cout << vals[j] / res << " " ;
    }
    cout << endl;
  }
}
