#include "loader.hpp"

namespace mars {

namespace qi = boost::spirit::qi;

void print(int const& i) {
  std::cout << i << std::endl;
}

void yayprint() {
  std::cout << "YAY" << std::endl;
}

void comment(std::vector<char> str) {
  std::string stri(str.begin(), str.end());
  std::cout << "YAY found comment" << stri << std::endl;
}

namespace ascii = boost::spirit::ascii;
template <typename Iterator>
struct redcode_gr : qi::grammar<Iterator, std::string()> {
  redcode_gr() : redcode_gr::base_type(start) {
    using qi::eps;
    using qi::lit;
    using qi::_val;
    using qi::_1;
    using boost::spirit::lexeme;
    using boost::spirit::ascii::char_;
    command = lexeme["ADD" >> +(char_)] |
      (lexeme["MOV" >> +(char_)])[&comment] |
      lexeme["DAT" >> +(char_)] |
      lexeme["SUB" >> +(char_)] |
      lexeme["MUL" >> +(char_)] |
      lexeme["DIV" >> +(char_)] |
      lexeme["MOD" >> +(char_)] |
      lexeme["JMP" >> +(char_)]
      ;
    start = *(command | (lexeme[';' >> +(char_)])[&comment]);
  }

  qi::rule<Iterator, std::string()> start;
  qi::rule<Iterator, std::string()> command;
};

program loader::load(std::string filename){
  program ret;
  std::ifstream in (filename);
  std::string tmp;


  typedef std::string::const_iterator iterator_type;
  typedef mars::redcode_gr<iterator_type> redcode_gram;
  redcode_gram gram;
  while(getline(in, tmp)){
    std::string::const_iterator iter = tmp.begin();
    std::string::const_iterator end = tmp.end();
    std::string res;
    bool r = parse (iter, end, gram); 

    if ( r && iter == end ) {
      std::cout << "parsing command sucess" << std::endl;
    } else {
      std::cout << "parsing command failed" << std::endl;
    }

  }

  return ret;
}

}
