#include <iostream>

using namespace std;

int main(){
  int ncases;
  cin >> ncases;
  for(int i=0; i < ncases; i++){
    int a, b;
    cin >> a >> b;

    cout << a % b << endl;
  }
}
