//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_CALL_BUILDER_HXX)
#define ARIEL_CALL_BUILDER_HXX

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

// FIXME: this all could be done with Boost.PP in less LOC

#define ARIEL_1ARY_CALL_PARAMS(_0)                                \
  typedef boost::fusion::vector1<_0> parameters                   \
  /**/

#define ARIEL_2ARY_CALL_PARAMS(_0, _1)                            \
  typedef boost::fusion::vector2<_0, _1> parameters               \
  /**/

#define ARIEL_3ARY_CALL_PARAMS(_0, _1, _2)                        \
  typedef boost::fusion::vector3<_0, _1, _2> parameters           \
  /**/

#define ARIEL_4ARY_CALL_PARAMS(_0, _1, _2, _3)                    \
  typedef boost::fusion::vector4<_0, _1, _2, _3> parameters       \
  /**/

#define ARIEL_5ARY_CALL_PARAMS(_0, _1, _2, _3, _4)                \
  typedef boost::fusion::vector5<_0, _1, _2, _3, _4> parameters   \
  /**/

#define ARIEL_1ARY_CALL(_0)                                 \
  static result call (                                      \
    boost::fusion::result_of::at_c<parameters, 0>::type _0  \
  )                                                         \
  /**/

#define ARIEL_2ARY_CALL(_0, _1)                             \
  static result call (                                      \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1  \
  )                                                         \
  /**/

#define ARIEL_3ARY_CALL(_0, _1, _2)                         \
  static result call (                                      \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1, \
    boost::fusion::result_of::at_c<parameters, 2>::type _2  \
  )                                                         \
  /**/

#define ARIEL_4ARY_CALL(_0, _1, _2, _3)                     \
  static result call (                                      \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1  \
    boost::fusion::result_of::at_c<parameters, 2>::type _2, \
    boost::fusion::result_of::at_c<parameters, 3>::type _3  \
  )                                                         \
  /**/

#define ARIEL_5ARY_CALL(_0, _1, _2, _3, _4)                 \
  static result call (                                      \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1, \
    boost::fusion::result_of::at_c<parameters, 2>::type _2, \
    boost::fusion::result_of::at_c<parameters, 3>::type _3, \
    boost::fusion::result_of::at_c<parameters, 4>::type _4  \
  )                                                         \
  /**/

#define ARIEL_1ARY_CALL_DEF(T, x, _0)                       \
  T<x>::result T<x>::call (                                 \
    boost::fusion::result_of::at_c<parameters, 0>::type _0  \
  )                                                         \
  /**/

#define ARIEL_2ARY_CALL_DEF(T, x, _0, _1)                   \
  T<x>::result T<x>::call (                                 \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1  \
  )                                                         \
  /**/

#define ARIEL_3ARY_CALL_DEF(T, x, _0, _1, _2)               \
  T<x>::result T<x>::call (                                 \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1, \
    boost::fusion::result_of::at_c<parameters, 2>::type _2  \
  )                                                         \
  /**/

#define ARIEL_4ARY_CALL_DEF(T, x, _0, _1, _2, _3)           \
  T<x>::result T<x>::call (                                 \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1  \
    boost::fusion::result_of::at_c<parameters, 2>::type _2, \
    boost::fusion::result_of::at_c<parameters, 3>::type _3  \
  )                                                         \
  /**/

#define ARIEL_5ARY_CALL_DEF(T, x, _0, _1, _2, _3, _4)       \
  T<x>::result T<x>::call (                                 \
    boost::fusion::result_of::at_c<parameters, 0>::type _0, \
    boost::fusion::result_of::at_c<parameters, 1>::type _1, \
    boost::fusion::result_of::at_c<parameters, 2>::type _2, \
    boost::fusion::result_of::at_c<parameters, 3>::type _3, \
    boost::fusion::result_of::at_c<parameters, 4>::type _4  \
  )                                                         \
  /**/

#endif // ARIEL_CALL_BUILDER_HXX
