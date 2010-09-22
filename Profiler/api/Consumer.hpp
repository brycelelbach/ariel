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

#include "llvm/Support/raw_ostream.h"

#include "PP/poly.hpp"
#include "PP/foreach.hpp"

namespace ariel {
namespace Profiler {

template<typename View>
class Consumer: public clang::ASTConsumer {
 public:
  Consumer (std::string name): name(name) { }
  
  virtual void HandleTranslationUnit (clang::ASTContext& ctx) { 
    #if 0
    typedef clang::ASTContext::type_iterator iterator;
    
    llvm::FoldingSet<clang::ClassTemplateSpecializationDecl>
      instantiations;
    
    ARIEL_FOREACH_LLVM(iterator, it, end, ctx, types_) {
      ARIEL_IF_DYN_CAST(
        clang::RecordType, rec, *it
      ) continue;

      ARIEL_IF_DYN_CAST(
        clang::ClassTemplateSpecializationDecl, decl, rec->getDecl()
      ) continue;
  
      instantiations.GetOrInsertNode(decl);
    }
    #endif

    static_cast<View*>(this)->Process(ctx);
  }

  std::string const& getName (void) const { return name; }

 private:
  std::string const name;
};

class NullView: public Consumer<NullView> {
 public:
  void Process (clang::ASTContext&) { }
};

} // Profiler
} // ariel

#endif // ARIEL_PROFILER_CONSUMER_HPP
