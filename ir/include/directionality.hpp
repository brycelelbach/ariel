// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_IR_DIRECTIONALITY_HPP)
#define ARIEL_IR_DIRECTIONALITY_HPP

namespace ariel {
namespace ir {

enum directionality {
  // held by a dependent actor; points to a dependency
  UPWARDS,
  // held by a dependent or independent actor; points to an actor who
  // depends on this actor
  DOWNWARDS,
  // held by a dependent or independent actor; indicates a dependency
  // free relationship
  UNDIRECTED
};

} // ir
} // ariel

#endif // ARIEL_IR_DIRECTIONALITY_HPP
