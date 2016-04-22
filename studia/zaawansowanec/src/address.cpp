#include "address.hpp"

std::ostream& operator<<(std::ostream& os, const mars::address& a){
  os << static_cast<std::underlying_type<mars::address::modes>::type>(a.mode) << a.offset;
}
