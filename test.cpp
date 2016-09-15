#include <iostream>

int main(){
  int n;
  std::cin>> n;
  int ret = 0;
  
  int cur = 1;
  int prev = 0;
  for(int i = 0 ; i < n; i ++){
 
    int tmp = cur + prev;

    prev = cur;
    cur = tmp;
    ret += cur;

  }
  std::cout << cur << std::endl;
}

