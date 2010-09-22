// A template profiler implemented as an ASTConsumer for Clang 
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_CONSUMER_HPP)
#define ARIEL_PROFILER_CONSUMER_HPP

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"

namespace ariel {
namespace Profiler {

class Consumer: public clang::ASTConsumer {
 public:
  typedef llvm::FoldingSet<
    clang::ClassTemplateSpecializationDecl
  > InstantiationSet;
  
  Consumer (std::string name): name(name) { }

  virtual void HandleTranslationUnit (clang::ASTContext& ctx);
  
 private:
  const std::string name;
  InstantiationSet  instantiations;
};

} // Profiler
} // ariel

#endif // ARIEL_PROFILER_CONSUMER_HPP
