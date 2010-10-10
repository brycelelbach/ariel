//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_MODULE_HXX)
#define ARIEL_PROFILER_MODULE_HXX

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/AST.h>
#include <clang/Frontend/CompilerInstance.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/ErrorHandling.h>

#include <ariel/profiler/consumer.hxx>
#include <ariel/profiler/grammar/cmdline.hxx>

#include <fanged/module_action.hxx>

namespace ariel {
namespace profiler {

template<class Production>
class module: public fanged::module_action {
 protected:
  clang::ASTConsumer* CreateASTConsumer (
    clang::CompilerInstance& cc,
    llvm::StringRef file
  ) {
    Production* prod = new Production();
    prod->set_name(file);
    return prod;
  }

 public:
  virtual void parse_args (clang::CompilerInstance& cc) {
    std::vector<std::string> const& av = cc.getFrontendOpts().PluginArgs;
    std::vector<std::string>::size_type const ac = av.size();

    if (ac < 1) llvm::report_fatal_error("module argument vector is empty");

    cmdline_grammar<std::string::iterator> grammar(cc, av[0]);

    // process the command line arguments
    for (unsigned i = 1; i < ac; ++i) {
      // create a temporary string, because karma::parse requires a mutable
      // iterator to work on, and we don't want to mutate av
      std::string arg(av[i]);

      std::string::iterator it = arg.begin();

      if (!qi::parse(it, arg.end(), grammar) || (it != arg.end())) 
        llvm::report_fatal_error(
          std::string("module couldn't parse command line argument \"")
              .append(av[i]).append("\"")
        );
    }
  }
};

} // profiler
} // ariel 

#endif // ARIEL_PROFILER_MODULE_HXX
