#include <iostream>
#include <cmath>

using namespace std;

struct point{
  int x;
  int y;
};

float dist(point o, point t){
  float dx ,dy;
  dx = o.x - t.x;
  dy = o.y - t.y;
  float ret = sqrt(dx * dx + dy * dy);
  return ret;
}

int main(){
  int ncases;
  cin >> ncases;

  for(int i = 0; i < ncases; i++){
    int range;
    cin >> range;
    point o1, o2, o3;
    cin >> o1.x >> o1.y;
    cin >> o2.x >> o2.y;
    cin >> o3.x >> o3.y;
    int res = 0;
    if(dist(o1, o2) <= range){
      res ++;
    }
    if(dist(o2, o3) <= range){
      res ++;
    }
    if(dist(o1, o3) <= range){
      res ++;
    }
    if (res > 1){
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}
