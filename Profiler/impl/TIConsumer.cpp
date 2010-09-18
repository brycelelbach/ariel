// A template instantiation ASTConsumer for Clang 
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "Profiler/api/TIConsumer.hpp"

#include "llvm/Support/raw_ostream.h"

using namespace ariel;

void TIConsumer::HandleTopLevelDecl (clang::DeclGroupRef ref) {
  if (ref.isNull()) return; // ignore nulls

  if (ref.isSingleDecl()) {
    TraverseDecl(ref.getSingleDecl());
    return;
  }

  if (ref.isDeclGroup()) {
    clang::DeclGroup& group = ref.getDeclGroup();

    for (unsigned it = 0, end = group.size(); it < end; ++it)
      TraverseDecl(group[it]);
  }
}

bool TIConsumer::TraverseTemplateName (clang::TemplateName temp) {
  TreeifyTemplateName(temp); // add the instantiation to the XML tree IR
  
  return true;
}

void TIConsumer::TreeifyTemplateName (clang::TemplateName& temp) {
  switch (temp.getKind()) {
    case clang::TemplateName::Template:
    case clang::TemplateName::OverloadedTemplate: 
      // FIXME: push to XML tree IR here
      llvm::outs() << temp.getAsTemplateDecl()->getNameAsString() << "\n";
      return; 
    case clang::TemplateName::QualifiedTemplate: 
      TreeifyQualifiedTemplateName(temp.getAsQualifiedTemplateName());
      return;
    case clang::TemplateName::DependentTemplate:
      // ATM the profiler completely ignores dependent contexts
      return;
  }
}

void TIConsumer::TreeifyQualifiedTemplateName (clang::QualifiedTemplateName* temp) {
  #if defined(ARIEL_ASSERT_NULLS)
    assert(temp && "cannot expand a NULL QualifiedTemplateName*");
  #else
    if (!temp) return;
  #endif

  TreeifyNestedNameSpecifier(temp->getQualifier());
  
  // FIXME: push to XML tree IR here
  llvm::outs() << temp->getDecl()->getNameAsString() << "\n";
}

void TIConsumer::TreeifyNestedNameSpecifier (clang::NestedNameSpecifier* nss) {
  #if defined(ARIEL_ASSERT_NULLS)
    assert(nss && "cannot expand a NULL NestedNameSpecifier*");
  #else
    if (!nss) return;
  #endif

  switch (nss->getKind()) {
    case clang::NestedNameSpecifier::Identifier: 
      // FIXME: push to XML tree IR here
      llvm::outs() << nss->getAsIdentifier()->getName() << "\n";
      break;
    case clang::NestedNameSpecifier::Namespace:
      // FIXME: push to XML tree IR here
      llvm::outs() << nss->getAsNamespace()->getName() << "\n";      
      break;
    case clang::NestedNameSpecifier::TypeSpec:
    case clang::NestedNameSpecifier::TypeSpecWithTemplate: 
      // FIXME: push to XML tree IR here
      llvm::outs() << nss->getAsType()->getCanonicalTypeInternal().getAsString() << "\n";
      break;
    case clang::NestedNameSpecifier::Global:
      break;
  }
  
  // recurse to end of NestedNameSpecifier
  while ((nss = nss->getPrefix())) { TreeifyNestedNameSpecifier(nss); } 
}

