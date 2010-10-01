//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_IR_LINK_HXX)
#define ARIEL_IR_LINK_HXX

#include <set>

#include <boost/call_traits.hpp>
#include <boost/integer.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <ariel/ir/relationship.hxx>

namespace ariel {
namespace ir {

struct node;

struct link {
 public:
  typedef boost::uint_t<8>::fast metadata; 
  typedef std::set<node>::iterator value_type;
  typedef boost::call_traits<value_type>::param_type param_type;

  value_type from;
  value_type to;
  metadata relation;

  // STL DefaultConstructible
  link (void): from(), to(), relation(UNRELATED) { } 

  link (param_type new_from, param_type new_to, relationship new_relation):
    from(new_from), to(new_to), relation(new_relation) { }

  // STL Assignable
  link (link const& rhs): from(rhs.from), to(rhs.to), relation(rhs.relation) { }
  
  // STL Assignable 
  link& operator= (link const& rhs) {
    from = rhs.from;
    to = rhs.to; 
    relation = rhs.relation;
    return *this;
  }

  bool operator== (link const& rhs) const {
    return (from == rhs.from) && (to == rhs.to) && (relation == rhs.relation);
  }
  
  bool operator!= (link const& rhs) const {
    return (from != rhs.from) && (to != rhs.to) && (relation != rhs.relation);
  }
}; 

} // ir 
} // ariel

BOOST_FUSION_ADAPT_STRUCT(
  ariel::ir::link,
  (ariel::ir::link::value_type, from)
  (ariel::ir::link::value_type, to)
  (ariel::ir::link::metadata, relation)
)

#endif // ARIEL_IR_LINK_HXX

