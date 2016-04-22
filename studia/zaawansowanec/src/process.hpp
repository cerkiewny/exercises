#pragma once
#include "address.hpp"

namespace mars {
class process{
  public:
    process(unsigned int start);
  private:
    unsigned int exec_addr;
};
}
