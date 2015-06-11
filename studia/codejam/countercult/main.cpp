#include <iostream>
#include <fstream>
#include <list>

using namespace std;


int costs[1000000];

int reverse(int number){
  int reverse = 0;
  for( ; number!= 0 ; )
  {
    reverse = reverse * 10;
    reverse = reverse + number%10;
    number = number/10;
  }
  return reverse;
}


int main(){
  
  ifstream in("in.txt");
  ofstream out("out.txt");


  int ncases;

  in >> ncases;
  for(int i = 0 ; i < 1000000; i++){
    costs[i] == 0;
  }
  costs[1] == 1;
  for (int i = 0; i < ncases; i++){
    int curnum;
    in >> curnum;
    for(int j = 1; j < curnum; j++){
      if(costs[j] == 0){
        costs[j] = costs[j-1] + 1;
        tmp = reverse[j];
        if(costs[tmp] == 0){
          costs[tmp] = costs[j] + 1;
        }
      }
    
    }




    out << "Case #" << i+1 << ": " << res  << endl;
  }
}


