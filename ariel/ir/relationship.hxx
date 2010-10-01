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

namespace ariel {
namespace ir {

enum relationship {
  UNRELATED = 0,

  // held by a base or derived class 
  INHERITANCE = 10,

  // held by a template class or template parameter
  PARAMETRIC,

  // held by a class or a member of a class
  MEMBERSHIP
};

} // ir
} // ariel

#endif // ARIEL_IR_RELATIONSHIP_HXX
