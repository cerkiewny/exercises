#pragma once
#include <iostream>

namespace mars {

class address {
  public:
    enum class modes : char {
      IMMIDIATE = '#',
      DIRECT = '$',
      INDIRECT_B = '@',
      PREDECREMENT_B = '<',
      POSTINCREMENT_B = '>',
      INDIRECT_A = '*',
      PREDECREMENT_A = '{',
      POSTINCREMENT_A = '}'
    };

    address(){
      mode = modes::DIRECT;
      offset = 0;
    }

    address(int off){
      offset = off;
      mode = modes::DIRECT;
    }

    address(int off, modes m){
      offset = off;
      mode = m;
    }

    address(modes m){
      mode = m;
      offset = 0;
    }

    int offset;
    modes mode;
};

}

std::ostream& operator<<(std::ostream& os, const mars::address& a);

inline bool operator==(const mars::address &lhs, const mars::address &rhs){
  if(lhs.mode == rhs.mode && lhs.offset == rhs.offset)
    return true;
  return false;
}

inline bool operator!=(const mars::address &lhs, const mars::address &rhs){
  return !(rhs == lhs);
}
