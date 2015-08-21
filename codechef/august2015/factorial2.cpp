#include <iostream>
#include <algorithm>

int nums[200];
int nextnums[200];

using namespace std;

int main(){
  int n;

  cin >> n;
  for( int i = 0; i < n; i++){
    int cur;
    cin >> cur;
    for( int j = 0; j < 200; j++){
      nums [j] = 0;
      nextnums [j] = 0;
    }
    nums[0] = 1;
    for( int j = 1; j <= cur; j++){
      for( int k = 0; k < 197; k++){
        nextnums[k] += (nums[k] * j) % 10; 
        if(nextnums[k] >= 10){
          nextnums[k] -= 10;
          nextnums[k + 1] ++;
        }
        nextnums[k+1] += ((nums[k] * j) / 10) % 10;
        if(nextnums[k + 1] >= 10){
          nextnums[k + 1] -= 10;
          nextnums[k + 2] ++;
        }
        nextnums[k+2] += ((nums[k] * j) / 100) % 10;
        if(nextnums[k + 2] >= 10){
          nextnums[k + 2] -= 10;
          nextnums[k + 3] ++;
        }

      }
      for( int k = 0; k < 200; k++){
        nums [k] = nextnums[k];
        nextnums [k] = 0;
      }
    }
    bool print = false;
    for( int j = 199; j >= 0 ; j--){
      if (nums[j] != 0){
        print = true;
      }
      if (print){
        cout << nums[j];
      }
    }
    cout << endl;
  }
}
