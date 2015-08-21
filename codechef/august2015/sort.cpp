#include<iostream>
#include<algorithm>

using namespace std;

int nums[1000001];
int main(){
  int n;

  cin >> n;
  int maxim = 0;
  for(int i = 0; i < n; i++){
    int tmp;
    cin >> tmp;
    nums[tmp] ++;
  }

  for(int i= 0; i <= 1000000; i++){
    while(nums[i] > 0){
      cout << i << endl;
      nums[i]--;
    }
  }

}
