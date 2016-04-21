#pragma once

#include <vector>
#include <queue>
#include "process.hpp"

class scheduler{

  private:
    std::vector<std::queue<process>> programs;

  public:
    int turn;
};
