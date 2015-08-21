#include <iostream>

using namespace std;

int main(){
  int ncases;
  cin >> ncases;
  for(int i = 0; i < ncases; i ++){
    unsigned long long int tmp;
    cin >> tmp;
    cout << (tmp / 2)  + 1<< endl;
  }
}
