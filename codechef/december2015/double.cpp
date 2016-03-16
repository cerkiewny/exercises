#include<iostream>

using namespace std;

int main(){
  int ncases;

  cin >> ncases;
  for(int i = 0; i < ncases; i++){
    int cur;
    cin >> cur;
    cout << cur - (cur % 2) << endl;
  }
}
