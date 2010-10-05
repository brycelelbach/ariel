//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_LINK_BASES_HXX)
#define ARIEL_PROFILER_LINK_BASES_HXX

#include <clang/AST/AST.h>

#include <boost/call_traits.hpp>

#include <ariel/ir/node.hxx>
#include <ariel/ir/make_link.hxx>
#include <ariel/utility/llvm.hxx>

namespace ariel {
namespace profiler {

template<class ASTNode, class Filter>
struct link_bases;

template<class Filter>
struct link_bases<clang::ClassTemplateSpecializationDecl, Filter> {
  typedef clang::ClassTemplateSpecializationDecl target_type;
  typedef typename boost::call_traits<target_type*>::param_type param_type;

  typedef clang::CXXRecordDecl::base_class_iterator iterator;

  static void call (
    ir::context& ariel_ctx, ir::context::iterator root, param_type x
  ) {
    if (!x) return;

    iterator b_it  = x->bases_begin(),
             b_end = x->bases_end(),
             v_it  = x->vbases_begin(),
             v_end = x->vbases_end();

    for (; b_it !=  b_end; ++b_it) {
      clang::QualType qual = b_it->getType();

      clang::Type const* type(0);

      // if we can't get a type, give up and move on 
      if (!(type = qual.getTypePtr())) continue;

      // retrieve the canonical type (e.g. record)
      clang::QualType canon = type->getCanonicalTypeInternal();
      
      ARIEL_IF_NOT_DYN_CAST(clang::RecordType, rec, canon.getTypePtr()) continue;
      ARIEL_IF_NOT_DYN_CAST(target_type, decl, rec->getDecl()) continue;
      
      ir::make_link(root, Filter::add(ariel_ctx, decl), ir::INHERITANCE);
    } 

    for (; v_it !=  v_end; ++v_it) {
      clang::QualType qual = v_it->getType();

      clang::Type const* type(0);

      // if we can't get a type, give up and move on 
      if (!(type = qual.getTypePtr())) continue;

      // retrieve the canonical type (e.g. record)
      clang::QualType canon = type->getCanonicalTypeInternal();
      
      ARIEL_IF_NOT_DYN_CAST(clang::RecordType, rec, canon.getTypePtr()) continue;
      ARIEL_IF_NOT_DYN_CAST(target_type, decl, rec->getDecl()) continue;
      
      ir::make_link(root, Filter::add(ariel_ctx, decl), ir::INHERITANCE);
    } 
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_LINK_BASES_HXX
