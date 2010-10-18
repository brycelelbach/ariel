//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_ADD_NODE_HXX)
#define ARIEL_PROFILER_ADD_NODE_HXX

#include <clang/AST/AST.h>

#include <boost/type_traits.hpp>

#include <ariel/ir/node.hxx>
#include <ariel/ir/kind.hxx>
#include <ariel/ir/make_link.hxx>
#include <ariel/profiler/filters/get_name.hxx>
#include <ariel/profiler/filters/get_id.hxx>
#include <ariel/utility/call_builder.hxx>

namespace ariel {
namespace profiler {

template<class ASTNode>
struct add_node;

template<>
struct add_node<clang::Type> {
  typedef clang::Type target;

  typedef ir::context::iterator result;

  ARIEL_2ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    boost::add_pointer<target>::type
  );

  ARIEL_2ARY_CALL(ariel_ctx, x);
};

template<>
struct add_node<clang::RecordType> {
  typedef clang::RecordType target;

  typedef ir::context::iterator result;

  ARIEL_2ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    boost::add_pointer<target>::type
  );

  ARIEL_2ARY_CALL(ariel_ctx, x);
};

template<>
struct add_node<clang::ClassTemplateSpecializationDecl> {
  typedef clang::ClassTemplateSpecializationDecl target;

  typedef ir::context::iterator result;

  ARIEL_2ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    boost::add_pointer<target>::type
  );

  ARIEL_2ARY_CALL(ariel_ctx, x);
};

template<>
struct add_node<llvm::APSInt> {
  typedef llvm::APSInt target;

  typedef ir::context::iterator result;

  ARIEL_2ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    boost::add_pointer<boost::add_const<target>::type>::type
  );

  ARIEL_2ARY_CALL(ariel_ctx, x);
};

template<>
struct add_node<clang::PresumedLoc> {
  typedef clang::PresumedLoc target;

  typedef ir::context::iterator result;

  ARIEL_2ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    boost::add_reference<boost::add_const<target>::type>::type
  );

  ARIEL_2ARY_CALL(ariel_ctx, x);
};

} // profiler
} // ariel

#include <ariel/profiler/filters/link_parameters.hxx>
#include <ariel/profiler/filters/link_bases.hxx>
#include <ariel/profiler/filters/link_location.hxx>

namespace ariel {
namespace profiler {

ARIEL_2ARY_CALL_DEF(
  add_node, clang::Type, ariel_ctx, x
) {
  return ariel_ctx.insert(ir::node(
    get_id<target>::call(x),
    get_name<target>::call(x)
  )).first;
}

ARIEL_2ARY_CALL_DEF(
  add_node, clang::RecordType, ariel_ctx, x
) {
  std::pair<ir::context::iterator, bool> r =
    ariel_ctx.insert(ir::node(
      get_id<target>::call(x),
      get_name<target>::call(x)
    ));

  if (r.second == false) return r.first;
  
  ARIEL_IF_NOT_DYN_CAST(clang::CXXRecordDecl, y, x->getDecl()) return r.first;

  link_location<clang::CXXRecordDecl>::call(ariel_ctx, r.first, y);
  link_bases<clang::CXXRecordDecl>::call(ariel_ctx, r.first, y);

  return r.first;
}

ARIEL_2ARY_CALL_DEF(
  add_node, clang::ClassTemplateSpecializationDecl, ariel_ctx, x
) {
  std::pair<ir::context::iterator, bool> r =
    ariel_ctx.insert(ir::node(
      get_id<target>::call(x),
      get_name<target>::call(x)
    ));
  
  if (r.second == false) return r.first;

  link_location<target>::call(ariel_ctx, r.first, x);
  link_parameters<target>::call(ariel_ctx, r.first, x);
  link_bases<target>::call(ariel_ctx, r.first, x);

  return r.first;
}

ARIEL_2ARY_CALL_DEF(
  add_node, llvm::APSInt, ariel_ctx, x
) {
  std::pair<ir::context::iterator, bool> r =
    ariel_ctx.insert(ir::node(
      get_id<target>::call(x),
      get_name<target>::call(x)
    ));

  return r.first;
}

ARIEL_2ARY_CALL_DEF(
  add_node, clang::PresumedLoc, ariel_ctx, x
) {
  std::pair<ir::context::iterator, bool> r =
    ariel_ctx.insert(ir::node(
      get_id<target>::call(x),
      get_name<target>::call(x)
    ));

  return r.first;
}

} // profiler
} // ariel

#endif // ARIEL_PROFILER_ADD_NODE_HXX
