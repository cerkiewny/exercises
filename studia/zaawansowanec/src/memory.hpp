#pragma once

#include "program.hpp"
#include "instruction.hpp"
#include "scheduler.hpp"

namespace mars {

class memory {
 public:
  static unsigned int memsize;
  void load(unsigned int where, program p);
  instruction get(unsigned int where);
  void set(unsigned int where, instruction instr);
  static unsigned int memoffset;
  std::vector<instruction> mem;
  void load_all(std::vector<program> warriors);
  void print(unsigned int location);
  memory();
  scheduler shed;
  void exec_turns(int howmany);

};

}
