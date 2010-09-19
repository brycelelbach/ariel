// Clang plugin class for arielProfiler
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_TIACTION_HPP)
#define ARIEL_PROFILER_TIACTION_HPP

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"
#include "clang/Frontend/CompilerInstance.h"

#include "llvm/Support/raw_ostream.h"

namespace ariel {

class TIAction: public clang::PluginASTAction {
 protected:
  clang::ASTConsumer* CreateASTConsumer (
    clang::CompilerInstance& compiler,
    llvm::StringRef string
  ); 

  bool ParseArgs (
    clang::CompilerInstance const& compiler,
    std::vector<std::string> const& args
  );
 
  void PrintHelp (llvm::raw_ostream& ros);
};

} // ariel 

#endif // ARIEL_PROFILER_TIACTION_HPP
