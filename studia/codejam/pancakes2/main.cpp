#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>

#define maxnum 1000 


int findmax(int max, int * nums]){
  for (int i = max; i > 0; i++){
    if (nums[i] != 0){
      return i;
    }
  }
}

int main(){
  static int nums [maxnum];
  std::ifstream in("in.txt");
  std::ofstream out("out.txt");

  int count = 0;
  in >> count;
  for(int i = 0; i < count; i++){
    for(int j = 0; j < maxnum; j++){
      nums[j] = 0;
    }
    int max = 0;
    int cost = 0;
    int diners = 0;
    in >> diners;
    for(int j = 0; j < diners; j++){
      int curnum;
      in >> curnum;
      std::cout << curnum << "asdf ";
      nums[curnum]++;
      if(curnum > max){
        max = curnum;
      }
    }
    int res = max;   

    while(res > cost){
      for(int i = max; i > 0; i--){
         nums[max]--;
         nums[max/2] ++;
         if(max % 2 ==0){
           nums[max/2] ++;
         }
         else{
           nums[(max/2) + 1]++;
         }
         cost++;
         max = findmax(max, nums);
         if (max + cost < res){
          res = max + cost;
         }
      }
    }
    std::cout << res << std::endl;
    out << "Case #" << i + 1 << ": " << res << std::endl;
    
  }

}
