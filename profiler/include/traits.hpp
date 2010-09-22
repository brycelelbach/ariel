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

template<class Target>
struct target_traits {
  typedef Target        value_type;
  typedef Target*       container;
  typedef Target*       iterator;
  typedef Target const* const_iterator;
  typedef Target&       reference;
  typedef Target const& const_reference;
};

// consumer specialization
template<
  template<template<class> class, class> class Writer,
  template<class> class Filter, class Target
>
struct production_traits<consumer<Filter<Writer<Filter, Target> > > > {
 public:
  typedef typename target_traits<Target>::value_type value_type;
  typedef typename target_traits<Target>::container  container;

  typedef Writer<Filter, Target> writer_type;
  typedef Filter<writer_type>    filter_type;
  typedef consumer<filter_type>  consumer_type;
};

// filter specialization
template<
  template<template<class> class, class> class Writer,
  template<class> class Filter, class Target
>
struct production_traits<Filter<Writer<Filter, Target> > > {
 public:
  typedef typename target_traits<Target>::value_type value_type;
  typedef typename target_traits<Target>::container  container;

  typedef Writer<Filter, Target> writer_type;
  typedef Filter<writer_type>    filter_type;
  typedef consumer<filter_type>  consumer_type;
};

// writer specialization
template<
  template<template<class> class, class> class Writer,
  template<class> class Filter, class Target
>
struct production_traits<Writer<Filter, Target> > {
 public:
  typedef typename target_traits<Target>::value_type value_type;
  typedef typename target_traits<Target>::container  container;

  typedef Writer<Filter, Target> writer_type;
  typedef Filter<writer_type>    filter_type;
  typedef consumer<filter_type>  consumer_type;
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_TRAITS_HPP
