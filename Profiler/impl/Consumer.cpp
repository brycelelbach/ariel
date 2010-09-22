// A template instantiation ASTConsumer for Clang 
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "Profiler/api/Consumer.hpp"

#include "llvm/Support/raw_ostream.h"

#include "PP/poly.hpp"
#include "PP/foreach.hpp"

using namespace ariel;
using namespace ariel::Profiler;

void Consumer::HandleTranslationUnit (clang::ASTContext& ctx) {
  typedef clang::ASTContext::type_iterator iterator;

  ARIEL_FOREACH_LLVM(iterator, it, end, ctx, types_) {
    ARIEL_IF_DYN_CAST(
      clang::RecordType, rec, *it
    ) continue;

    ARIEL_IF_DYN_CAST(
      clang::ClassTemplateSpecializationDecl, decl, rec->getDecl()
    ) continue;
  
    instantiations.GetOrInsertNode(decl);
  }
}


