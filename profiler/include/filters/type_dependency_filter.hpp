// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_TYPE_DEPENDENCY_FILTER_HPP)
#define ARIEL_PROFILER_TYPE_DEPENDENCY_FILTER_HPP

#include "clang/AST/ASTContext.h"
#include "clang/AST/AST.h"

#include "ir/include/node.hpp"

#include "preprocessor/poly.hpp"
#include "preprocessor/foreach.hpp"

#include "profiler/include/traits.hpp"
#include "profiler/include/filters/filter_builder.hpp"
#include "profiler/include/filters/get_type_name.hpp"

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
    ARIEL_FOREACH_LLVM(typename Context::type_iterator, it, end, ctx, types_) {
      add(*it);
    }

    static_cast<writer_type*>(this)->call(ctx);
  }

  std::list<ir::node>::iterator add (target_type* data) {
    std::list<ir::node>::iterator it = _ir.insert(_ir.begin(), ir::node());

    ir::node& node = *it;

    node.attributes.insert(ir::node::add_attribute(
      "name", get_type_name<clang::Type>::call(data)
    ));

    return it;
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_TYPE_DEPENDENCY_FILTER_HPP
