//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_GET_ID_HXX)
#define ARIEL_PROFILER_GET_ID_HXX

#include <clang/AST/AST.h>

#include <boost/type_traits.hpp>

#include <ariel/ir/node.hxx>
#include <ariel/ir/kind.hxx>
#include <ariel/profiler/filters/filter_builder.hxx>
#include <ariel/utility/call_builder.hxx>

namespace ariel {
namespace profiler {

template<class ASTNode>
struct get_id;

template<>
struct get_id<clang::Type> {
  typedef clang::Type target;

  typedef ir::unique_id result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return ir::unique_id(ir::TYPE, 0);
    
    typedef llvm::PointerLikeTypeTraits<clang::QualType> traits;
    return ir::unique_id(
      ir::TYPE,
      (std::size_t) traits::getAsVoidPointer(x->getCanonicalTypeInternal())
    );
  }
};

template<>
struct get_id<clang::RecordType> {
  typedef clang::RecordType target;

  typedef ir::unique_id result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return ir::unique_id(ir::CLASS, 0);
    
    typedef llvm::PointerLikeTypeTraits<clang::QualType> traits;
    return ir::unique_id(
      ir::CLASS,
      (std::size_t) traits::getAsVoidPointer(x->getCanonicalTypeInternal())
    );
  }
};

template<>
struct get_id<clang::ClassTemplateSpecializationDecl> {
  typedef clang::ClassTemplateSpecializationDecl target;

  typedef ir::unique_id result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return ir::unique_id(ir::CLASS | ir::TEMPLATE, 0);
    
    llvm::FoldingSetNodeID id;
    x->Profile(id);
    return ir::unique_id(
      ir::CLASS | ir::TEMPLATE |
      (x->getPointOfInstantiation().isValid() ? ir::INSTANTIATED : 0),
      id.ComputeHash()
    );
  }
};

template<>
struct get_id<llvm::APSInt> {
  typedef llvm::APSInt target;

  typedef ir::unique_id result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<boost::add_const<target>::type>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return ir::unique_id(ir::INTEGRAL, 0);
    
    llvm::FoldingSetNodeID id;
    x->Profile(id);
    return ir::unique_id(ir::INTEGRAL, id.ComputeHash());
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_GET_ID_HXX
