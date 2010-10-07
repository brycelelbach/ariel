//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_IR_MAKE_LINK_HXX)
#define ARIEL_IR_MAKE_LINK_HXX

#include <boost/mpl/int.hpp>

#include <ariel/utility/call_builder.hxx>
#include <ariel/ir/node.hxx>

namespace ariel {
namespace ir {

template<relationship Relation>
struct make_link;

template<>
struct make_link<INHERITANCE> {
  typedef boost::mpl::int_<INHERITANCE> target;
  typedef boost::add_reference<link>::type result;

  ARIEL_2ARY_CALL_PARAMS(link::param_type, link::param_type);

  ARIEL_2ARY_CALL(from_it, to_it) {
    node const& from = *from_it;
    from.bases.push_back(link(from_it, to_it, INHERITANCE));
    return from.bases.back();
  }
};

template<>
struct make_link<PARAMETRIC> {
  typedef boost::mpl::int_<PARAMETRIC> target;
  typedef boost::add_reference<link>::type result;

  ARIEL_2ARY_CALL_PARAMS(link::param_type, link::param_type);

  ARIEL_2ARY_CALL(from_it, to_it) {
    node const& from = *from_it;
    from.bases.push_back(link(from_it, to_it, PARAMETRIC));
    return from.bases.back();
  }
};

template<>
struct make_link<MEMBERSHIP> {
  typedef boost::mpl::int_<MEMBERSHIP> target;
  typedef boost::add_reference<link>::type result;

  ARIEL_2ARY_CALL_PARAMS(link::param_type, link::param_type);

  ARIEL_2ARY_CALL(from_it, to_it) {
    node const& from = *from_it;
    from.bases.push_back(link(from_it, to_it, MEMBERSHIP));
    return from.bases.back();
  }
};

} // ir 
} // ariel

#endif // ARIEL_IR_MAKE_LINK_HXX
