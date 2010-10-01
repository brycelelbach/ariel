// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_NULL_FILTER_HPP)
#define ARIEL_PROFILER_NULL_FILTER_HPP

#include "ir/node.hpp"

#include "profiler/include/traits.hpp"
#include "profiler/include/filters/filter_builder.hpp"

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
struct consumer;

template<class Writer>
struct null_filter;

ARIEL_FILTER_PARAMS(Writer)
class ARIEL_FILTER(null_filter, Writer):
  public consumer<ARIEL_FILTER(null_filter, Writer)>
{
 protected:
  std::list<ir::node> _ir;
 
 public:
  typedef production_traits<null_filter> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  template<class Context>
  void call (Context& ctx) { static_cast<writer_type*>(this)->call(ctx); }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_NULL_FILTER_HPP
