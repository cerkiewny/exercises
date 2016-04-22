#pragma once

#include <queue>
#include "instruction.hpp"
#include "program.hpp"
#include "process.hpp"

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
  void exec_turns(int howmany);
  void exec_command(unsigned int which, process &proc);
  std::vector<std::queue<process>> programs;
 private:
  unsigned int resolve_adr(address which, unsigned int where);
  class command_invalid{
    public:
      command_invalid(std::string why) : why(why){};
      std::string why;
  };
  int turn;

};

}
