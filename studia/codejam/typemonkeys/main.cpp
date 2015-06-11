#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>

using namespace std;

char chars[7];
char word[7];
int maxocur;

bool checkpos(int l, int k){
  for(int i = 0; i < l; i++){
    bool pos = false;
    for(int j = 0; j < k; j++){
      if (word[i] == chars[j]){
        pos = true; 
      }
    }
    if(!pos){
      return false;
    }
  }
  return true;
}

int countcomp(int l){
  for(int i = 1; i < l; i++){
    bool res = true;
    for(int j = 0; j < l; j++){
      if(word[j] != word[(j + i) % l]){
        res = false;
      }
    }
    if (res)
      return i;
  }
  return l;
}

int occurances(char tocheck[7], int l, int s){
  cout << tocheck << endl;
  int ret = 0;
  for(int i = 0; i < s - l; i++){
    bool found = true;
    for(int j = 0; j < l; j++){
       if(tocheck[i + j] != word[j]){
         found = false;
         break;
       }
    }
    if(found)
      ret++;
    
  }
  if(ret > maxocur){
    maxocur = ret;
  }
  return ret;
  
}

int recur_search(int k, int l, int s, char curword[7], int curlen = 0){
  if (curlen == s){
    return occurances(curword, l, s);
  }
  else{
    int sum = 0;
    for(int i = 0; i < k; i++){
      char nextword[7];
      for(int j = 0; j < curlen; j++){
        nextword[j] = curword[j];
      }
      nextword[curlen] = chars[i];
      sum += recur_search(k, l, s, nextword, curlen + 1);
    }
    return sum;
  }
}

int main(){

  ifstream in ("in");
  ofstream out ("out");

  int ncases;

  in >> ncases;

  for(int i = 0; i < ncases; i++){
    double res;
    maxocur = 0;
    for(int j = 0; j < 26; j++){
      chars[j] = 0;
    }


    int k, l, s;

    in >> k >> l >> s;

    for(int j = 0; j < k; j++){
       in >> chars[j];
    }

    for(int j = 0; j < l; j++){
       in >> word[j];
    }
    if(checkpos(l, k)){
      char firstarray[7];
      int count = recur_search(k, l, s, firstarray, 0);
      double howmany = pow(k, s); 
      double expected = count / howmany;
      res = (double)maxocur - expected;
    }
    else{
      res = 0.0;
    }
   
    if (res < 0.0){
      res = 0.0;
    }
    cout << res << endl;
    out << setprecision(9) << "Case #" << i + 1 << ": " << res << endl;

  }

  return 0;

}
