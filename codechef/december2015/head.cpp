#include <iostream>


using namespace std;

int main(){
  int ncases;
  cin >> ncases;

  for(int i = 0 ; i < ncases; i++){
    string line;
    int nr;
    cin >> nr;
    cin >> line;
    int res = 0;
    for(int j = 0 ; j < line.size(); j++){
      if(line[j] == 'Y'){
        res = 1;
        break;
      }
      if(line[j] == 'I'){
        res = 2;
        break;
      }
    }
    if (res == 0){
      cout << "NOT SURE" << endl;
    }
    if (res == 1){
      cout << "NOT INDIAN" << endl;
    }
    if (res == 2){
      cout << "INDIAN" << endl;
    }
  }
}
