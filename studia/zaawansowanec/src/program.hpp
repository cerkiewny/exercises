#pragma once
#include <iostream>
#include <vector>
#include "instruction.hpp"


namespace mars {
class program {
 public:
  std::vector<instruction> instructions;
  void addinstr(instruction newinstr);
};

}

std::ostream& operator<<(std::ostream& os, const mars::program& p);
