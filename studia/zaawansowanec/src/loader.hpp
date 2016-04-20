#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/include/qi_int.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include "program.hpp"

namespace mars {

class loader {
  public:
    static program load(std::string filename);
};

}
