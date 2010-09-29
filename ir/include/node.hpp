// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_IR_NODE_HPP)
#define ARIEL_IR_NODE_HPP

#include "ir/include/links.hpp"

namespace ariel {
namespace ir {

// This IR jazz is pretty simple. Each node corresponds more or less to a
// single node on the clang AST. The node class primarily stores two types
// of information; links to other nodes, and attributes.
//
// Lookup of links and attributes is string based (thus the need for a tst;
// we need a lookup method that will fail lookups of unmapped keys early on).
// This will make coding writer classes easier, as it will just be a matter
// of formatting strings.
//
// Attributes are boost::variants, and can either be strings or integers; the
// rationale for this type limitation is again oriented towards easing the
// creation of writers.
//
// For dot output, C++ node objects will always map to dot nodes, and C++
// directed links will map to dot edges. Undirected links may be represented
// as label data in record-shape dot nodes.

class node {
 public:
  boost::variant<std::string, boost::intmax_t> attribute_type;

  // std::map is a stand-in here until tst hackery is complete
  std::map<std::string, std::set<static_base_pointer*> > link_lookup;
  std::map<std::string, attribute_type> attribute_lookup;

 private:
  link_lookup links;
  attribute_lookup attribute; 
};

} // ir
} // ariel

#endif // ARIEL_IR_NODE_HPP

