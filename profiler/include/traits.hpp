// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_TRAITS_HPP)
#define ARIEL_PROFILER_TRAITS_HPP

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
struct consumer;

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

// defined to demonstrate the concept, this class should
// be specialized by each filter
template<typename Filter>
struct target_traits {
  typedef void*        value_type; 
  typedef void**       container;
  typedef void**       iterator;
  typedef void* const* const_iterator;
  typedef void*&       reference;
  typedef void* const& const_reference;
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_TRAITS_HPP
