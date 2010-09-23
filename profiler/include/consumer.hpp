// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_CONSUMER_HPP)
#define ARIEL_PROFILER_CONSUMER_HPP

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"

#include "profiler/include/traits.hpp"

namespace ariel {
namespace profiler {

template<class Production>
class plugin;

template<class Filter>
class consumer;

template<
  template<template<class> class> class Writer,
  template<class> class Filter
>
class consumer<Filter<Writer<Filter> > >: public clang::ASTConsumer {
 public:
  typedef production_traits<consumer> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  typedef typename target_traits<filter_type>::container container;

  // these aren't inherited, but plugin static_casts the Production
  // that it makes to a Production::consumer_type so we can avoid
  // requiring that client classes friend plugin if they inherit from
  // consumer
  friend class plugin<writer_type>;
  friend class plugin<filter_type>;
  friend class plugin<consumer_type>;
  
  void HandleTranslationUnit (clang::ASTContext& ctx) { 
    if (!static_cast<filter_type*>(this)->call(ctx)
    &&  !static_cast<filter_type*>(this)->error(ctx))
      return;

    if (!static_cast<writer_type*>(this)->call(ctx))
      static_cast<writer_type*>(this)->error(ctx);
  }

 protected:
  std::string name;
  container   ir;
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_CONSUMER_HPP
