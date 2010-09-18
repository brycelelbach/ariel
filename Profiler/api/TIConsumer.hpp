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

namespace ariel {

class TIConsumer:
  public clang::ASTConsumer,
  public clang::RecursiveASTVisitor<TIConsumer>
{
 public:
  virtual void HandleTopLevelDecl (clang::DeclGroupRef ref);

  bool TraverseTemplateName (clang::TemplateName temp);
   
  void TreeifyTemplateName (clang::TemplateName& temp);
  void TreeifyQualifiedTemplateName (clang::QualifiedTemplateName* temp);
  void TreeifyNestedNameSpecifier (clang::NestedNameSpecifier* nss);

  bool shouldVisitTemplateInstantiations (void) const { return true; }
};

} // ariel

#endif // ARIEL_PROFILER_TICONSUMER_HPP
