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

namespace llvm {

template<>
struct DenseMapInfo<clang::TemplateName> {
  static inline clang::TemplateName getEmptyKey() {
    return clang::TemplateName::getFromVoidPointer((void*) -1);
  }

  static inline clang::TemplateName getTombstoneKey() {
    return clang::TemplateName::getFromVoidPointer((void*) -2);
  }

  static unsigned getHashValue (clang::TemplateName OP) {
    return (uintptr_t) OP.getAsVoidPointer();
  }

  static inline bool
  isEqual(clang::TemplateName LHS, clang::TemplateName RHS) {
    return LHS.getAsVoidPointer() == RHS.getAsVoidPointer();
  }
};

template <>
struct isPodLike<clang::TemplateName> { static const bool value = true; };

}  // llvm

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

  typedef llvm::DenseMap<
    clang::TemplateName,
    InstantiationSet*
  > TemplateTable;
  
  TIConsumer (std::string name);
  ~TIConsumer (void);

  virtual void HandleTranslationUnit (clang::ASTContext&);
  virtual void HandleTopLevelDecl (clang::DeclGroupRef ref);

  // This is an override for RecursiveASTVisitor, to prevent explicit 
  // specializations from being added to our dataset
  bool TraverseClassTemplateSpecializationDecl (
    clang::ClassTemplateSpecializationDecl* decl
  ) { return true; }

  bool VisitTemplateSpecializationType (
    clang::TemplateSpecializationType* temp
  );

  // XML tree builder member functions
  void TreeifyTemplateName (
    clang::TemplateName temp, std::list<XML::Tree>::iterator& parent
  );

  void TreeifyQualifiedTemplateName (
    clang::QualifiedTemplateName* temp, std::list<XML::Tree>::iterator& parent
  );

  void TreeifyNestedNameSpecifier (
    clang::NestedNameSpecifier* nss, std::list<XML::Tree>::iterator& parent
  );

  void TreeifyTemplateArguments (
    const clang::TemplateArgument* args, unsigned arity,
    std::list<XML::Tree>::iterator& parent
  );
  
  // Tells RecursiveASTVisitor to visit template instantiations
  bool shouldVisitTemplateInstantiations (void) const { return true; }
 
 private:
  TemplateTable        templates; 
  std::list<XML::Tree> tree;
};

} // ariel

#endif // ARIEL_PROFILER_TICONSUMER_HPP
