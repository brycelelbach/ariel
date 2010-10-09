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

#include <llvm/Support/raw_ostream.h>

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

#include <fanged/cmdline/builtins.hxx>

namespace fanged {

namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;
namespace fusion = boost::fusion;

namespace cmdline {

class help_printer {
 private:
  llvm::raw_ostream& os;

 public:
  typedef void result_type;

  help_printer (void): os(llvm::outs()) { }

  void operator() (void) const {
    os << "fanged <module> <module-arguments>\n\n"
          "builtin modules:\n";

    list_builtins(os);
  }
};

class version_printer {
 private:
  llvm::raw_ostream& os;

 public:
  typedef void result_type;

  version_printer (void): os(llvm::outs()) { }

  void operator() (void) const {
    os << "fanged: Frontend to Ariel that's Not a Gcc Esque Driver\n\n"
       << "ariel v" << ARIEL_RELEASE
       << " (\"" << ARIEL_CODENAME
       << "\") " << ARIEL_VERSION
       << "\n";
  }
};

template<class Iterator>
class module_loader_grammar: public qi::grammar<Iterator> {
 public:
  clang::CompilerInstance& comp;

  qi::rule<Iterator>
    start;

  px::function<help_printer> help;
  px::function<version_printer> version;

  module_loader_grammar (clang::CompilerInstance& new_comp):
    module_loader_grammar::base_type(start),
    comp(new_comp)
  {
    start %= qi::kwd("help")    [qi::eps[help()]]
           / qi::kwd("version") [qi::eps[version()]];
  }
};

} // cmdline 
} // fanged

#endif // FANGED_CMDLINE_MODULE_LOADER_GRAMMAR_HXX
