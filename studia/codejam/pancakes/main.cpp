#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct solution{
  vector<int> plates;
  int cost;
  int price;
};

bool cmp (int i,int j) { return (i<j); }

class Compare{
    public:
    bool operator()(solution& t1, solution& t2) // Returns true if t1 is earlier than t2
    {
       if (t1.cost > t2.cost) return true;
       return false;
    }
};


int main(){
  ifstream in("in.txt");
  ofstream out("out.txt");

  int count = 0;
  in >> count;
  for(int i = 0; i < count; i++){
    int diners = 0;
    in >> diners;
    std::vector<int> plates(diners);
    int max = 0;
    for(int j = 0; j < diners; j++){
      in >> plates[j];
      if(plates[j] > max){
        max = plates[j]; 
      }
    }
    int res = max;
    priority_queue<solution, vector<solution>, Compare> pq;
    solution cursol;
    cursol.plates = plates;
    cursol.cost = 0;
    cursol.price = max;
    pq.push(cursol);
    while(cursol.cost <= res && !pq.empty()){
      cursol = pq.top();
      if(cursol.price < res){
        res = cursol.price;
      }
      pq.pop();
      std::sort (cursol.plates.begin(), cursol.plates.end(), cmp);
      for(int i = 1; i < cursol.plates[cursol.plates.size() - 1] / 2 + 1; i++){
        solution tempsol;
        tempsol.plates = cursol.plates;
        tempsol.plates.pop_back();
        tempsol.plates.push_back(i);
        tempsol.plates.push_back(cursol.plates[cursol.plates.size() - 1] - i);
        tempsol.cost = cursol.cost +1;
        tempsol.price = tempsol.cost + *std::max_element(tempsol.plates.begin(), tempsol.plates.end());
        if(tempsol.cost < res){
          pq.push(tempsol);
        }
      }
    }

    cout << "Case #" << i +1 << ": " << res << endl;
  }

}
