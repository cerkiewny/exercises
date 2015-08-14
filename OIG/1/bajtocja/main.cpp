#include <iostream>
#include <queue>
#include <list>

using namespace std;

int maxrt = 0;

bool seen[7000];

struct connection{
  int from;
  int dest;
  int cost;
};

connection choice[7000];
list < connection > cons[7000]; 

list < connection > allcons; 

bool finish(int n){
  for (int i = 0; i < n; i++){
    if (seen[i] == false)
      return false;
  }
  return true;
}

bool operator<(const connection& lhs, const connection& rhs)
{
    return lhs.cost > rhs.cost;
}


unsigned long long calccost(int howmany, priority_queue<connection>& pq, unsigned long long mincost, bool rt = false){
  int ret = 0;
  while(!finish(howmany)){
    connection tmp = pq.top();
    pq.pop();
    while(seen[tmp.dest]){
      tmp = pq.top();
      pq.pop();
    }
    ret += tmp.cost;
    if (choice[tmp.from].cost > tmp.cost){
      choice[tmp.from] = tmp;
    }
    if(rt && tmp.cost > maxrt){
      maxrt = tmp.cost;
    }
    seen[tmp.dest] = true;
    for( list<connection>::iterator i = cons[tmp.dest].begin(); i != cons[tmp.dest].end(); i++ ){
      pq.push(*i);
    }
  }
  return ret;
}

using namespace std;

int main(){

  int cnt_n, cnt_v;

  cin >> cnt_n;
  cin >> cnt_v;

  for ( int i = 0; i < cnt_n; i++){
    seen[i] = false;
    choice[i].cost = 9999999;
  }
  for ( int i = 0; i < cnt_v; i++){
    connection tmp;
    int from, to, cost;
    cin >> from;
    cin >> to;
    cin >> cost;
    from--;
    to--;
    tmp.dest = to;
    tmp.from = from;
    tmp.cost = cost;
    allcons.push_back(tmp);
    cons[from].push_back(tmp);
    tmp.from = to;
    tmp.dest = from;
    cons[to].push_back(tmp);
  }
  priority_queue<connection> pq;
  seen[0] = true;
  for( list<connection>::iterator i = cons[0].begin(); i != cons[0].end(); i++){
    pq.push(*i);
  }
  unsigned long long mincost = calccost(cnt_n, pq, 99999999999, true);
  for( list<connection>::iterator it = allcons.begin(); it != allcons.end(); it++ ){
        for ( int i = 0; i < cnt_n; i++){
          seen[i] = false;
        }
        priority_queue<connection> pq2;
        unsigned long long cst = it->cost;
        seen[it->from] = true;
        seen[it->dest] = true;
        for( list<connection>::iterator it2 = cons[it->dest].begin(); it2 != cons[it->dest].end(); it2++ ){
          pq2.push(*it2);
        }
        for( list<connection>::iterator it2 = cons[it->from].begin(); it2 != cons[it->from].end(); it2++ ){
          pq2.push(*it2);
        }
        cst += calccost(cnt_n, pq2, mincost);
        if (cst > mincost)
          cout << "NIE" << endl;
        else
          cout << "TAK" << endl;
      //cout << cst << " " << mincost << endl;
    }

}
