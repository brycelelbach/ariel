// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_IR_NODE_HPP)
#define ARIEL_IR_NODE_HPP

#include <map>

#include <boost/cstdint.hpp>
#include <boost/variant/variant.hpp>

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
  typedef boost::variant<std::string, boost::intmax_t> attribute_type;

  // this is possibly better implemented as a llvm::FoldingSet
  typedef std::set<static_base_pointer*> link_set;

  // std::map is a stand-in here until tst hackery is complete
  typedef std::map<std::string, link_set*> link_lookup;
  typedef std::map<std::string, attribute_type> attribute_lookup;

  struct link { }; // link tag for get
  struct attribute { }; // attribute tag for get

 private:
  link_lookup links;
  attribute_lookup attribute;

 public:
  // forward declarations for get
  template<class Tag> link_set* get (std::string const& key);
  template<class Tag> link_set const* get (std::string const& key) const;
  template<class Tag> attribute_type get (std::string const& key);
  template<class Tag> attribute_type const get (std::string const& key) const;
  
  template<>
  link_set* get<link> (std::string const& key) {
    typename link_lookup::iterator it = links.find(key);
  }

  template<>
  link_set const* get<link> (std::string const& key) const {
    typename link_lookup::iterator it = links.find(key);
  }

  template<>
  attribute_type get<attribute> (std::string const& key) {

  }

  template<>
  attribute_type const get<attribute> (std::string const& key) const {

  }
};

} // ir
} // ariel

#endif // ARIEL_IR_NODE_HPP

