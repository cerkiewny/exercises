#include <iostream>

using namespace std;
int main(){
  int n, k;

  cin >> n >> k;
  int res = 0;
  int tmp;
  for(int i = 0; i < n; i++){
    cin >> tmp;
    if (tmp % k ==0){
      res ++;
    }
  }
  cout << res << endl;
}
