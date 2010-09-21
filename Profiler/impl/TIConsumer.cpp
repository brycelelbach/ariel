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

TIConsumer::~TIConsumer (void) {
  TemplateTable::iterator tempIt = templates.begin(),
                          tempEnd = templates.end();

  for (; tempIt != tempEnd; ++tempIt) {
    delete (*tempIt).second;
  }
}

void TIConsumer::HandleTranslationUnit (clang::ASTContext& ctx) {
  TemplateTable::iterator tempIt = templates.begin(),
                          tempEnd = templates.end();

  clang::LangOptions LO;
  LO.CPlusPlus = true;
  LO.Bool = true;

  clang::PrintingPolicy policy(LO);

  for (; tempIt != tempEnd; ++tempIt) {
    llvm::outs()
      << (*tempIt).first.getAsTemplateDecl()->getQualifiedNameAsString()
      << " -> " << (*tempIt).second->size() << "\n";
  }
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
  clang::TemplateSpecializationType* temp
) {
  #if defined(ARIEL_ASSERT_NULLS)
    assert(temp && "cannot expand a NULL TemplateSpecializationType*");
  #else
    if (!temp) return false;
  #endif

  clang::TemplateName name = temp->getTemplateName();

  // ignore dependent templates for now
  if (name.isDependent() || name.isNull()) return true;

  TemplateTable::iterator it = templates.find(name),
                               end = templates.end();

  // the template isn't in the table yet
  if (it == end) {
    clang::TemplateDecl* decl = name.getAsTemplateDecl();

    // FIXME: a set of function templates can have a NULL
    // declaration. ATM we don't handle function templates
    // at all, but this would be done by calling name.getKind()
    // (OverloadedTemplate == function template set)
    if (!decl) return true;

    // allocate a new InstantiationSet for this template
    InstantiationSet* set = new InstantiationSet(
      decl->getASTContext()
    );
    
    // insert the instantiation into the set
    set->InsertNode(temp);

    // insert the set into the template table
    templates.insert(TemplateTable::value_type(name, set));
  }

  // the template is in the table
  else
    (*it).second->GetOrInsertNode(temp);

  return true;
}

