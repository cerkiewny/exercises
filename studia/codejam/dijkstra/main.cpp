#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;
bool cmp (int i,int j) { return (i<j); }
//0 1 2 3  4  5  6  7
//1 i j k -1 -i -j -k

void printquat(int num){
  switch(num){
    case 0:
      cout << " 1";
      break;
    case 1:
      cout << " i";
      break;
    case 2:
      cout << " j";
      break;
    case 3:
      cout << " k";
      break;
    case 4:
      cout << "-1";
      break;
    case 5:
      cout << "-i";
      break;
    case 6:
      cout << "-j";
      break;
    case 7:
      cout << "-k";
      break;
  }
}


int quat[8][8] =
{
  { 0, 1, 2, 3, (0 + 4) % 8, (1 + 4) % 8, (2 + 4) % 8, (3 + 4) % 8},
  { 1, 4, 3, 6, (1 + 4) % 8, (4 + 4) % 8, (3 + 4) % 8, (6 + 4) % 8},
  { 2, 7, 4, 1, (2 + 4) % 8, (7 + 4) % 8, (4 + 4) % 8, (1 + 4) % 8},
  { 3, 2, 5, 4, (3 + 4) % 8, (2 + 4) % 8, (5 + 4) % 8, (4 + 4) % 8},
  { 4, 5, 6, 7, (4 + 4) % 8, (5 + 4) % 8, (6 + 4) % 8, (7 + 4) % 8},
  { 5, 0, 7, 2, (5 + 4) % 8, (0 + 4) % 8, (7 + 4) % 8, (2 + 4) % 8},
  { 6, 3, 0, 5, (6 + 4) % 8, (3 + 4) % 8, (0 + 4) % 8, (5 + 4) % 8},
  { 7, 6, 1, 0, (7 + 4) % 8, (6 + 4) % 8, (1 + 4) % 8, (0 + 4) % 8},
};

bool seeni;
bool seenk;
bool seen[8];

int calcres(int subres, int res, int count){
  if (count == 0)
    return 0;
  return quat[subres][calcres(subres, quat[res][subres], count - 1)];
}

void calcpos(int subres, int count){
  int curbeg = 0;
  bool seenbegs[8];
  bool cycle1  = false;
  bool cycle2 = false;
  int cyclen = 1;
  int cyccount = 1;

  for ( int i = 0; i < 8; i ++){
    seenbegs[i] = false;
  }
  while(!cycle1 && count > 0){
    count--;
    if (seenbegs[curbeg]){
      cycle1 = true;
    }
    curbeg = quat[curbeg][subres];
    seenbegs[curbeg] = true;
    if(seeni){
      if (curbeg == 3){
        seenk = true;
      }
      for(int i = 0; i < 8; i++){
        if(seen[i]){
          if(quat[curbeg][i] == 3){
             seenk = true;
          }
        }
      }
    }
    if(curbeg == 1){
      seeni = true;
    }
    for(int i = 0; i < 8; i++){
      if(seen[i]){
        if(quat[curbeg][i] == 1){
           seeni = true;
        }
      }
    }
     
  }
  while(!cycle2 && count > 0){
    count--;
    if (seenbegs[curbeg]){
      cycle2 = true;
    }
    curbeg = quat[curbeg][subres];
    seenbegs[curbeg] = true;
    if(seeni){
      if (curbeg == 3){
        seenk = true;
      }
      for(int i = 0; i < 8; i++){
        if(seen[i]){
          if(quat[curbeg][i] == 3){
             seenk = true;
          }
        }
      }
    }
    if(curbeg == 1){
      seeni = true;
    }
    for(int i = 0; i < 8; i++){
      if(seen[i]){
        if(quat[curbeg][i] == 1){
           seeni = true;
        }
      }
    }
     
  }
  for ( int i = 0; i < 8; i ++){
    seenbegs[i] = false;
  }
}


int main(){
  ifstream in("in.txt");
  ofstream out("out.txt");
  int count = 0;
  in >> count;
  for(int i = 0; i < count; i++){
    int len = 0;
    in >> len;
    int rep = 0;
    in >> rep;
    seeni = false;
    seenk = false;
    for(int j = 0; j < 8; j++){
      seen[j] = false;
    }
    int res = 0;
    int subres = 0;
    for( int j = 0; j < len; j++){
      char cur;
      in >> cur;
      int curn = (int)(cur - 'h');
      res = quat[res][curn]; 
      seen[res] = true;
      if(seeni && res == 3){
        seenk = true;
      }
      if(res == 1){
        seeni = true;
      }

    }
    subres = res;
    printquat(subres);
    cout << " ";
    calcpos(subres, rep - 1);
    res = calcres(subres, 0, rep);
    cout << res << " " << seeni << " " << seenk << endl;
    if (res == 4 && seeni && seenk){
      cout << "yes";
      out << "Case #" << i + 1 << ": YES" << endl;
      cout << endl;
    }
    else{
      out << "Case #" << i + 1 << ": NO" << endl;
      cout << "no";
      cout << endl;
    }

    cout << endl;
  }

}
