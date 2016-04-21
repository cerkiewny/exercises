#pragma once

#include "program.hpp"
#include "instruction.hpp"

namespace mars {

class memory {
 public:
  const static unsigned int memsize;
  memory();
  void load(unsigned int where, program);
  instruction get(unsigned int where);
  void set(unsigned int where, instruction instr);
};

}
