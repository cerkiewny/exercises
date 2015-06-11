#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>

bool cmp (int i,int j) { return (i<j); }

using namespace std;

int main(){
  ifstream in("in.txt");
  ofstream out("out.txt");

  int count = 0;
  in >> count;
  for(int i = 0; i < count; i++){
    int x;
    int r;
    int c;

    in >> x;
    in >> r;
    in >> c;

    bool rich = false;
    if( (r * c) % x != 0){
      rich = true;
    }
    else if(x == 1){
      rich = false;
    }
    else{
      if(max(r, c) < x){
        rich = true;
      }
      if(r + c < (x - 1) ){
        rich = true;
      }
    }
    if ( x > 6){
      rich = true ;
    }
    if (!rich){
      out << "Case #" << i +1 << ": GABRIEL" << endl;
    }
    else{
      out << "Case #" << i +1 << ": RICHARD" << endl;
    }
  }

}
