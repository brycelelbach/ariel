//===-----------------------------------------------------------*- C++ -*-===//
// Copyright 2010 Bryce Lelbach
// Copyright (c) 2001-2010 Hartmut Kaiser
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PROFILER_NAIVE_DOT_GRAMMAR_HXX)
#define ARIEL_PROFILER_NAIVE_DOT_GRAMMAR_HXX

#include <boost/spirit/include/karma_action.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_nonterminal.hpp>
#include <boost/spirit/include/karma_directive.hpp>
#include <boost/spirit/include/karma_auxiliary.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_operator.hpp>
#include <boost/spirit/include/karma_numeric.hpp>
#include <boost/spirit/include/karma_string.hpp>

#include <boost/spirit/include/phoenix.hpp>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector.hpp>

#include <ariel/ir/node.hxx>

namespace ariel {

namespace karma = boost::spirit::karma;
namespace px = boost::phoenix;

namespace profiler {

template<class Iterator>
struct naive_dot_grammar: karma::grammar<Iterator, ir::context(void)> {
 public:
  karma::rule<Iterator, ir::context(void)>
    start;

  karma::rule<Iterator, ir::context(void)>
    context;

  karma::rule<Iterator, ir::node(void)>
    name, node;

  karma::rule<Iterator, ir::unique_id(void)>
    id, styled_id;

  karma::rule<Iterator, std::vector<ir::link>(void), karma::locals<unsigned> >
    links;

  karma::rule<Iterator, ir::link(std::size_t)>
    link, relationship, dependency;

  karma::uint_generator<std::size_t>
    hash;

  karma::uint_generator<boost::uint_t<8>::fast>
    relation;

  std::size_t count;

  naive_dot_grammar (void): naive_dot_grammar::base_type(start), count(0) {
    using karma::skip;
    using karma::omit;
    using karma::lit;
    using karma::duplicate;
    using karma::string;
    using karma::_a;
    using karma::_r1;
    using karma::_val;
    using px::size;
    using px::ref;

    start = lit("digraph {\n  rankdir=\"BT\"; clusterrank=\"local\";\n")
         << context
         << "}\n";

    context = *( lit("  subgraph cluster_") << lit(++ref(count))
              << " {\n" << node << "  };\n"
               );
    
    // FIXME: handle each optional link collection, e.g. formatting, etc
    node = styled_id << "label=\"" << string << "\"];\n"
        << links << links << links;
    
    name = id << skip[string]
        << skip[links] << skip[links] << skip[links];

    // FIXME: style nodes by kind
    styled_id = lit("    n") << lit(ref(count)) << "_" << hash << "_" << hash
             << "[";
    
    id = lit("n") << lit(ref(count)) << "_" << hash << "_" << hash;
    
    links = *link(++_a);

    link = duplicate[relationship(_r1) << dependency(_r1)];        
 
    relationship = lit("    ") << name << " -> " << name << "[" <<
      ( (&relation(ir::INHERITANCE)
         << "color=\"blue\"")
      | (&relation(ir::MEMBERSHIP) 
         << "color=\"green\"")
      | (&relation(ir::PARAMETRIC) 
         << "color=\"red\" label=\"" << lit(_r1) << "\"")
      ) << "];\n"; 
 
    dependency = skip[name] << node << skip[relation];
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_NAIVE_DOT_GRAMMAR_HXX

