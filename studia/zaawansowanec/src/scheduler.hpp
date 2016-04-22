#pragma once

#include <vector>
#include <queue>
#include "process.hpp"

namespace mars {

class scheduler{

  private:
    std::vector<std::queue<process>> programs;

  public:
    int exec_turn();

};
}
