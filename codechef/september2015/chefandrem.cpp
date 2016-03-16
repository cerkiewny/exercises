#include <iostream>
using namespace std;
int main(){
  int ncases;
  cin >> ncases;
  for(int i = 0; i < ncases; i ++){
    int a, b;
    cin >> a >> b;
    int max = a > b ? a : b;
    cout << max << " " << a + b << endl;
  }
}
