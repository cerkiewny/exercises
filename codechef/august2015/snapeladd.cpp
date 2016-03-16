#include<iostream>
#include<cmath>

using namespace std;

int main(){
  int ncases;
  cin >> ncases;

  for ( int i = 0 ; i < ncases; i ++){
    int a, b ;
    cin >> a;
    cin >> b;

    double res;
    res = sqrt(abs(a*a - b*b)); 
    cout << res << " ";
    res = sqrt(a*a + b*b);
    cout << res << endl;
  }
}
