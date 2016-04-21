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
      DEFAULT,
      A,
      B,
      AB,
      BA,
      F,
      X,
      I
    };

    address a;
    address b;
    kinds kind;
    instruction () : a(), b(){
      kind = DAT;
    };
};

}

std::ostream& operator<<(std::ostream& os, const mars::instruction& p);
