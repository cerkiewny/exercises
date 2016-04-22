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

inline bool operator==(const mars::instruction &lhs, const mars::instruction &rhs){
  if(lhs.address_a == rhs.address_b &&
     lhs.kind == rhs.kind &&
     lhs.modifier == rhs.modifier )
    return true;
  return false;
}

inline bool operator!=(const mars::instruction &lhs, const mars::instruction &rhs){
  return !(rhs == lhs);
}

std::ostream& operator<<(std::ostream& os, const mars::instruction& p);
