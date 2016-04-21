#pragma once

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
    virtual int calculate(int where) { return where; }
};
}
