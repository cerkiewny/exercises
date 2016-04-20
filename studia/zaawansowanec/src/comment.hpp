#pragma once
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <string>
#include <iostream>

namespace mars { 

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

void print ( std::vector<char> str ){
  std::string tmp(str.begin(), str.end());
  std::cout << "Parsed comment: " << tmp << std::endl;
}

template <typename Iterator>
bool comment_parser ( Iterator first, Iterator last ) {
  qi::rule<Iterator, std::string(), ascii::space_type> comment_string;
  using qi::int_;
  using qi::lit;
  using qi::double_;
  using qi::lexeme;
  using ascii::char_;

  comment_string %= lexeme[';' >> +(char_)];

  bool r = phrase_parse( first, last, comment_string[&print]);
  if( first != last ){
    return false;
  }
  return r; 
}


}  // namespace mars

