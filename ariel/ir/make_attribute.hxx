//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_IR_MAKE_ATTRIBUTE_HXX)
#define ARIEL_IR_MAKE_ATTRIBUTE_HXX

#include <ariel/ir/node.hxx>

namespace ariel {
namespace ir {

void make_attribute (
  link::param_type node, std::string const& key, std::string const& val
) {
  (*node).attributes.insert(attributes::value_type(key, val));
}

} // ir 
} // ariel

#endif // ARIEL_IR_MAKE_ATTRIBUTE_HXX
