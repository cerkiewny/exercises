#include "loader.hpp"
#include <locale>
#include <boost/bind.hpp>
#include <boost/spirit/include/qi_char_class.hpp>

namespace mars {

namespace qi = boost::spirit::qi;

address loader::curaddr_one = {}; 
address loader::curaddr_two = {};
address::modes loader::curmode = address::modes::DIRECT;
instruction::modifiers loader::curmodif = instruction::modifiers::DEF;
int loader::curaddr = 0;
program loader::program_ = {};

void loader::set_modif(instruction::modifiers which){
  
}
void loader::start_creation(){
  address tmp(0, address::modes::DIRECT);
  loader::curmodif = instruction::modifiers::DEF;
  loader::curaddr_one = tmp; 
  loader::curaddr_two = tmp;
}

void loader::set_cur_addr(int which){
  loader::curaddr = which;
//  std::cout << which << std::endl;
}

void loader::set_cur_mode(address::modes which){
  loader::curmode = which;
  //std::cout << static_cast<std::underlying_type<address::modes>::type>(curmode) << std::endl;
}

void loader::finish_addr() {
  curaddr_one.offset = loader::curaddr;
  curaddr_one.mode = loader::curmode;
  loader::curmode = address::modes::DIRECT;
  loader::curaddr = 0;
}

namespace ascii = boost::spirit::ascii;
template <typename Iterator>
struct redcode_gr : qi::grammar<Iterator, std::string(), ascii::space_type> {
  redcode_gr() : redcode_gr::base_type(start) {
    using qi::eps;
    using qi::lit;
    using qi::_val;
    using qi::_1;
    using boost::spirit::lexeme;
    using boost::spirit::ascii::char_;
    using boost::spirit::qi::int_;
    address_mode = 
      lexeme['#'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::IMMIDIATE)] |
      lexeme['@'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::INDIRECT_B)] |
      lexeme['<'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::PREDECREMENT_B)] |
      lexeme['>'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::POSTINCREMENT_B)] |
      lexeme['*'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::INDIRECT_A)] |
      lexeme['{'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::PREDECREMENT_A)] |
      lexeme['}'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::POSTINCREMENT_A)] |
      lexeme['$'] >> eps[boost::bind(&loader::set_cur_mode, address::modes::DIRECT)];
    comm_mod = 
      lexeme[".AB"] >> eps[boost::bind(&loader::set_modif, instruction::modifiers::AB)] |
      lexeme[".A"] >> eps[boost::bind(&loader::set_modif, instruction::modifiers::A)]  |
      lexeme[".BA"] >> eps[boost::bind(&loader::set_modif, instruction::modifiers::BA)] |
      lexeme[".B"] >> eps[boost::bind(&loader::set_modif, instruction::modifiers::B)]  |
      lexeme[".F"] >> eps[boost::bind(&loader::set_modif, instruction::modifiers::F)]  |
      lexeme[".X"] >> eps[boost::bind(&loader::set_modif, instruction::modifiers::X)]  |
      lexeme[".I"] >> eps[boost::bind(&loader::set_modif, instruction::modifiers::I)];
    address = eps[boost::bind(&loader::set_cur_mode, address::modes::DIRECT)] >> -address_mode >> *ascii::space  >> int_[&loader::set_cur_addr] >> *ascii::space;
    command_standard = 
      lexeme["DAT" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "DAT")] |
      lexeme["MOV" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "MOV")] |
      lexeme["ADD" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "ADD")] |
      lexeme["SUB" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "SUB")] |
      lexeme["MUL" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "MUL")] |
      lexeme["DIV" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "DIV")] |
      lexeme["MOD" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "MOD")] |
      lexeme["JMP" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "JMP")] |
      lexeme["JMZ" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "JMZ")] |
      lexeme["JMN" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "JMN")] |
      lexeme["DJN" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "DJN")] |
      lexeme["SPL" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "SPL")] |
      lexeme["SLT" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "SLT")] |
      lexeme["CMP" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "CMP")] |
      lexeme["SEQ" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "SEQ")] |
      lexeme["SNE" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "SNE")] |
      lexeme["NOP" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "NOP")] |
      lexeme["LDP" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "LDP")] |
      lexeme["STP" >> eps[&loader::start_creation] >> -comm_mod >> *ascii::space >> address[&loader::finish_addr] >> *ascii::space >> -(',' >> *ascii::space  >> address)] >> eps[boost::bind(&loader::create_instr, "STP")];

    start = *(command_standard | (lexeme[';' >> +(char_)]));
  }

  qi::rule<Iterator, std::string(), ascii::space_type> start;
  qi::rule<Iterator, std::string(), ascii::space_type> command_standard;
  qi::rule<Iterator> address;
  qi::rule<Iterator> address_mode;
  qi::rule<Iterator> comm_mod;
};

void loader::create_instr(const std::string what){
  instruction newinstr;
  curaddr_two.offset = loader::curaddr;
  curaddr_two.mode = loader::curmode;
  if(what == "DAT"){
    newinstr.kind = instruction::kinds::DAT;
  } else if (what == "MOV"){
    newinstr.kind = instruction::kinds::MOV;
  } else if (what == "ADD"){
    newinstr.kind = instruction::kinds::ADD;
  } else if (what == "SUB"){
    newinstr.kind = instruction::kinds::SUB;
  } else if (what == "MUL"){
    newinstr.kind = instruction::kinds::MUL;
  } else if (what == "DIV"){
    newinstr.kind = instruction::kinds::DIV;
  } else if (what == "MOD"){
    newinstr.kind = instruction::kinds::MOD;
  } else if (what == "JMP"){
    newinstr.kind = instruction::kinds::JMP;
  } else if (what == "JMZ"){
    newinstr.kind = instruction::kinds::JMZ;
  } else if (what == "JMN"){
    newinstr.kind = instruction::kinds::JMN;
  } else if (what == "DJN"){
    newinstr.kind = instruction::kinds::DJN;
  } else if (what == "SPL"){
    newinstr.kind = instruction::kinds::SPL;
  } else if (what == "SLT"){
    newinstr.kind = instruction::kinds::SLT;
  } else if (what == "CMP"){
    newinstr.kind = instruction::kinds::CMP;
  } else if (what == "SEQ"){
    newinstr.kind = instruction::kinds::SEQ;
  } else if (what == "SNE"){
    newinstr.kind = instruction::kinds::SNE;
  } else if (what == "NOP"){
    newinstr.kind = instruction::kinds::NOP;
  } else if (what == "LDP"){
    newinstr.kind = instruction::kinds::LDP;
  } else if (what == "STP"){
    newinstr.kind = instruction::kinds::STP;
  }
  newinstr.modifier = curmodif;
  newinstr.address_a = curaddr_one;
  newinstr.address_b = curaddr_two;
  loader::program_.addinstr(newinstr); 
}

program loader::load(std::string filename){
  std::ifstream in (filename);
  std::string tmp;


  typedef std::string::const_iterator iterator_type;
  typedef mars::redcode_gr<iterator_type> redcode_gram;
  redcode_gram gram;
  while(getline(in, tmp)) {
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), toupper);
    std::string::const_iterator iter = tmp.begin();
    std::string::const_iterator end = tmp.end();
    std::string res;
    bool r = phrase_parse (iter, end, gram, ascii::space); 

    if ( r && iter == end ) {
      //std::cout << "parsing command sucess" << std::endl;
    } else {
      //std::cout << "parsing command failed" << std::endl;
    }

  }
  program ret = program_;
  program_ = program();
  return ret;
}

}
