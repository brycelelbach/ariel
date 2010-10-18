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
#if !defined(ARIEL_PROFILER_LINK_LOCATION_HXX) \
    && defined(ARIEL_PROFILER_ADD_NODE_HXX)
#define ARIEL_PROFILER_LINK_LOCATION_HXX

namespace ariel {
namespace profiler {

template<class ASTNode>
struct link_location;

template<>
struct link_location<clang::ClassTemplateSpecializationDecl> {
  typedef clang::ClassTemplateSpecializationDecl target;

  typedef void result;

  ARIEL_3ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    ir::context::iterator,
    boost::add_pointer<target>::type
  );

  ARIEL_3ARY_CALL(ariel_ctx, root, x) {
    if (!x) return;

    clang::SourceLocation loc = x->getLocation();

    if (loc.isInvalid()) return;

    clang::PresumedLoc ploc =
      x->getASTContext().getSourceManager().getPresumedLoc(loc);
  
    ir::make_link<ir::INSTANTIATION>::call(
      root, add_node<clang::PresumedLoc>::call(ariel_ctx, ploc)
    );
  }
};

template<>
struct link_location<clang::CXXRecordDecl> {
  typedef clang::CXXRecordDecl target;

  typedef void result;

  ARIEL_3ARY_CALL_PARAMS(
    boost::add_reference<ir::context>::type,
    ir::context::iterator,
    boost::add_pointer<target>::type
  );

  ARIEL_3ARY_CALL(ariel_ctx, root, x) {
    if (!x) return;

    clang::SourceLocation loc = x->getLocation();

    if (loc.isInvalid()) return;
    
    clang::PresumedLoc ploc =
      x->getASTContext().getSourceManager().getPresumedLoc(loc);
  
    ir::make_link<ir::DECLARATION>::call(
      root, add_node<clang::PresumedLoc>::call(ariel_ctx, ploc)
    );
  }
};
 
} // profiler
} // ariel

#endif // ARIEL_PROFILER_LINK_LOCATION_HXX
