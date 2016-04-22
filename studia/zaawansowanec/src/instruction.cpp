#include "instruction.hpp"

namespace mars {

instruction::instruction() : address_a(), address_b(){
}

}

std::ostream& operator<<(std::ostream& os, const mars::instruction& p) {
  switch(p.kind){
    case(mars::instruction::kinds::DAT): os << std::string("DAT"); break;
    case(mars::instruction::kinds::MOV): os << std::string("MOV"); break;
    case(mars::instruction::kinds::ADD): os << std::string("ADD"); break;
    case(mars::instruction::kinds::SUB): os << std::string("SUB"); break;
    case(mars::instruction::kinds::MUL): os << std::string("MUL"); break;
    case(mars::instruction::kinds::DIV): os << std::string("DIV"); break;
    case(mars::instruction::kinds::MOD): os << std::string("MOD"); break;
    case(mars::instruction::kinds::JMP): os << std::string("JMP"); break;
    case(mars::instruction::kinds::JMZ): os << std::string("JMZ"); break;
    case(mars::instruction::kinds::JMN): os << std::string("JMN"); break;
    case(mars::instruction::kinds::DJN): os << std::string("DJN"); break;
    case(mars::instruction::kinds::SPL): os << std::string("SPL"); break;
    case(mars::instruction::kinds::SLT): os << std::string("SLT"); break;
    case(mars::instruction::kinds::CMP): os << std::string("CMP"); break;
    case(mars::instruction::kinds::SEQ): os << std::string("SEQ"); break;
    case(mars::instruction::kinds::SNE): os << std::string("SNE"); break;
    case(mars::instruction::kinds::NOP): os << std::string("NOP"); break;
    case(mars::instruction::kinds::LDP): os << std::string("LDP"); break;
    case(mars::instruction::kinds::STP): os << std::string("STP"); break;
  }
  switch(p.modifier){
    case(mars::instruction::modifiers::A):
      os << std::string(".A");
      break;
    case(mars::instruction::modifiers::B):
      os << std::string(".B");
      break;
    case(mars::instruction::modifiers::AB):
      os << std::string(".AB");
      break;
    case(mars::instruction::modifiers::BA):
      os << std::string(".BA");
      break;
    case(mars::instruction::modifiers::F):
      os << std::string(".F");
      break;
    case(mars::instruction::modifiers::X):
      os << std::string(".X");
      break;
    case(mars::instruction::modifiers::I):
      os << std::string(".I");
      break;
  }
  os << " " << p.address_a << ", " << p.address_b;
  return os;
}
