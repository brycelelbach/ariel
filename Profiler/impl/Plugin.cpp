// Clang plugin class for arielProfiler
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "Profiler/api/Plugin.hpp"

#include "clang/Frontend/FrontendPluginRegistry.h"

#include "Profiler/api/Consumer.hpp"

using namespace ariel;
using namespace ariel::Profiler;

clang::ASTConsumer* Plugin::CreateASTConsumer (
  clang::CompilerInstance&, llvm::StringRef string
) {
  return new Consumer(string.data());
}

bool Plugin::ParseArgs (
  clang::CompilerInstance const& compiler,
  std::vector<std::string> const& args
) {
  // FIXME: implement
  return true; 
}

void Plugin::PrintHelp (llvm::raw_ostream& ros) {
  // FIXME: implement
}

static clang::FrontendPluginRegistry::Add<ariel::Profiler::Plugin>
X("arielProfiler", "Build AST and emit XML template instantiation profile");

