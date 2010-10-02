//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_NULL_FILTER_HXX)
#define ARIEL_PROFILER_NULL_FILTER_HXX

#include <ariel/ir/node.hxx>

#include <ariel/profiler/traits.hxx>
#include <ariel/profiler/filters/filter_builder.hxx>

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
 public:
  typedef production_traits<null_filter> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  template<class ClangContext>
  void call (ClangContext& clang_ctx) {
    ir::context ariel_ctx;
    static_cast<writer_type*>(this)->call(clang_ctx, ariel_ctx);
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_NULL_FILTER_HXX
