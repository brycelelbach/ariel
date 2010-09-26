// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_FILTER_VISITOR_HPP)
#define ARIEL_PROFILER_FILTER_VISITOR_HPP

#include "clang/AST/RecursiveASTVisitor.h"

#include <boost/preprocessor/cat.hpp>

#include <list>

// Specializes RecursiveASTVisitor for a specific clang AST node. Use in
// namespace ariel::profiler!
#define ARIEL_FILTER_VISITOR(Target)                                           \
  template<>                                                                   \
  class filter_visitor<clang::Target>:                                         \
    public clang::RecursiveASTVisitor<filter_visitor<clang::Target> >          \
  {                                                                            \
   private:                                                                    \
    typedef clang::Target target_type;                                         \
    std::list<target_type*> targets;                                           \
                                                                               \
   public:                                                                     \
    bool shouldVisitTemplateInstantiations (void) const { return true; }       \
                                                                               \
    bool BOOST_PP_CAT(Traverse, Target) (target_type* t) {                     \
      if (t) targets.push_back(t);                                             \
      return true;                                                             \
    }                                                                          \
                                                                               \
    std::list<target_type*>& get (void) { return targets; }                    \
  };                                                                           \
  /**/

#endif // ARIEL_PROFILER_FILTER_VISITOR_HPP
