// clang plugin class for arielProfiler
//
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

#include "Profiler/api/Consumer.hpp"

namespace ariel {
namespace Profiler {

template<typename View>
class Plugin: public clang::PluginASTAction {
 protected:
  clang::ASTConsumer* CreateASTConsumer (
    clang::CompilerInstance& compiler,
    llvm::StringRef string
  ) {
    return new Consumer<View>(string.data());
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

} // Profiler
} // ariel 

#endif // ARIEL_PROFILER_PLUGIN_HPP
