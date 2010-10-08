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

#include <boost/type_traits.hpp>

#include <ariel/profiler/filters/filter_builder.hxx>

namespace ariel {
namespace profiler {

template<class ASTNode>
struct get_name;

template<>
struct get_name<clang::Type> {
  typedef clang::Type target;

  typedef std::string result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return "";
    return x->getCanonicalTypeInternal().getAsString();
  }
};

template<>
struct get_name<clang::RecordType> {
  typedef clang::RecordType target;

  typedef std::string result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return "";

    ARIEL_IF_NOT_DYN_CAST(clang::RecordDecl, decl, x->getDecl()) return "";

    return decl->getNameAsString();
  }
};

template<>
struct get_name<clang::ClassTemplateSpecializationDecl> {
  typedef clang::ClassTemplateSpecializationDecl target;

  typedef std::string result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<target>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return "";

    clang::ClassTemplateDecl* decl = x->getSpecializedTemplate();

    if (!decl) return "";

    // FIXME: make nested name specifiers show up
    return decl->getNameAsString();
  }
};

template<>
struct get_name<llvm::APSInt> {
  typedef llvm::APSInt target;

  typedef std::string result;

  ARIEL_1ARY_CALL_PARAMS(
    boost::add_pointer<boost::add_const<target>::type>::type
  );

  ARIEL_1ARY_CALL(x) {
    if (!x) return "";

    return std::string("0x") + x->toString(16);
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_GET_NAME_HXX
