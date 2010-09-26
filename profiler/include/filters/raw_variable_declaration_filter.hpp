// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_RAW_VARIABLE_DECLARATION_FILTER_HPP)
#define ARIEL_PROFILER_RAW_VARIABLE_DECLARATION_FILTER_HPP

#include "clang/AST/ASTContext.h"
#include "clang/AST/AST.h"

#include <boost/foreach.hpp>

#include "profiler/include/traits.hpp"
#include "profiler/include/filters/filter_visitor.hpp"
#include "profiler/include/filters/filter_builder.hpp"

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
class consumer;

// forward declaration
template<class Target>
class filter_visitor;

// specialization
ARIEL_FILTER_VISITOR(VarDecl)

template<class Writer>
struct raw_variable_declaration_filter;

ARIEL_FILTER_PARAMS(Writer)
class ARIEL_FILTER(raw_variable_declaration_filter, Writer):
  public consumer<ARIEL_FILTER(raw_variable_declaration_filter, Writer)>
{
 private:
  filter_visitor<clang::VarDecl> visitor;

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
  typedef production_traits<raw_variable_declaration_filter> traits;
  
  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  typedef clang::VarDecl target_type;
 
  bool call (clang::ASTContext& ctx) {
    if (!visitor.TraverseDecl(ctx.getTranslationUnitDecl()));
      return false;

    BOOST_FOREACH(target_type* i, visitor.get()) { add(i); }

    return true;
  }

  bool error (clang::ASTContext& ctx) { return false; }

  void add (target_type* data) {
    // TODO: implement after implementation of ir::point
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_RAW_VARIABLE_DECLARATION_FILTER_HPP
