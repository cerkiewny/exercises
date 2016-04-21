#include "instruction.hpp"

std::ostream& operator<<(std::ostream& os, const mars::instruction& p) {
  os << static_cast<std::underlying_type<mars::address::modes>::type>(p.kind) << std::endl;
  return os;
}
