//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2000 - 2004 Aleksey Gurtovoy
// (C) Copyright 2003 - 2004 David Abrahams
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <boost/mpl/transform.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>

#include <boost/assert.hpp>

int main (void) {
  using namespace boost;
  using namespace boost::mpl;
  
  typedef list_c<long, 0, 2, 4, 6, 8, 10> evens;
  typedef list_c<long, 2, 3, 5, 7, 11, 13> primes;
  typedef list_c<long, 2, 5, 9, 13, 19, 23> sums;

  typedef transform2<evens, primes, plus<> >::type result;
  BOOST_ASSERT((equal<result, sums, equal_to<_1, _2> >::value));
}
