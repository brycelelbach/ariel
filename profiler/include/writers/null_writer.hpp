// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_NULL_WRITER_HPP)
#define ARIEL_PROFILER_NULL_WRITER_HPP

#include "profiler/include/traits.hpp"

namespace ariel {
namespace profiler {

template<template<class> class Filter>
class null_writer: public Filter<null_writer<Filter> > {
 public:
  typedef production_traits<null_writer> traits;

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

#endif // ARIEL_PROFILER_NULL_WRITER_HPP
