#include<fstream>
#include<iostream>
#include<sstream>

using namespace std;

int main(){
  ifstream in("in.txt");
  ofstream out("out.txt");
  string line;
  getline(in, line);

  int count;
  istringstream ( line) >> count;
  for(int i = 0; i < count; i++){
    getline(in, line);
    string delimiter = " ";
    string numppls = line.substr(0, line.find(delimiter)); // token is "scott"
    string rest  = line.substr(line.find(delimiter) + 1, line.length()); // token is "scott"
    int numppl;
    istringstream ( numppls ) >> numppl ;
    int res = 0;
    int standing = 0;
    for(int j = 0; j < numppl + 1; j++){
      int cur = (int) (rest[j] - '0');

      if(standing >= j)
        standing += cur;
      else{
        cout << "++" << cur << " " << j << endl;
        standing += cur;
        standing++;
        res++;
      }
    }
    cout << res << endl;
    out << "Case #" << i + 1 << ": " << res << endl;
  }

}
