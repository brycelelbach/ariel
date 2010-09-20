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

TIConsumer::TIConsumer (std::string name): tree() {
  #if 0
  XML::Tree root(name);
  tree.push_back(name);
  #endif
}

TIConsumer::~TIConsumer (void) {
  TemplateTable::iterator tempIt = templates.begin(),
                          tempEnd = templates.end();

  do {
    delete (*tempIt).second;
  } while (++tempIt != tempEnd);
}

void TIConsumer::HandleTranslationUnit (clang::ASTContext&) {
  #if 0
  XML::Document doc(tree.front(), llvm::outs());
  doc.Finalize(); // call this explicitly to shut up unused warnings
  #endif
  TemplateTable::iterator tempIt = templates.begin(),
                          tempEnd = templates.end();

  do {
    (*tempIt).first.dump();
    llvm::outs() << " -> " << (*tempIt).second->size() << "\n";
  } while (++tempIt != tempEnd);
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

  #if 0
  std::list<XML::Tree>::iterator root = tree.begin();

  TreeifyTemplateName(temp->getTemplateName(), root);
  TreeifyTemplateArguments(temp->getArgs(), temp->getNumArgs(), root);
  #endif 

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
        const clang::TemplateSpecializationType* temp = 
          nss->getAsType()->getAs<clang::TemplateSpecializationType>();
        
        if (temp) {
          TreeifyTemplateName(temp->getTemplateName(), parent);
          TreeifyTemplateArguments(temp->getArgs(), temp->getNumArgs(), parent);
        }

        else {
          parent = (*parent).addChild("type");
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

void TIConsumer::TreeifyTemplateArguments (
  const clang::TemplateArgument* args, unsigned arity,
  std::list<XML::Tree>::iterator& parent
) {
  std::list<XML::Tree>::iterator root = parent;
  
  root = (*root).addChild("parameters");

  for (unsigned i = 0; i < arity; ++i) {
    switch (args[i].getKind()) {
      case clang::TemplateArgument::Null: {
          root = (*root).addChild("null");
        } break;
      case clang::TemplateArgument::Type: {
          root = (*root).addChild("type");
          (*root).addAttribute(
            "name", args[i].getAsType()->getCanonicalTypeInternal().getAsString()
          );
        } break;
      // FIXME: implement
      case clang::TemplateArgument::Declaration: {
          root = (*root).addChild("declaration");
        } break;
      case clang::TemplateArgument::Integral: {
          root = (*root).addChild("integral");
          (*root).addAttribute("value", args[i].getAsIntegral()->toString(10));
        } break;
      case clang::TemplateArgument::Template: {
          root = (*root).addChild("template");
        } break;
      case clang::TemplateArgument::Expression: {
          root = (*root).addChild("expression");
        } break;
      case clang::TemplateArgument::Pack: {
          root = (*root).addChild("parameter-pack");
        } break;
    }
  }
}
