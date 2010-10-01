//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_IR_NODE_HXX)
#define ARIEL_IR_NODE_HXX

#include <list>

#include <ariel/ir/link.hxx>

namespace ariel {
namespace ir {

struct node {
 public:
  std::string name;
  // sets don't provide mutable keys; links isn't used for
  // equality/ordering, though, so this is fine for now
  mutable std::list<link> links;

  // STL DefaultConstructible
  node (void): name("node"), links() { }

  node (std::string const& new_name):
    name(new_name), links() { } 
  
  node (std::string const& new_name, std::list<link> const& new_links):
    name(new_name), links(new_links) { } 

  node (link::value_type const& it) {
    *this = *it;
  }

  // STL Assignable
  node (node const& rhs):
    name(rhs.name), links(rhs.links) { } 
 
  // STL Assignable 
  node& operator= (node const& rhs) {
    name = rhs.name;
    links = rhs.links;
    return *this;
  }
  
  // STL EqualityComparable
  bool operator== (node const& rhs) const {
    return (name == rhs.name);
  }

  // STL EqualityComparable
  bool operator!= (node const& rhs) const {
    return (name != rhs.name);
  }

  // STL LessThanComparable
  bool operator< (node const& rhs) const {
    return (name < rhs.name);
  }

  // STL LessThanComparable
  bool operator<= (node const& rhs) const {
    return (name <= rhs.name);
  }

  // STL LessThanComparable
  bool operator> (node const& rhs) const {
    return (name > rhs.name);
  }

  // STL LessThanComparable
  bool operator>= (node const& rhs) const { 
    return (name >= rhs.name);
  }
};

typedef std::set<node> context;

} // ir
} // ariel

BOOST_FUSION_ADAPT_STRUCT(
  ariel::ir::node,
  (std::string, name)
  (std::list<ariel::ir::link>, links)
)

#endif // ARIEL_IR_NODE_HXX

