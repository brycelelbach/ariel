//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_CROSS_DOT_WRITER_HXX)
#define ARIEL_PROFILER_CROSS_DOT_WRITER_HXX

#include <llvm/Support/raw_ostream.h>

#include <ariel/profiler/traits.hxx>
#include <ariel/profiler/writers/writer_builder.hxx>
#include <ariel/profiler/grammar/cross_dot.hxx>

namespace ariel {
namespace profiler {

ARIEL_WRITER_PARAMS(Filter)
class cross_dot_writer: public Filter<cross_dot_writer<Filter> > {
 public:
  typedef production_traits<cross_dot_writer> traits;

  typedef typename traits::writer_type   writer_type;
  typedef typename traits::filter_type   filter_type;
  typedef typename traits::consumer_type consumer_type;

  template<class ClangContext>
  void call (ClangContext& clang_ctx, ir::context& ariel_ctx) {
    typedef std::back_insert_iterator<std::string> iterator;
    
    std::string generated;
    iterator sink(generated);
    cross_dot_grammar<iterator> gram;
  
    if (!karma::generate(sink, gram, ariel_ctx))
      llvm::outs() << "generation failed\n";

    else
      llvm::outs() << generated;
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_CROSS_DOT_WRITER_HXX
