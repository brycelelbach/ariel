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

#include <vector>

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

typedef std::vector<link> link_collection;

struct node {
 public:
  unique_id   id;
  std::string name;

  mutable link_collection parameters, bases, members;

 private:
  // shared implementation details for Assignable and DefaultConstructible 
  void copy (node const& rhs) {
    id = rhs.id;
    name = rhs.name;
    parameters = rhs.parameters;
    bases = rhs.bases;
    members = rhs.members;
  }

 public:
  // STL DefaultConstructible
  node (void): id(0, 0), name("null") { }

  node (unique_id new_id, std::string new_name): id(new_id), name(new_name) { } 

  node (link::value_type const& it) { copy(*it); }

  // STL Assignable
  node (node const& rhs) { copy(rhs); }

  // STL EqualityComparable
  #define M0(_)                                                       \
    bool operator _ (node const& rhs) const { return (id _ rhs.id); } \
    /**/

  M0(==)
  M0(!=)

  #undef M0

  // STL Assignable 
  node& operator= (node const& rhs) {
    if (*this != rhs) copy(rhs);
    return *this;
  }
};

std::size_t hash_value (node const& n) {
  boost::hash<std::string> hasher; return hasher(n.name);
}

typedef boost::unordered_set<node> context;

} // ir
} // ariel

BOOST_FUSION_ADAPT_STRUCT(
  ariel::ir::node,
  (ariel::ir::unique_id, id)
  (std::string, name)
  (ariel::ir::link_collection, parameters)
  (ariel::ir::link_collection, bases)
  (ariel::ir::link_collection, members)
)

#endif // ARIEL_IR_NODE_HXX

