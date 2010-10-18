//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_IR_KIND_HXX)
#define ARIEL_IR_KIND_HXX

#include <boost/utility/binary.hpp>

namespace ariel {
namespace ir {

enum kind {
  VOID          = BOOST_BINARY(0 0 0 0 0 0 0 0),
  TYPE          = BOOST_BINARY(0 0 0 0 0 0 0 1),
  TEMPLATE      = BOOST_BINARY(0 0 0 0 0 0 1 0),
  CLASS         = BOOST_BINARY(0 0 0 0 0 1 0 0),
  INTEGRAL      = BOOST_BINARY(0 0 0 0 1 0 0 0),
  INSTANTIATED  = BOOST_BINARY(0 0 0 1 0 0 0 0)
};

} // ir
} // ariel

#endif // ARIEL_IR_KIND_HXX
