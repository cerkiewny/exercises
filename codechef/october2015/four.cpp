#include <iostream>

using namespace std;

int main(){
  int ncases;

  cin >> ncases;
  cin >> noskipws;
  char tmp;
  cin >> tmp;
  for(int i = 0; i < ncases; i++){
    tmp = 'a';
    int res = 0;
    while(tmp != '\n'){
      if(tmp == '4')
        res ++;
      cin >> tmp;
    }
    cout << res <<endl;
  }
}
