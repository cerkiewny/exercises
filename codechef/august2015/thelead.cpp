#include <iostream>

using namespace std;

int main(){
  int ngames;

  cin >> ngames;
  int suma, sumb;
  suma = 0;
  sumb = 0;
  int maxim = 0;
  int winer;
  for(int i = 0; i < ngames; i++){
    int tmpa, tmpb;
    cin >> tmpa;
    cin >> tmpb;
    suma += tmpa;
    sumb += tmpb;
    if (suma - sumb < 0){
      if(sumb - suma > maxim){
        maxim = sumb - suma;
        winer = 2;
      }
    }
    else if(suma - sumb > maxim){
        maxim = suma - sumb;
        winer = 1;
    }
  }
  cout << winer << " "<< maxim << endl;
}
