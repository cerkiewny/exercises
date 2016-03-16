#include <iostream>
#include <stdio.h>

using namespace std;


int a[1000000] = {};

long long int calc( long long int n){
   if(n < 12){
      return n;
   } else if (n < 1000000){
     if (a[n]){
      return a[n];
     } else {
      a[n] = calc(n/2) + calc(n/3) + calc(n/4);
      return a[n];
     }
   } else {
      return calc(n/2) + calc(n/3) + calc(n/4);
   }
}



int main(){

  long long int n;
  while(scanf("%lli", &n) != EOF){
    long long int ret = calc(n);
    cout << ret << endl;


  }
}
