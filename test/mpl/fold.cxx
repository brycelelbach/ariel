//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2000 - 2004 Aleksey Gurtovoy
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <boost/mpl/fold.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>

#include <boost/assert.hpp>
#include <boost/type_traits/is_float.hpp>

int main (void) {
  using namespace boost;
  using namespace boost::mpl;

  typedef list<long, float, short, double, float, long, long double> types;

  typedef fold<types, int_<0>, if_<is_float<_2>, next<_1>, _1> >::type result;

  BOOST_ASSERT(result::value == 4);
}

