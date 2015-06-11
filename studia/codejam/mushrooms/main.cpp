#include <iostream>
#include <fstream>

int data[1000];
using namespace std;

int main(){

  int ncases;
  ifstream in ("in");
  ofstream out ("out");

  in >> ncases;

  for(int i = 0; i < ncases; i++){
    int inters;

    in >> inters;

    int maxint = 0;
    for(int j = 0; j < inters; j++){
      in >> data[j];
      
      if(j > 0){
        if(data[j-1] - data[j] > maxint){
          maxint = data[j-1] - data[j];
        }
      }

    }
    long res1 = 0;
    long res2 = 0;
    for(int j = 0; j < inters; j++){
      if(j > 0 && data[j - 1] > data[j]){
        res1 += data[j - 1] - data[j];
      }
      if(j != inters - 1){
        if(data[j] < maxint)
          res2 += data[j];
        else
          res2 += maxint;
      }
    }
    out << "Case #" << i + 1<< ": " << res1 << " " << res2 << endl;
  
  }
}
