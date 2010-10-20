//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2001 - 2002 Peter Dimov
// (C) Copyright 2001 - 2004 Aleksey Gurtovoy
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>

#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>

struct f4 {
  template<typename T1, typename T2, typename T3, typename T4> struct apply {
    typedef T4 type;
  };
};

int main (void) {
  using namespace boost;
  using namespace boost::mpl;

  typedef apply_wrap4<
    bind4<f4, _4, _3, _2, _1>, int, void, void, void
  >::type result;

  BOOST_ASSERT((is_same<result, int>::value));
}

