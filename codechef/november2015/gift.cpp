#include <iostream>
#include <algorithm>



int main(){

  int ncases;
  std::cin >> ncases;
  for (int i = 0; i < ncases; i++){
    int k;
    std::cin >> k;

    int cur;
    std::cin >> cur;
    int max = cur;
    int min = cur;
    for(int j = 0; j < k - 1; j++){
      std::cin >> cur;
      int nmax = max + cur;
      nmax = std::max(nmax, min + cur);
      nmax = std::max(nmax, min - cur);
      nmax = std::max(nmax, min * cur);
      nmax = std::max(nmax, max - cur);
      nmax = std::max(nmax, max * cur);
      int nmin = min + cur;
      nmin = std::min(nmin, min - cur);
      nmin = std::min(nmin, min * cur);
      nmin = std::min(nmin, max + cur);
      nmin = std::min(nmin, max - cur);
      nmin = std::min(nmin, max * cur);
      min = nmin;
      max = nmax;
    }
    std::cout << min << std::endl;
  }
}
