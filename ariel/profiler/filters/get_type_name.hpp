// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_GET_TYPE_NAME_HPP)
#define ARIEL_PROFILER_GET_TYPE_NAME_HPP

#include "clang/AST/ASTContext.h"
#include "clang/AST/AST.h"

#include <boost/call_traits.hpp>

namespace ariel {
namespace profiler {

template<class ASTNode>
struct get_type_name;

template<>
struct get_type_name<clang::Type> {
  typedef typename boost::call_traits<clang::Type*>::param_type param_type;

  static std::string call (param_type type) {
    if (!type) return "";

    return type->getCanonicalTypeInternal().getAsString();
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_GET_TYPE_NAME_HPP
