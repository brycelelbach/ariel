//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_TYPE_DEPENDENCY_FILTER_HXX)
#define ARIEL_PROFILER_TYPE_DEPENDENCY_FILTER_HXX

#include <clang/AST/ASTContext.h>
#include <clang/AST/AST.h>

#include <ariel/ir/node.hxx>

#include <ariel/utility/llvm.hxx>

#include <ariel/profiler/traits.hxx>
#include <ariel/profiler/filters/filter_builder.hxx>
#include <ariel/profiler/filters/get_type_name.hxx>

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
class consumer;

template<class Writer>
class type_dependency_filter;

ARIEL_FILTER_PARAMS(Writer)
class ARIEL_FILTER(type_dependency_filter, Writer):
  public consumer<ARIEL_FILTER(type_dependency_filter, Writer)>
{
 protected:
  std::list<ir::node> _ir;
  
 public:
  typedef production_traits<type_dependency_filter> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  typedef clang::Type target_type;
  
  template<class Context>
  void call (Context& ctx) {
    ARIEL_LLVM_FOREACH(typename Context::type_iterator, it, end, ctx, types_) {
      add(*it);
    }

    static_cast<writer_type*>(this)->call(ctx);
  }

  std::list<ir::node>::iterator add (target_type* data) {
    std::list<ir::node>::iterator it = _ir.insert(_ir.begin(), ir::node());

    return it;
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_TYPE_DEPENDENCY_FILTER_HXX
