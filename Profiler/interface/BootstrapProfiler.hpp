// Plugin that allows us to enter libclangSema
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_BOOTSTRAP_PROFILER_HPP)
#define ARIEL_PROFILER_BOOTSTRAP_PROFILER_HPP

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"

#include "llvm/Support/raw_ostream.h"

namespace ariel {

class HotSema;

// BootstrapProfiler is our primary entrance into the clang
// compiler. 
//
// Originally, I used a typical implementation of a Clang plugin.
// This limited me to a set of predefined hooks mostly in 
// libclangAST. I could have gotten the job done this way,
// but it would've been kludgy. Templates are not instantiated
// in libclangAST, they are instantiated by the class clang::Sema
// in libclangSema, during semantic analysis.
//
// It is much cleaner to overload the virtual member function
// ASTFrontendAction::ExecuteAction through the plugin, and
// "install" our own semantic analysis class, ariel::HotSema
// (derived from clang::Sema, adds hooks into instantiation
// of templates and changes nothing else)
//
// Because the functions I am hooking into in clang::Sema are
// not virtual, I have to basically copy and paste a few modules
// from clang's API; not having to change anything in Clang itself
//
// inheritance hierarchy (CLANGDIR/Frontend/FrontendAction.h)
//
//   clang::FrontendAction
//             ^^
//             ||
//  clang::ASTFrontendAction
//             ^^
//             ||
//   clang::PluginASTAction
//             ^^
//             ||
//  ariel::BootstrapProfiler
 
class BootstrapProfiler: public clang::PluginASTAction {
 protected:
  // Basically, calls ariel::ApplyHotSema (our equivalent of
  // clang::ParseAST)
  virtual void
  ExecuteAction (void);

  // Read arguments given on the command line for the plugin
  virtual bool
  ParseArgs (
    clang::CompilerInstance const& compiler,
    std::vector<std::string> const& args
  );

  // Print help for the plugin
  virtual void
  PrintHelp (llvm::raw_ostream& ros);

  // clang::PluginASTAction is an abstract base class, so
  // we need to define this even though we're not using it.
  virtual clang::ASTConsumer*
  CreateASTConsumer (clang::CompilerInstance&, llvm::StringRef);
};

} // ariel

#endif // ARIEL_PROFILER_BOOTSTRAP_PROFILER_HPP

