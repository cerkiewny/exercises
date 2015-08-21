#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
  double q;
  double s;
  cin >> q;
  cin >> s;

  cout << setprecision(2) << fixed;
  if( fmod(q, 5.0) == 0.0){
    if(q + 0.5 <= s){
      cout << s - q - 0.5 << endl;
    }
    else
      cout << s << endl;
  }
  else
    cout << s << endl;
}
