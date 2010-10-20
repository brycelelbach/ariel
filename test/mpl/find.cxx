//===------------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2001 - 2002 Peter Dimov
// (C) Copyright 2000 - 2004 Aleksey Gurtovoy
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <boost/mpl/find.hpp>
#include <boost/mpl/list.hpp>

#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>

int main (void) {
  using namespace boost;
  using namespace boost::mpl;

  typedef list<int, char, long, short, char, long, double, long>::type types;

  typedef find<types, short >::type result;

  BOOST_ASSERT((is_same<deref<result>::type, short>::value));
}

