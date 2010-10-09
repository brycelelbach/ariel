//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(FANGED_CMDLINE_MODULE_LOADER_GRAMMAR_HXX)
#define FANGED_CMDLINE_MODULE_LOADER_GRAMMAR_HXX

#include <clang/Frontend/CompilerInstance.h>

#include <boost/spirit/home/qi/action.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/auxiliary.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/binary.hpp>
#include <boost/spirit/home/qi/directive.hpp>
#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <boost/spirit/home/qi/string.hpp>

#include <boost/spirit/include/phoenix.hpp>

namespace fanged {

namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;
namespace fusion = boost::fusion;

namespace cmdline {

template<class Iterator>
class module_loader_grammar: public qi::grammar<Iterator> {
 public:
  clang::CompilerInstance& comp;

  qi::rule<Iterator>
    start;

  module_loader_grammar (clang::CompilerInstance& new_comp):
    module_loader_grammar::base_type(start),
    comp(new_comp)
  {
    start %= qi::kwd("help")[qi::eps] / qi::kwd("version")[qi::eps];
  }
};

} // cmdline 
} // fanged

#endif // FANGED_CMDLINE_MODULE_LOADER_GRAMMAR_HXX
