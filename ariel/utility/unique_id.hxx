//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_UNIQUE_ID_HXX)
  #define ARIEL_UNIQUE_ID_HXX
  #include <boost/preprocessor/slot/counter.hpp>
#endif // ARIEL_UNIQUE_ID_HXX

// begin vertical repetition

#define ARIEL_UNIQUE_ID 0x10 + BOOST_PP_COUNTER
#include BOOST_PP_UPDATE_COUNTER()

// end vertical repetition

