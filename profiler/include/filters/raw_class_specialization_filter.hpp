// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_RAW_CLASS_SPECIALIZATION_FILTER_HPP)
#define ARIEL_PROFILER_RAW_CLASS_SPECIALIZATION_FILTER_HPP

#include "clang/AST/ASTContext.h"
#include "clang/AST/AST.h"

#include "preprocessor/poly.hpp"
#include "preprocessor/foreach.hpp"

#include "profiler/include/traits.hpp"

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
struct consumer;

template<class Writer>
struct raw_class_specialization_filter;

template<template<template<class> class> class Writer>
class raw_class_specialization_filter<Writer<raw_class_specialization_filter> >:
  public consumer<
    raw_class_specialization_filter<Writer<raw_class_specialization_filter> >
  >
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
  typedef production_traits<raw_class_specialization_filter> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  typedef clang::ClassTemplateSpecializationDecl target_type;
  
  bool call (clang::ASTContext& ctx) {
    typedef clang::ASTContext::type_iterator iterator;
    
    ARIEL_FOREACH_LLVM(iterator, it, end, ctx, types_) {
      ARIEL_IF_DYN_CAST(clang::RecordType, rec, *it) continue;
      ARIEL_IF_DYN_CAST(target_type, decl, rec->getDecl()) continue;
  
      add(decl);
    }

    return true;
  }

  bool error (clang::ASTContext& ctx) { return false; }

  void add (target_type* data) {
    // TODO: implement after implementation of ir::point
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_RAW_CLASS_SPECIALIZATION_FILTER_HPP
