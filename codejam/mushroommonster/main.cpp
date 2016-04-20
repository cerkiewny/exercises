#include <iostream>

using namespace std;

int intervals[10000];

int main(){
  int T;

  cin >> T;

  for(int i = 0 ; i < T; i++){
    unsigned long ret1 = 0, ret2 = 0;
    int n;
    int pace = 0;
    cin >> n;

    for(int j = 0; j < n; j++){
      cin >> intervals[j];
    }
    for(int k = 0; k < n - 1; k++){
      if(intervals[k + 1] < intervals[k]){
        ret1 += intervals[k] - intervals[k + 1];
        if (intervals[k] - intervals[k + 1] > pace){
          pace = intervals[k] - intervals[k + 1];
        }
      }
    }
    for(int j = 0; j < n - 1; j++){
      ret2 += min(pace, intervals[j]);
    }
    cout << "Case #" << i + 1 << ": " << ret1 << " " << ret2 << endl;
  }
}
