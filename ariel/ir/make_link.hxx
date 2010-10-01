//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_IR_MAKE_LINK_HXX)
#define ARIEL_IR_MAKE_LINK_HXX

#include <ariel/ir/node.hxx>

namespace ariel {
namespace ir {

link& make_link (
  link::param_type from, link::param_type to, relationship relation
) {
  (*from).links.push_back(link(from, to, relation));

  return (*from).links.back();
}

} // ir 
} // ariel

#endif // ARIEL_IR_MAKE_LINK_HXX
