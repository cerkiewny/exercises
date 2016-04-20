#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <string>

namespace mars { 
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct command_parser : qi::grammar<Iterator, command(), ascii::space_type> {
  command_parser() : command_parser::base_type(start) {
  using qi::int_;
  using qi::lit;
  using qi::double_;
  using qi::lexeme;
  using ascii::char_;

  comment_string %= lexeme[';' >> +(char_)];
  command_string %= lexeme[+(char_)];

  start %=
    comand_string >> ','
    | -comment_string >> ','
    ;
  }

  qi::rule<Iterator, std::string(), ascii::space_type> comment_string;
  qi::rule<Iterator, std::string(), ascii::space_type> command_string;
  qi::rule<Iterator, command(), ascii::space_type> start;
};

}  // namespace mars

BOOST_FUSION_ADAPT_STRUCT(
    mars::command,
    (std::string, surname)
    (std::string, forename)
)
