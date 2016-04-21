#include "program.hpp"

namespace mars {
  void program::addinstr(instruction newinstr){
    instructions.push_back(newinstr);
  
  }
}

std::ostream& operator<<(std::ostream& os, const mars::program& p) {
    for(int i = 0 ; i < p.instructions.size(); i ++){
      mars::instruction cur = p.instructions.at(i);
      os << cur << std::endl;
    }
    return os;
}
