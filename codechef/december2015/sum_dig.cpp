#include<iostream>
#include<string>

using namespace std;

int main(){
  int ncases;


  cin >> ncases;
  for (int i = 0; i < ncases; i++){
    string line;

    cin >> line;

    int sum = ((line[0]) - '0') + (line[line.size() -1] -'0');
    cout << sum << endl;
  }
}
