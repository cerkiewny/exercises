#include <iostream>
#include <cmath>


using namespace std;

bool primes[1000000];

int main(){
  int ncases;

  cin >> ncases;

  for (int k = 0; k < ncases; k++){
    long long int n, m;
    cin >> n >> m;
    for (int j = 0; j < m - n + 1; j++){
      primes[j] = true;
    }

    for(int i = 2 ; i <= sqrt(m);i++){
      long long int cur = n - n % i;
      while(cur <= m){
        if (cur >= n && cur != i){
          primes[cur - n] = false;
        }
        cur += i;
      }
      
    }
    for (int j = 0; j < m - n + 1; j++){

      if (primes[j] == true && n + j > 1){
        cout << n + j<< endl;
      }
    }
  }
}
