#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}include <iostream>

using namespace std;

void printall(vector<string> a, vector<string> b, string cur){
  if(a.size() = 0){
    cout << cur;
  }
  else 

}


int main(){
  string a, b;
  cin >> a;
  cin >> b;

  auto fir = split(a, ' ');
  auto sec = split(b, ' ');
  
  printall(fir,sec, "");
  
}
