//===------------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2000 - 2004 Aleksey Gurtovoy
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>

#include <boost/assert.hpp>

int main (void) {
  using namespace boost;
  using namespace boost::mpl;

  typedef list_c<int, 5, -1, 0, -7, -2, 0, -5, 4> numbers;
  typedef list_c<int, -1, -7, -2, -5> negatives;

  typedef reverse_fold<
    numbers, list_c<int>, if_<less<_2, int_<0> >, push_front<_1, _2 >, _1>
  >::type result;

  BOOST_ASSERT((equal<result, negatives, equal_to<_1, _2> >::value));
}

