//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_LINK_CHILDREN_HXX)
#define ARIEL_PROFILER_LINK_CHILDREN_HXX

#include <clang/AST/AST.h>

#include <boost/call_traits.hpp>

#include <ariel/ir/node.hxx>
#include <ariel/ir/make_link.hxx>
#include <ariel/utility/llvm.hxx>

namespace ariel {
namespace profiler {

template<class ASTNode, class Filter>
struct link_children;

template<class Filter>
struct link_children<clang::ClassTemplateSpecializationDecl, Filter> {
  typedef clang::ClassTemplateSpecializationDecl target_type;
  typedef typename boost::call_traits<target_type*>::param_type param_type;

  static void call (
    ir::context& ariel_ctx, ir::context::iterator root, param_type x
  ) {
    clang::TemplateArgument const* args = x->getTemplateArgs().getFlatArgumentList();

    if (args) {
      for (unsigned i = 0, end = x->getTemplateArgs().flat_size(); i < end; ++i) {
        switch (args[i].getKind()) {
          case clang::TemplateArgument::Type: {
            clang::QualType qual = args[i].getAsType();
            
            ARIEL_IF_NOT_DYN_CAST(clang::RecordType, rec, qual.getTypePtr()) break;
            ARIEL_IF_NOT_DYN_CAST(target_type, decl, rec->getDecl()) break;
            
            ir::make_link(root, Filter::add(ariel_ctx, decl), ir::PARAMETRIC);
          } break;
          default: break; 
        }
      }
    }
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_LINK_CHILDREN_HXX
