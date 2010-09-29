// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_IR_BASE_LINK_HPP)
#define ARIEL_IR_BASE_LINK_HPP

#include "ir/include/directionality.hpp"

namespace ariel {
namespace ir {

template<class Derived>
class base_link {
  directionality direction (void) const {
    return static_cast<Derived*>(this)->_direction;
  }
};

} // ir
} // ariel

#endif // ARIEL_IR_BASE_LINK_HPP

