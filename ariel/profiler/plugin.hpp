// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_PLUGIN_HPP)
#define ARIEL_PROFILER_PLUGIN_HPP

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"
#include "clang/Frontend/CompilerInstance.h"

#include "llvm/Support/raw_ostream.h"

#include "profiler/include/consumer.hpp"

namespace ariel {
namespace profiler {

template<class Production>
class plugin: public clang::PluginASTAction {
 protected:
  clang::ASTConsumer* CreateASTConsumer (
    clang::CompilerInstance& compiler,
    llvm::StringRef name
  ) {
    Production* prod = new Production();
    prod->set_name(name);
    return prod;
  }

  bool ParseArgs (
    clang::CompilerInstance const& compiler,
    std::vector<std::string> const& args
  ) {
    // FIXME: implement
    return true;
  }
 
  void PrintHelp (llvm::raw_ostream& out) {
    // FIXME: implement
  }
};

} // profiler
} // ariel 

#endif // ARIEL_PROFILER_PLUGIN_HPP
