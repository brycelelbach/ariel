//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_TRAITS_HXX)
#define ARIEL_PROFILER_TRAITS_HXX

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
class consumer;

template<class Production>
struct production_traits;

// consumer specialization
template<
  template<template<class> class> class Writer,
  template<class> class Filter
>
struct production_traits<consumer<Filter<Writer<Filter> > > > {
 public:
  typedef Writer<Filter>         writer_type;
  typedef Filter<writer_type>    filter_type;
  typedef consumer<filter_type>  consumer_type;
};

// filter specialization
template<
  template<template<class> class> class Writer,
  template<class> class Filter
>
struct production_traits<Filter<Writer<Filter> > > {
 public:
  typedef Writer<Filter>         writer_type;
  typedef Filter<writer_type>    filter_type;
  typedef consumer<filter_type>  consumer_type;
};

// writer specialization
template<
  template<template<class> class> class Writer,
  template<class> class Filter 
>
struct production_traits<Writer<Filter> > {
 public:
  typedef Writer<Filter>         writer_type;
  typedef Filter<writer_type>    filter_type;
  typedef consumer<filter_type>  consumer_type;
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_TRAITS_HXX
