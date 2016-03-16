#include <cmath>
#include <iostream>
#include <utility>

using namespace std;

int main(){
  int ncases;

  cin >> ncases;

  for(int i = 0; i < ncases; i++){
    int nnums;
    cin >> nnums;
    int min = 1000001;
    int smin = 1000001;
    for(int j = 0; j < nnums; j++){
      int tmp;
      cin >> tmp;
      if (tmp < min){
        smin = min;
        min = tmp;;
      } else if ( tmp < smin ){
        smin = tmp;
      }
    }
    cout << smin + min << endl;
  }
}
