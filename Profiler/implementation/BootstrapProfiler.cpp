// Plugin that allows us to enter libclangSema
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Frontend/CompilerInstance.h"

#include "Profiler/interface/BootstrapProfiler.hpp"

using namespace ariel;

void
BootstrapProfiler::ExecuteAction (void) {
  #if 0
  clang::CompilerInstance& compiler = getCompilerInstance();
  #endif

  // FIXME: Implemente ariel::HotSema
  #if 0
  HotSema sema;
  #endif

  // FIXME: Implement ariel::ApplyHotSeam
  #if 0
  ariel::ApplyHotSema(sema, CI.getFrontendOpts().ShowStats);
  #endif
}

bool
BootstrapProfiler::ParseArgs (
  clang::CompilerInstance const& CI,
  std::vector<std::string> const& args
) {
  // FIXME: implement
  return true;
}

void
BootstrapProfiler::PrintHelp (llvm::raw_ostream& ros) {
  // FIXME: implement
}

clang::ASTConsumer*
BootstrapProfiler::CreateASTConsumer (clang::CompilerInstance&, llvm::StringRef) {
  return new clang::ASTConsumer();
}

static clang::FrontendPluginRegistry::Add<ariel::BootstrapProfiler>
X("arielProfiler", "profile template metaprograms");

