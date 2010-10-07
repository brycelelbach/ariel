//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

// include by including add_node.hxx
#if !defined(ARIEL_PROFILER_LINK_BASES_HXX) \
    && defined(ARIEL_PROFILER_ADD_NODE_HXX)
#define ARIEL_PROFILER_LINK_BASES_HXX

namespace ariel {
namespace profiler {

template<class ASTNode>
struct link_bases;

template<>
struct link_bases<clang::ClassTemplateSpecializationDecl> {
  typedef clang::ClassTemplateSpecializationDecl target;

  typedef void result;

  ARIEL_3ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    ir::context::iterator,
    boost::add_pointer<target>::type
  );

  ARIEL_3ARY_CALL(ariel_ctx, root, x) {
    if (!x || !x->hasDefinition()) return;

    clang::CXXRecordDecl* def = x->getDefinition();

    if (!def) return; 

    typedef clang::CXXRecordDecl::base_class_iterator iterator;

    iterator b_it  = def->bases_begin(),
             b_end = def->bases_end(),
             v_it  = def->vbases_begin(),
             v_end = def->vbases_end();

    for (; b_it !=  b_end; ++b_it) {
      clang::QualType qual = b_it->getType();

      clang::Type const* type(0);

      // if we can't get a type, give up and move on 
      if (!(type = qual.getTypePtr())) continue;

      // retrieve the canonical type (e.g. record)
      clang::QualType canon = type->getCanonicalTypeInternal();
      
      ARIEL_IF_NOT_DYN_CAST(clang::RecordType, rec, canon.getTypePtr())
        continue;

      ARIEL_IF_NOT_DYN_CAST(target, data, rec->getDecl())
        continue;
      
      ir::make_link<ir::INHERITANCE>::call(
        root, add_node<target>::call(ariel_ctx, data)
      );
    } 

    for (; v_it !=  v_end; ++v_it) {
      clang::QualType qual = v_it->getType();

      clang::Type const* type(0);

      // if we can't get a type, give up and move on 
      if (!(type = qual.getTypePtr())) continue;

      // retrieve the canonical type (e.g. record)
      clang::QualType canon = type->getCanonicalTypeInternal();
      
      ARIEL_IF_NOT_DYN_CAST(clang::RecordType, rec, canon.getTypePtr())
        continue;

      ARIEL_IF_NOT_DYN_CAST(target, data, rec->getDecl())
        continue;
      
      ir::make_link<ir::INHERITANCE>::call(
        root, add_node<target>::call(ariel_ctx, data)
      );
    } 
  }
};

template<>
struct link_bases<clang::CXXRecordDecl> {
  typedef clang::CXXRecordDecl target;

  typedef void result;

  ARIEL_3ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    ir::context::iterator,
    boost::add_pointer<target>::type
  );

  ARIEL_3ARY_CALL(ariel_ctx, root, x) {
    if (!x || !x->hasDefinition()) return;
    
    ARIEL_IF_DYN_CAST(clang::ClassTemplateSpecializationDecl, temp, x)
      link_bases<clang::ClassTemplateSpecializationDecl>::call(
        ariel_ctx, root, temp
      );

    clang::CXXRecordDecl* def = x->getDefinition();

    if (!def) return; 

    typedef clang::CXXRecordDecl::base_class_iterator iterator;

    iterator b_it  = def->bases_begin(),
             b_end = def->bases_end(),
             v_it  = def->vbases_begin(),
             v_end = def->vbases_end();

    for (; b_it !=  b_end; ++b_it) {
      clang::QualType qual = b_it->getType();

      clang::Type const* type(0);

      // if we can't get a type, give up and move on 
      if (!(type = qual.getTypePtr())) continue;

      // retrieve the canonical type (e.g. record)
      clang::QualType canon = type->getCanonicalTypeInternal();
      
      ARIEL_IF_NOT_DYN_CAST(clang::RecordType, data, canon.getTypePtr())
        continue;

      ir::make_link<ir::INHERITANCE>::call(
        root, add_node<clang::RecordType>::call(ariel_ctx, data)
      );
    } 

    for (; v_it !=  v_end; ++v_it) {
      clang::QualType qual = v_it->getType();

      clang::Type const* type(0);

      // if we can't get a type, give up and move on 
      if (!(type = qual.getTypePtr())) continue;

      // retrieve the canonical type (e.g. record)
      clang::QualType canon = type->getCanonicalTypeInternal();
      
      ARIEL_IF_NOT_DYN_CAST(clang::RecordType, data, canon.getTypePtr())
        continue;

      ir::make_link<ir::INHERITANCE>::call(
        root, add_node<clang::RecordType>::call(ariel_ctx, data)
      );
    } 
  }
};
 
} // profiler
} // ariel

#endif // ARIEL_PROFILER_LINK_BASES_HXX
