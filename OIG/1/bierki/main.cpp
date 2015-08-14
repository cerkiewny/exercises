#include<iostream>
#include<algorithm>

using namespace std;


int counts[500] = {0};

bool checktri(int min, int secmin, int max, int secmax){
  if ( min + secmin > secmax && max - secmax < min){
    return true;
  }
  return false;
}

int findsum(int sum, int max, int min, int *cts){
  int secmin, secmax;
  while ( cts[min] == 0 ){
    min ++;
  }
  while ( cts[max] == 0 ){
    max --;
  }

  if(max == min){
    return 0;
  }
  if( cts[max] > 1){
    secmax = max - 1;
    while ( cts[secmax] == 0 ){
      secmax--;
    }
  }
  if( cts[max] > 1){
    secmax = max - 1;
    while ( cts[secmax] == 0 ){
      secmax--;
    }
  }

  bool able = checktri(min, secmin, max, secmax);

}

int main(){
  int n;

  for (int i = 0; i < n; i++){
    int tmp;
    cin >> tmp;
    counts [ tmp ] ++;
  }
  int sum = n;
  int res = findsum(sum, 0, 500, counts);
  
}
