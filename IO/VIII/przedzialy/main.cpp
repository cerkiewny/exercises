#include<iostream>
#include<list>

using namespace std;

struct przed{
  int beg;
  int end;
};

int main(){

  int nprz;
  cin >> nprz;
  list<przed> sol;

  for(int i = 0 ; i < nprz; i ++){
    przed tmp;
    cin >> tmp.beg;
    cin >> tmp.end;
    for(list<przed>::iterator j = sol.begin(); j != sol.end(); j++){
      bool del = false;
      if(j->end <= tmp.end && j->end >= tmp.beg){
        if( j->beg < tmp.beg)
          tmp.beg  = j->beg;
        del = true;
      }
      if(j->beg >= tmp.beg && j->beg <= tmp.end){
        if( j->end > tmp.end)
          tmp.end = j->end;
        del = true;
      }
      if (del)
        sol.erase(j);
    }
    sol.push_back(tmp);

  }
  for(list<przed>::iterator j = sol.begin(); j != sol.end(); j++){
    cout << j->beg << " " << j->end << " " << endl;
  }
}
