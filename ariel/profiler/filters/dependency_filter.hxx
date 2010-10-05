//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_DEPENDENCY_FILTER_HXX)
#define ARIEL_PROFILER_DEPENDENCY_FILTER_HXX

#include <clang/AST/ASTContext.h>
#include <clang/AST/AST.h>

#include <ariel/ir/node.hxx>
#include <ariel/ir/make_attribute.hxx>
#include <ariel/utility/llvm.hxx>
#include <ariel/profiler/traits.hxx>
#include <ariel/profiler/filters/filter_builder.hxx>
#include <ariel/profiler/filters/get_name.hxx>
#include <ariel/profiler/filters/get_id.hxx>
#include <ariel/profiler/filters/link_children.hxx>
#include <ariel/profiler/filters/link_bases.hxx>

namespace ariel {
namespace profiler {

// forward declaration
template<class Filter>
class consumer;

template<class Writer>
class dependency_filter;

ARIEL_FILTER_PARAMS(Writer)
class ARIEL_FILTER(dependency_filter, Writer):
  public consumer<ARIEL_FILTER(dependency_filter, Writer)>
{
 public:
  typedef production_traits<dependency_filter> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  typedef clang::ClassTemplateSpecializationDecl target_type;
  
  template<class ClangContext>
  void call (ClangContext& clang_ctx) {
    ir::context ariel_ctx;

    ARIEL_LLVM_FOREACH(
      typename ClangContext::type_iterator, it, end, clang_ctx, types_
    ) {
      ARIEL_IF_NOT_DYN_CAST(clang::RecordType, rec, *it) continue;
      ARIEL_IF_NOT_DYN_CAST(target_type, decl, rec->getDecl()) continue;
      
      add(ariel_ctx, decl);
    }

    static_cast<writer_type*>(this)->call(clang_ctx, ariel_ctx);
  }

  static ir::context::iterator add (ir::context& ariel_ctx, target_type* data) {
    std::pair<ir::context::iterator, bool> r = ariel_ctx.insert(
      ir::node(get_id<target_type>::call(data))
    );

    if (r.second == false) return r.first;

    link_children<target_type, dependency_filter>::call(
      ariel_ctx, r.first, data
    );

    link_bases<target_type, dependency_filter>::call(
      ariel_ctx, r.first, data
    );

    ir::make_attribute(r.first, "name", get_name<target_type>::call(data));

    return r.first;
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_DEPENDENCY_FILTER_HXX
