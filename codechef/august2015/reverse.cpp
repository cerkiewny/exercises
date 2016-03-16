#include <iostream>

using namespace std;

int main(){
  int ncases;
  cin >> ncases;
  for( int i = 0; i < ncases; i++){
    string tmp;
    cin >> tmp;
    bool first = true;
    for(string::reverse_iterator a = tmp.rbegin(); a != tmp.rend(); a++){
      if(first && *a != '0'){
        cout << *a;
        first = false;
        
      } else if (!first){
        cout << *a;
      }
    }
    cout << endl;
    
  }
}
