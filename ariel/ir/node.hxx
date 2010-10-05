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

#include <map>
#include <list>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/include/comparison.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <ariel/ir/kind.hxx>
#include <ariel/ir/link.hxx>

namespace ariel {

namespace fusion = boost::fusion;

namespace ir {

// first integral contains the kind, second contains the hash
typedef fusion::vector2<std::size_t, std::size_t> unique_id; 

struct node {
 public:
  unique_id id;
  // temporary use of map until tst has been tested more extensively
  mutable std::map<std::string, std::string> attributes;
  // sets don't provide mutable keys; links isn't used for
  // equality/ordering, though, so this is fine for now
  mutable std::list<link> links;

  // STL DefaultConstructible
  node (void): id(), attributes(), links() { }

  node (unique_id new_id): id(new_id), links() { } 

  node (link::value_type const& it): id() {
    id = (*it).id;
    attributes = (*it).attributes;
    links = (*it).links;
  }

  // STL Assignable
  node (node const& rhs):
    id(rhs.id), attributes(rhs.attributes), links(rhs.links) { } 

  // STL EqualityComparable
  bool operator== (node const& rhs) const { return (id == rhs.id); }
  bool operator!= (node const& rhs) const { return (id != rhs.id); }

  // STL LessThanComparable
  bool operator< (node const& rhs) const { return (id < rhs.id); }
  bool operator<= (node const& rhs) const { return (id <= rhs.id); }
  bool operator> (node const& rhs) const { return (id > rhs.id); }
  bool operator>= (node const& rhs) const { return (id >= rhs.id); }
 
  // STL Assignable 
  node& operator= (node const& rhs) {
    if (*this == rhs) {
      id = rhs.id;
      attributes = rhs.attributes;
      links = rhs.links;
    }
    return *this;
  }
};

typedef std::set<node> context;

typedef std::map<std::string, std::string> attributes;

} // ir
} // ariel

BOOST_FUSION_ADAPT_STRUCT(
  ariel::ir::node,
  (ariel::ir::unique_id, id)
  (ariel::ir::attributes, attributes)
  (std::list<ariel::ir::link>, links)
)

#endif // ARIEL_IR_NODE_HXX

