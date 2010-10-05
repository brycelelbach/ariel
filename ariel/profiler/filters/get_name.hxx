//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_GET_NAME_HXX)
#define ARIEL_PROFILER_GET_NAME_HXX

#include <clang/AST/AST.h>

#include <boost/call_traits.hpp>

namespace ariel {
namespace profiler {

template<class ASTNode>
struct get_name;

template<>
struct get_name<clang::Type> {
  typedef typename boost::call_traits<clang::Type*>::param_type param_type;
  typedef std::string value_type;

  static value_type call (param_type x) {
    if (!x) return "";
    return x->getCanonicalTypeInternal().getAsString();
  }
};

template<>
struct get_name<clang::ClassTemplateSpecializationDecl> {
  typedef typename boost::call_traits<
    clang::ClassTemplateSpecializationDecl*
  >::param_type param_type;
  typedef std::string value_type;

  static value_type call (param_type x) {
    if (!x) return "";
  
    #if 0
    clang::LangOptions LO;
    std::string name;

    x->getNameForDiagnostic(name, clang::PrintingPolicy(LO), true);

    return name;
    #endif

    clang::ClassTemplateDecl* decl = x->getSpecializedTemplate();

    if (!decl) return "";

    return decl->getNameAsString();
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_GET_NAME_HXX
