#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main(){
  
  ifstream in("in.txt");
  ofstream out("out.txt");


  int ncases;

  in >> ncases;

  for (int i = 0; i < ncases; i++){
    int x;
    int y;
    int n;
    in >> n >> x >> y;


    out << "Case #" << i+1 << ": " << res  << endl;
  }
}


