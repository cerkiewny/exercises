#include<random>
#include<iostream>

int main(){

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(1,100);
  int rand1 = distribution(generator);

  std::cout << rand1 <<  std::endl; 
  for(int i = 0; i < rand1; i++){
    int rand2 = distribution(generator);
    std::cout << rand2 << " ";
    for(int j = 0; j < rand2; j++){
      std::uniform_int_distribution<int> distribution2(0,2);
      std::cout << distribution2(generator);
    }
    std::cout << std::endl;
  }
}
