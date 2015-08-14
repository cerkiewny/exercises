#include<iostream>

using namespace std;

int main(){

  int n;

  cin >> n;
  int score[27];
  for(int i = 0; i < n; i++){
    cin >> score[i]; 
  }
  int max = score[0];
  for(int i = 0; i < n; i++){
    if (score[i] > max){
      max = score[i];
    }
  }
  for(int i = 0; i < n; i++){
    if ( max == score[i]){
      cout << char('A' + i);
    }
  }
  cout << endl;
  
}
