#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/include/qi_int.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include "program.hpp"
#include "address.hpp"

namespace mars {

class loader {
  public:
    static program load(std::string filename);
    static void create_instr(const std::string str);
    static void start_creation();
    static void set_cur_mode(address::modes which);
    static void set_cur_addr(int  which);
    static void finish_addr();
    static address::modes curmode;
    static instruction::modifiers curmodif;
    static int curaddr;
    static void set_modif(instruction::modifiers which);
  private:
    static program program_;
    static address curaddr_one;
    static address curaddr_two;
};

}
