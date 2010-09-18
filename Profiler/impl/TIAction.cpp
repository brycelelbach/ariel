// Clang plugin class for arielProfiler
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "Profiler/api/TIAction.hpp"

#include "clang/Frontend/FrontendPluginRegistry.h"

#include "Profiler/api/TIConsumer.hpp"

using namespace ariel;

clang::ASTConsumer* TIAction::CreateASTConsumer (
  clang::CompilerInstance&, llvm::StringRef
) {
  return new TIConsumer();
}

bool TIAction::ParseArgs (
  clang::CompilerInstance const& compiler,
  std::vector<std::string> const& args
) {
  // FIXME: implement
  return true; 
}

void TIAction::PrintHelp (llvm::raw_ostream& ros) {
  // FIXME: implement
}

static clang::FrontendPluginRegistry::Add<ariel::TIAction>
X("arielProfiler", "Build AST and emit XML template instantiation profile");

