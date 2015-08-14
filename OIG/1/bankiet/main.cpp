#include<iostream>

using namespace std;

int neighbours[30001];
bool seen[30001];

int main(){
  int res = 0;
  int ncs;

  cin >> ncs;
  
  for(int i = 1; i < ncs + 1; i ++){
    int tmp;
    cin >> tmp;
    neighbours[i] = tmp;
    seen[i] = false;
  }
  for(int i = 1; i < ncs + 1; i ++){
    if(!seen[i]){
      int next;
      seen[i] = true;
      next = neighbours[i]; 
      while(!seen[next]){
        seen[next] = true;
        next = neighbours[next]; 
      }
      res++;
    }
  }
  cout << res << endl;
}
