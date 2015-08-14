#include<string>
#include<queue>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class cmpr{ 
  public:
    bool operator() ( string lhs, string rhs){
      if(lhs.size() > rhs.size()){
        return true;
      }
      else if(lhs.size() < rhs.size()){
        return false;
      }
      else{
        if(lhs > rhs){
          return true; 
        }
        else
          return false;
      }
    }
};

int main(){
  int n;
  cin >> n;

  priority_queue<string, vector<string>, cmpr> pq;
  for ( int i = 0; i < n ; i++){
    std::string tmp;
    cin >> tmp;
    pq.push(tmp);
  }

  while(!pq.empty()){
    cout << pq.top() << endl;
    pq.pop();
  }
}
