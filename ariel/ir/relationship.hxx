//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_IR_RELATIONSHIP_HXX)
#define ARIEL_IR_RELATIONSHIP_HXX

#include <boost/utility/binary.hpp>

namespace ariel {
namespace ir {

enum relationship {
  UNRELATED   = BOOST_BINARY(0 0 0 0 0 0 0 0),
  INHERITANCE = BOOST_BINARY(0 0 0 0 0 0 0 1),
  PARAMETRIC  = BOOST_BINARY(0 0 0 0 0 0 1 0),
  MEMBERSHIP  = BOOST_BINARY(0 0 0 0 0 1 0 0)
};

} // ir
} // ariel

#endif // ARIEL_IR_RELATIONSHIP_HXX
