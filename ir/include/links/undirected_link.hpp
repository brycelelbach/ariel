// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_IR_UNDIRECTED_LINK_HPP)
#define ARIEL_IR_UNDIRECTED_LINK_HPP

#include "ir/include/links/base_link.hpp"

namespace ariel {
namespace ir {

class undirected_link:
  public base_link<undirected_link>, public static_base_pointer
{
 friend base_link<undirected_link>;

 private:
  static directionality _direction;
};

directionality undirected_link::_direction = UNDIRECTED;

} // ir
} // ariel

#endif // ARIEL_IR_UNDIRECTED_LINK_HPP

