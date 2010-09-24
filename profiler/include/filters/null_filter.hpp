// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_NULL_FILTER_HPP)
#define ARIEL_PROFILER_NULL_FILTER_HPP

#include "profiler/include/traits.hpp"

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
struct consumer;

template<class Writer>
struct null_filter;

template<template<template<class> class> class Writer>
class null_filter<Writer<null_filter> >:
  public consumer<null_filter<Writer<null_filter> > >
{
 private:
  // TODO: uncomment after implementation of ir::point
  #if 0
  std::list<ir::point> points;
  #endif

 protected:
  // TODO: uncomment after implementation of ir::point
  #if 0
  std::list<ir::point>::iterator get (void) { return points.begin(); }
  #endif
 
 public:
  typedef production_traits<null_filter> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  template<class Context>
  bool call (Context& ctx) { return true; }
  
  template<class Context>
  bool error (Context& ctx) { return false; }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_NULL_FILTER_HPP
