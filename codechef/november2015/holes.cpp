#include <iostream>
#include <string>


using namespace std;

int main(){
  int ncases;
  cin >> ncases;
  for ( int i = 0; i < ncases; i ++){
    int res = 0 ; 
    std::string text;
    cin >> text;
    for ( std::string::iterator a = text.begin(); a != text.end(); ++a){
      if ((*a) == 'Q'){
        res++;
      } else if ( (*a) == 'R'){
        res++;
      } else if ( (*a) == 'P'){
        res++;
      } else if ( (*a) == 'A'){
        res++;
      } else if ( (*a) == 'D'){
        res++;
      } else if ( (*a) == 'O'){
        res++;
      } else if ( (*a) == 'B'){
        res += 2;
      }
    }
    cout << res << endl;
  }
}
