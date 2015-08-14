#include<iostream>

using namespace std;

int male[26];
int duze[26];

int main(){
  int nlines;
  cin >> nlines;

  for(int i = 0; i < 26; i++){
    male[i] = 0;
    duze[i] = 0;
  }
  for(int i = 0; i < nlines + 1; i++){
    string curline;
    getline(cin,  curline);
    for (int j = 0; j < curline.size(); j++){
      char tmp = curline[j];
      if( tmp >= 'a' && tmp <= 'z'){
        male[tmp - 'a'] ++;
      }
      if( tmp >= 'A' && tmp <= 'Z'){
        duze[tmp - 'A'] ++;
      }
    }
  }
  for (int i = 0; i < 26; i++){
    if ( male[i] > 0 ){
      cout << char(i+'a') << " " << male[i] << endl;
    }
  }
  for (int i = 0; i < 26; i++){
    if ( duze[i] > 0 ){
      cout << char(i+'A') << " " << duze[i] << endl;
    }
  }
}
