//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_FILTER_BUILDER_HXX)
#define ARIEL_PROFILER_FILTER_BUILDER_HXX

// Name builder macro for filter classes. 
#define ARIEL_FILTER(Name, Writer)                      \
  Name<Writer<Name> >                                   \
  /**/

// Parameter builder for filters. 
#define ARIEL_FILTER_PARAMS(Name)                       \
  template<template<template<class> class> class Name>  \
  /**/

#endif // ARIEL_PROFILER_FILTER_BUILDER_HXX
