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

TIConsumer::TIConsumer (std::string name):
  tree(name),
  last(tree.end()) { }

TIConsumer::~TIConsumer (void) {
  XML::Document doc(tree, llvm::outs());
  doc.Finalize(); // call this explicitly to shut up unused warnings
}

void TIConsumer::Initialize (clang::ASTContext& ctx) {
  last = tree.addChild("translation-unit");
}

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

bool TIConsumer::VisitTemplateSpecializationType (
  const clang::TemplateSpecializationType* temp
) {
  #if defined(ARIEL_ASSERT_NULLS)
    assert(temp && "cannot expand a NULL TemplateSpecializationType*");
  #else
    if (!temp) return false;
  #endif

  std::list<XML::Tree>::iterator root = last;

  TreeifyTemplateName(temp->getTemplateName(), root);
  
  return true;
}

void TIConsumer::TreeifyTemplateName (
  clang::TemplateName temp, std::list<XML::Tree>::iterator& parent
) {
  switch (temp.getKind()) {
    case clang::TemplateName::Template: {
        parent = (*parent).addChild("template");
        (*parent).addAttribute("name", temp.getAsTemplateDecl()->getNameAsString());
      } break; 
    case clang::TemplateName::OverloadedTemplate: {
        parent = (*parent).addChild("template");
        (*parent).addAttribute("name", temp.getAsTemplateDecl()->getNameAsString());
        (*parent).addAttribute("overloaded", "true");
      } break; 
    case clang::TemplateName::QualifiedTemplate: 
      TreeifyQualifiedTemplateName(temp.getAsQualifiedTemplateName(), parent);
      break;
    case clang::TemplateName::DependentTemplate:
      // ATM the profiler completely ignores dependent contexts
      break;
  }
}

void TIConsumer::TreeifyQualifiedTemplateName (
  clang::QualifiedTemplateName* temp, std::list<XML::Tree>::iterator& parent
) {
  #if defined(ARIEL_ASSERT_NULLS)
    assert(temp && "cannot expand a NULL QualifiedTemplateName*");
  #else
    if (!temp) return;
  #endif

  TreeifyNestedNameSpecifier(temp->getQualifier(), parent);
  
  parent = (*parent).addChild("template");
  (*parent).addAttribute("name", temp->getDecl()->getNameAsString());
  (*parent).addAttribute("qualified", "true");
}

void TIConsumer::TreeifyNestedNameSpecifier (
  clang::NestedNameSpecifier* nss, std::list<XML::Tree>::iterator& parent
) {
  #if defined(ARIEL_ASSERT_NULLS)
    assert(nss && "cannot expand a NULL NestedNameSpecifier*");
  #else
    if (!nss) return;
  #endif

  switch (nss->getKind()) {
    case clang::NestedNameSpecifier::Identifier: { 
        parent = (*parent).addChild("identifier");
        (*parent).addAttribute("name", nss->getAsIdentifier()->getName());
      } break;
    case clang::NestedNameSpecifier::Namespace: {
        parent = (*parent).addChild("namespace");
        (*parent).addAttribute("name", nss->getAsNamespace()->getName());
      } break;
    case clang::NestedNameSpecifier::TypeSpec:
    case clang::NestedNameSpecifier::TypeSpecWithTemplate: { 
        const clang::TemplateSpecializationType* spec = 
          nss->getAsType()->getAs<clang::TemplateSpecializationType>();
        
        if (spec) TreeifyTemplateName(spec->getTemplateName(), parent);

        else { 
          parent = (*parent).addChild("type-specifier");
          (*parent).addAttribute(
            "name", nss->getAsType()->getCanonicalTypeInternal().getAsString()
          );
        }
      } break;
    case clang::NestedNameSpecifier::Global:
      break;
  }
  
  // recurse to end of NestedNameSpecifier
  while ((nss = nss->getPrefix())) { TreeifyNestedNameSpecifier(nss, parent); }
}

