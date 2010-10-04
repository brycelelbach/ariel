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

#include <boost/cstdint.hpp>
#include <boost/call_traits.hpp>

namespace ariel {
namespace profiler {

template<class ASTNode>
struct get_id;

template<>
struct get_id<clang::Type> {
  typedef typename boost::call_traits<clang::Type*>::param_type param_type;
  typedef std::size_t value_type;

  static value_type call (param_type x) {
    if (!x) return 0;
    
    typedef llvm::PointerLikeTypeTraits<clang::QualType> traits;
    return (value_type) traits::getAsVoidPointer(x->getCanonicalTypeInternal());
  }
};

template<>
struct get_id<clang::ClassTemplateSpecializationDecl> {
  typedef typename boost::call_traits<
    clang::ClassTemplateSpecializationDecl*
  >::param_type param_type;
  typedef std::size_t value_type;

  static value_type call (param_type x) {
    if (!x) return 0;
    
    llvm::FoldingSetNodeID id;
    x->Profile(id);
    return id.ComputeHash();
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_GET_ID_HXX
