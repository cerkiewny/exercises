#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "memory.hpp"

namespace mars {

unsigned int memory::memsize = 8000;
unsigned int memory::memoffset = 5000;

memory::memory() : mem(memory::memsize), programs(){
  
}

void memory::print(unsigned int location){
  std::cout << mem.at(location) << std::endl;
};

void memory::load_all(std::vector<program> warriors){
  boost::random::random_device rng;
  boost::random::uniform_int_distribution<> rand(1, memsize);
  std::vector<unsigned int> locations;
  bool intersect;
  do {
    locations.clear();
    for(int i = 0; i < warriors.size(); i ++){
      locations.push_back(rand(rng));
      std::cout << locations.at(i) << " ";
    }
    for(int i = 0; i < warriors.size(); i ++){
      intersect = false;
      for(int j = 0; j < warriors.size(); j ++){
        for(int k = 0; k < warriors.size(); k ++){
          if(j != k){
            if(locations.at(j) + warriors.at(j).instructions.size() % memsize > locations.at(k) &&
                locations.at(j) < locations.at(k)) {
              intersect = true;
            }
          }
        }
      }
    }
  } while(intersect);
  for(int i = 0; i < warriors.size(); i++){
    load(locations.at(i), warriors.at(i));
  }
}

void memory::load(unsigned int where, program p){
  for(int i = 0; i < p.instructions.size(); i++){
    mem.at(i + where) = p.instructions.at(i);
  }
}

void memory::exec_turns(int howmany){
  for(int i = 0; i < howmany; i ++){
    int tmp = 0;
    if(tmp > 0){
      std::cout << "winner is warrior number" << tmp << std::endl; 
      return;
    }
  }
}

}
