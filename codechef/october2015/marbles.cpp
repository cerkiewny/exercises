#include <iostream>

using namespace std;

bool used[1000];

long long unsigned int newton( int a, int b){
  
}


int main(){
  int ncases;

  cin >> ncases;
  for(int i = 0; i < ncases; i++){
    for(int j = 0; j < 1000; j++){
      used[j] = false;
    }
    int a, b;
    cin >> a >> b;

    cout << newton(a, b);
  }
}
