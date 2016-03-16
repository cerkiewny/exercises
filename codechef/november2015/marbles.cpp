#include <iostream>

using namespace std;


int main(){
  int ncases;
  cin >> ncases;
  for(int i = 0; i < ncases; i++){
    int n, k;
    cin >> n >> k;
    unsigned long long res;
    res = 1;
    for(int i = 1; i < k; i ++){
      res *= (n-k+i);
      res /= i;
    }
    cout << res << endl;
  }
}
