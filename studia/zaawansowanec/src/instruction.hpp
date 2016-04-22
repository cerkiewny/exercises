#pragma once
#include <string>
#include "address.hpp"

namespace mars { 
class instruction {
  public:
    enum kinds {
       DAT,
       MOV,
       ADD,
       SUB,
       MUL,
       DIV,
       MOD,
       JMP,
       JMZ,
       JMN,
       DJN,
       SPL,
       SLT,
       CMP,
       SEQ,
       SNE,
       NOP,
       LDP,
       STP
    };

    enum modifiers {
      DEF,
      A,
      B,
      AB,
      BA,
      F,
      X,
      I
    };

    address address_a;
    address address_b;
    kinds kind;
    modifiers modifier;
    instruction ();
};

}

std::ostream& operator<<(std::ostream& os, const mars::instruction& p);
