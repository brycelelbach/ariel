// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_IR_LINK_HPP)
#define ARIEL_IR_LINK_HPP

#include <list>

#include "ir/include/directionality.hpp"

#include "utility/basic_iterator.hpp"

namespace ariel {
namespace ir {

struct node;

class link: public basic_iterator<std::list<node>::iterator> {
 private:
  directionality _direction;

 public:
  typedef basic_iterator<std::list<node>::iterator> base_type;
  typedef base_type::param_type param_type;

  // STL DefaultConstructible
  link (void): base_type(), _direction(NONE) { } 

  link (param_type new_data, directionality new_direction):
    base_type(new_data), _direction(new_direction) { }

  // STL Assignable
  link (link const& rhs): base_type(rhs), _direction(rhs._direction) { }
  
  // STL Assignable 
  link& operator= (link const& rhs) {
    static_cast<base_type*>(this)->assign(rhs);
    _direction = rhs._direction;
    return *this;
  }

  // alias for operator=
  link& assign (link const& rhs) { 
    static_cast<base_type*>(this)->assign(rhs);
    _direction = rhs._direction;
    return *this;
  }

  directionality direction (void) const { return _direction; }
}; 

} // ir 
} // ariel

#endif // ARIEL_IR_LINK_HPP

