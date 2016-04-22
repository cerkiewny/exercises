#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include "loader.hpp"
#include "memory.hpp"

int main(int argc, char * argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  std::vector<mars::program> warriors;
  mars::memory mem;
  bool debug = false;
  for(int i = 0; i < args.size(); i++) {
    if(args.at(i) == "-h") {
      std::cout << "-h prints this message\n-m <size> to change memory size\n \
        -d for debug mode (single warrior run) \
        provide all warrior files \n  use r for running s for \
        step other commands will likely be supported in future";
    } else if(args.at(i) == "-d") {
      debug = true;
    } else if(args.at(i) == "-m") {
      i++;
      unsigned int newmemsize = stoi(args.at(i));
      mars::memory::memsize = newmemsize;
      std::cout << "changing memmory size to " << newmemsize << std::endl;
    } else if ( !boost::filesystem::exists( args.at(i) ) ) {
        std::cout << "Can't find provided warrior " << args.at(i) << std::endl;
        return 0;
    } else if ( boost::filesystem::exists( args.at(i) ) ) {
      mars::program war = mars::loader::load (args.at(i));
      std::cout << "Loading warrior " << args.at(i) << std::endl;
      warriors.push_back(war);
    }
  }
  //warriors prepared
  if(debug || warriors.size() > 1) {
    // load them
    mem.load_all(warriors);
    if(debug){
      
    } else {
    
    }
    unsigned int totalsize = 0;
    for(int i = 0; i < warriors.size(); i++) {
      totalsize += warriors.at(i).instructions.size();
      std::cout << i << " warrior size " << warriors.at(i).instructions.size() << std::endl;
    }
    if (totalsize > mars::memory::memsize - mars::memory::memoffset) {
      std::cout << "the programs are too big for current memory settings" << std::endl;
      return 0;
    }

  } else {
    std::cout << "not enough warriors, use debug mode -d" << std::endl;
  }
  bool exit = false;
  while(!exit){
    std::string consolecom;
    std::cin >> consolecom;
    if(consolecom == "p"){
      unsigned int addr;
      std::cin >> addr;
      mem.print(addr);
    }
    if(consolecom == "q"){
      exit = true;
    }
    if(consolecom == "s"){
      int howmany;
      std::cin >> howmany;
      mem.exec_turns(howmany);
    }
  }

}
