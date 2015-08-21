#include <iostream>

using namespace std;

int nums[100000];
int rev[100000];

int main(){
    int nnums;
    cin >> nnums;
    while (nnums != 0){
      bool ambig = true;
      bool seen[100000];
      for(int j = 0; j < nnums; j ++){
        int tmp;
        cin >> tmp;
        nums[j] = tmp - 1;
        rev[nums[j]] = j;

      }
      for (int j = 0; j < nnums; j++){
        if (nums [j] != rev[j]){
          ambig = false;
          break;
        }
      }
      if (ambig){
        cout << "ambiguous" << endl;
      } else {
        cout << "not ambiguous" << endl;
      }
      cin >> nnums;
      
    }
  
}
