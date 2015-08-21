#include <iostream>
#include <algorithm>

using namespace std;

int main(){
  int n;
  cin >> n;
  for( int i = 0 ; i < n ; i ++){
    int cur;
    cin >> cur;
    int twos = 0;
    int fives = 0;
    int tmp = 2;
    while(tmp <= cur){
      twos += cur / tmp;
      tmp *= 2;
    }
    tmp = 5;
    while(tmp <= cur){
      fives += cur / tmp;
      tmp *= 5;
    }
    cout << min (fives, twos) << endl; 

  }
}
