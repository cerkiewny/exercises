#include<iostream>

using namespace std;

int main(){
  int ncases;
  cin >> ncases;

  for(int i = 0;i < ncases; i++){
    int num;
    int res = 0;
    cin >> num;
    while(num > 0){
      res += num % 10;
      num /= 10;
    } 
    cout << res << endl;
  }
}
