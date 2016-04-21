#include <string>
#include <iostream>
#include "loader.hpp"

int main(){
  mars::program test = mars::loader::load ("warriors/testwarrior1.redcode");
  std::cout << test;

}
