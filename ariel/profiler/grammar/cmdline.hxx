//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_CMDLINE_GRAMMAR_HXX)
#define ARIEL_PROFILER_CMDLINE_GRAMMAR_HXX

#include <clang/Frontend/CompilerInstance.h>

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/raw_ostream.h>

#include <boost/spirit/include/support_ascii.hpp>

#include <boost/spirit/home/qi/action.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/auxiliary.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/binary.hpp>
#include <boost/spirit/home/qi/directive.hpp>
#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <boost/spirit/home/qi/string.hpp>

#include <boost/spirit/include/phoenix.hpp>

#include <boost/scoped_ptr.hpp>

namespace ariel {

namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;
namespace fusion = boost::fusion;

namespace profiler {

template<class Iterator>
class cmdline_grammar: public qi::grammar<Iterator> {
 public:
  class help_printer {
   private:
    llvm::raw_ostream& os;
    std::string const& module;

   public:
    typedef void result_type;

    help_printer (std::string const& new_module):
      os(llvm::outs()), module(new_module) { }

    void operator() (void) const {
      os << "fanged " << module << " [include=path1,path2] <input=file>\n";
    }
  };

  class version_printer {
   private:
    llvm::raw_ostream& os;
    std::string const& module;

   public:
    typedef void result_type;

    version_printer (std::string const& new_module):
      os(llvm::outs()), module(new_module) { }

    void operator() (void) const {
      os << "ariel profiler API - fanged module " << module << "\n\n"
         << "ariel v" << ARIEL_RELEASE
         << " (\"" << ARIEL_CODENAME
         << "\") " << ARIEL_VERSION
         << "\n";
    }
  };

  class add_include {
   private:
    clang::HeaderSearchOptions& opt;

   public:
    template<typename>
    struct result { typedef void type; };

    add_include (clang::CompilerInstance& comp):
      opt(comp.getHeaderSearchOpts()) { }

    void operator() (std::string const& s) const {
      // works like gcc -I./foo 
      const_cast<add_include*>(this)->opt.AddPath(
        llvm::StringRef(s), clang::frontend::Angled, 1, 0, 0
      );
    }
  };

  class add_input {
   private:
    clang::FrontendOptions& opt;

   public:
    template<typename>
    struct result { typedef void type; };

    add_input (clang::CompilerInstance& comp):
      opt(comp.getFrontendOpts()) { }

    void operator() (std::string const& s) const {
      const_cast<add_input*>(this)->opt.Inputs.push_back(
        std::make_pair(clang::IK_CXX, s)
      );
    }
  };
  
  clang::CompilerInstance& comp;

  qi::rule<Iterator>
    start;

  qi::rule<Iterator, std::string(void)>
    include, input, string;

  px::function<help_printer> help;
  px::function<version_printer> version;
  px::function<add_include> include_adder;
  px::function<add_input> input_adder;

  cmdline_grammar (clang::CompilerInstance& new_comp, std::string const& module):
    cmdline_grammar::base_type(start),
    comp(new_comp),
    help(module),
    version(module),
    include_adder(new_comp),
    input_adder(new_comp)
  {
    using boost::spirit::ascii::char_;
    using qi::_val;
    using qi::_1;
    using qi::eps;
    using qi::kwd;
    using qi::lit;

    start %= kwd("help")         [eps[help()]]
           / kwd("version")      [eps[version()]]
           / kwd("include", 0, 1)['=' > +(include >> -lit(','))]
           / kwd("input", 0, 1)  ['=' > input]
    ;

    include %= string[include_adder(_1)];

    input %= string[input_adder(_1)];

    string %= +(char_ - ',');
  }
};

} // cmdline 
} // fanged

#endif // ARIEL_PROFILER_CMDLINE_GRAMMAR_HXX
