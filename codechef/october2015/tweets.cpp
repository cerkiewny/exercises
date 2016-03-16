#include<iostream>

using namespace std;

bool open[1001] = {};

int main(){
  int n;
  int k;
  int curo = 0;
  cin >> k >> n;
  for(int i = 0; i < n; i ++){
    string tmp;
    cin >> tmp;
    if(tmp == "CLOSEALL"){
      for ( int j = 1; j < k + 1; j++){
        open[j] = false;
      }
      curo = 0;
    } else {
      int num;
      cin >> num;
      open[num] = !open[num];
      if(open[num]){
        curo ++;
      } else {
        curo --;
      }

    }
    cout << curo << endl;
  }
}
