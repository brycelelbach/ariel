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

#include <ariel/profiler/filters/filter_builder.hxx>

namespace ariel {
namespace profiler {

template<class ASTNode>
struct get_id;

template<>
struct get_id<clang::Type> {
  typedef clang::Type target;

  typedef std::size_t result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return 0;
    
    typedef llvm::PointerLikeTypeTraits<clang::QualType> traits;
    return (result) traits::getAsVoidPointer(x->getCanonicalTypeInternal());
  }
};

template<>
struct get_id<clang::RecordType> {
  typedef clang::RecordType target;

  typedef std::size_t result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return 0;
    
    typedef llvm::PointerLikeTypeTraits<clang::QualType> traits;
    return (result) traits::getAsVoidPointer(x->getCanonicalTypeInternal());
  }
};

template<>
struct get_id<clang::ClassTemplateSpecializationDecl> {
  typedef clang::ClassTemplateSpecializationDecl target;

  typedef std::size_t result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return 0;
    
    llvm::FoldingSetNodeID id;
    x->Profile(id);
    return id.ComputeHash();
  }
};

template<>
struct get_id<llvm::APSInt> {
  typedef llvm::APSInt target;

  typedef std::size_t result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<boost::add_const<target>::type>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return 0;
    
    llvm::FoldingSetNodeID id;
    x->Profile(id);
    return id.ComputeHash();
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_GET_ID_HXX
