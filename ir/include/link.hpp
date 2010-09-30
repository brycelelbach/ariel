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

#include <boost/integer.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "ir/include/directionality.hpp"
#include "ir/include/relationship.hpp"

#include "utility/basic_iterator.hpp"

namespace ariel {
namespace ir {

struct node;

struct link: public basic_iterator<std::list<node>::iterator> {
 public:
  typedef boost::uint_t<8>::fast metadata; 
  metadata direction;
  metadata relation;

  typedef basic_iterator<std::list<node>::iterator> base_type;
  typedef base_type::param_type param_type;

  // STL DefaultConstructible
  link (void):
    base_type(), direction(DIRECTIONLESS), relation(UNRELATED) { } 

  link (
    param_type new_data,
    directionality new_direction,
    relationship new_relation
  ):
    base_type(new_data), direction(new_direction), relation(new_relation) { }

  // STL Assignable
  link (link const& rhs):
    base_type(rhs), direction(rhs.direction), relation(rhs.relation) { }
  
  // STL Assignable 
  link& operator= (link const& rhs) {
    static_cast<base_type*>(this)->assign(rhs);
    direction = rhs.direction;
    relation = rhs.relation;
    return *this;
  }
}; 

} // ir 
} // ariel

BOOST_FUSION_ADAPT_STRUCT(
  ariel::ir::link,
  (std::list<ariel::ir::node>::iterator, data)
  (ariel::ir::link::metadata, direction)
  (ariel::ir::link::metadata, relation)
)

#endif // ARIEL_IR_LINK_HPP

