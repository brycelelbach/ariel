// A template instantiation ASTConsumer for Clang 
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_TICONSUMER_HPP)
#define ARIEL_PROFILER_TICONSUMER_HPP

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/DeclTemplate.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/FoldingSet.h"

#include "XML/api/Document.hpp"
#include "XML/api/Tree.hpp"

#include <boost/unordered_map.hpp>

namespace clang {

std::size_t hash_value (TemplateName const& name);

bool operator== (TemplateName const& lhs, TemplateName const& rhs);

} // clang

namespace ariel {

class TIConsumer:
  public clang::ASTConsumer,
  public clang::RecursiveASTVisitor<TIConsumer>
{
 public:
  typedef llvm::ContextualFoldingSet<
    clang::TemplateSpecializationType,
    clang::ASTContext&
  > InstantiationSet;

  typedef boost::unordered_map<
    clang::TemplateName,
    InstantiationSet*
  > TemplateTable;
  
  TIConsumer (std::string name): name(name) { }
  ~TIConsumer (void);

  virtual void HandleTranslationUnit (clang::ASTContext& ctx);
  virtual void HandleTopLevelDecl (clang::DeclGroupRef ref);

  // This is an override for RecursiveASTVisitor, to prevent explicit 
  // specializations from being added to our dataset
  bool TraverseClassTemplateSpecializationDecl (
    clang::ClassTemplateSpecializationDecl* decl
  ) { return true; }

  bool VisitTemplateSpecializationType (
    clang::TemplateSpecializationType* temp
  );
  
  // Tells RecursiveASTVisitor to visit template instantiations
  bool shouldVisitTemplateInstantiations (void) const { return true; }
 
 private:
  const std::string name;
  TemplateTable     templates; 
};

} // ariel

#endif // ARIEL_PROFILER_TICONSUMER_HPP
