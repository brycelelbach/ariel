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

#include "XML/api/Document.hpp"
#include "XML/api/Tree.hpp"

namespace ariel {

class TIConsumer:
  public clang::ASTConsumer,
  public clang::RecursiveASTVisitor<TIConsumer>
{
 public:
  TIConsumer (std::string name);

  ~TIConsumer (void);

  virtual void Initialize (clang::ASTContext& ctx);

  virtual void HandleTopLevelDecl (clang::DeclGroupRef ref);

  // This is an override for RecursiveASTVisitor, to prevent explicit 
  // specializations from being added to our dataset
  bool TraverseClassTemplateSpecializationDecl (
    clang::ClassTemplateSpecializationDecl* decl
  ) { return true; }

  bool VisitTemplateSpecializationType (
    const clang::TemplateSpecializationType* temp
  );

  void TreeifyTemplateName (
    clang::TemplateName temp, std::list<XML::Tree>::iterator& parent
  );

  void TreeifyQualifiedTemplateName (
    clang::QualifiedTemplateName* temp, std::list<XML::Tree>::iterator& parent
  );

  void TreeifyNestedNameSpecifier (
    clang::NestedNameSpecifier* nss, std::list<XML::Tree>::iterator& parent
  );

  bool shouldVisitTemplateInstantiations (void) const { return true; }
 
 private:
  XML::Tree tree;
  std::list<XML::Tree>::iterator last;
};

} // ariel

#endif // ARIEL_PROFILER_TICONSUMER_HPP
