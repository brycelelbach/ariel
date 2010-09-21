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
  static inline clang::TemplateName getEmptyKey (void) {
    return clang::TemplateName::getFromVoidPointer((void*) -1);
  }

  static inline clang::TemplateName getTombstoneKey (void) {
    return clang::TemplateName::getFromVoidPointer((void*) -2);
  }

  static unsigned getHashValue (clang::TemplateName name) {
    clang::TemplateDecl* decl = name.getAsTemplateDecl();
 
    if (!decl) return (uintptr_t) name.getAsVoidPointer();

    clang::ASTContext& ctx = decl->getASTContext();

    clang::TemplateName canon = ctx.getCanonicalTemplateName(name); 

    uintptr_t ptr = (uintptr_t) canon.getAsVoidPointer();

    if (sizeof(unsigned) < sizeof(uintptr_t))
      // hash thought up by michi7x7 from #boost
      return (ptr >> sizeof(unsigned)) ^ (ptr & ((1 << sizeof(unsigned)) - 1));
    else
      return ptr;
  }

  static inline bool isEqual (clang::TemplateName lhs, clang::TemplateName rhs) {
    if (lhs.isNull() || rhs.isNull())
      return lhs.isNull() == rhs.isNull();
    
    clang::TemplateDecl* lhsDecl = lhs.getAsTemplateDecl();
    clang::TemplateDecl* rhsDecl = rhs.getAsTemplateDecl();
 
    if (!lhsDecl || !rhsDecl)
      return lhsDecl == rhsDecl;

    clang::ASTContext& lhsCtx = lhsDecl->getASTContext();
    clang::ASTContext& rhsCtx = rhsDecl->getASTContext();

    return lhsCtx.hasSameTemplateName(
      lhsCtx.getCanonicalTemplateName(lhs),
      lhsCtx.getCanonicalTemplateName(rhs)
    ) && (&lhsCtx == &rhsCtx);
  }
};

template<>
struct isPodLike<clang::TemplateName> { static const bool value = true; };

} // llvm

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
