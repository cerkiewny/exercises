#include<iostream>

using namespace std;

int main(){
  int ncases;
  cin >> ncases;
  for(int i = 0 ; i< ncases;i ++){
    int curn;
    cin >> curn;

    int res = 0;
    res = curn / 2048;
    curn %= 2048;
    while(curn > 0){
      if (curn % 2 == 1){
        res++;
      }
      curn /= 2;

    }
    cout << res << endl;
  }
}
