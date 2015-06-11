#include<iostream>
#include<fstream>
int data[1000];

int main(){
  ifstream in("in");
  ofstream out("out");

  int ncases;

  in >> ncases;



  for(int i =0; i < ncases; i++){
    int nbarb;
    int place;
    in >> nbarb;
    in >> place;
    for(int j = 0; j < nbarb; j++){
      in >> data[j];
    }
  }
}
