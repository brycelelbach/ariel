//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_CONSUMER_HXX)
#define ARIEL_PROFILER_CONSUMER_HXX

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/AST.h>

#include <ariel/profiler/traits.hxx>

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

  void HandleTranslationUnit (clang::ASTContext& ctx) { 
    static_cast<filter_type*>(this)->call(ctx);
  }

  void set_name (std::string const& new_name) { name = new_name; }
  void set_name (llvm::StringRef new_name) { name = new_name.data(); }
  std::string const& get_name (void) const { return name; }

 private:
  std::string name;
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_CONSUMER_HXX
