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

#if !defined(ARIEL_PROFILER_CROSS_DOT_GRAMMAR_HXX)
#define ARIEL_PROFILER_CROSS_DOT_GRAMMAR_HXX

#include <boost/spirit/include/karma_action.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_nonterminal.hpp>
#include <boost/spirit/include/karma_directive.hpp>
#include <boost/spirit/include/karma_auxiliary.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_operator.hpp>
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
struct cross_dot_grammar: karma::grammar<Iterator, ir::context(void)> {
 public:
  karma::rule<Iterator, ir::context(void)>
    start;

  karma::rule<Iterator, ir::context(void)>
    context;

  karma::rule<Iterator, ir::node(void)>
    node, dependencies, name;

  karma::rule<Iterator, ir::unique_id(void)>
    node_id, name_id;

  karma::rule<Iterator, std::vector<ir::link>(void), karma::locals<std::size_t> >
    links;

  karma::rule<Iterator, ir::link(std::size_t)>
    link;

  karma::rule<Iterator, void(std::size_t)>
    kind;

  karma::symbols<std::size_t, char const*>
    kind_table;

  karma::uint_generator<std::size_t>
    hash;

  karma::uint_generator<boost::uint_t<8>::fast>
    relation;

  cross_dot_grammar (void): cross_dot_grammar::base_type(start) {
    using karma::skip;
    using karma::omit;
    using karma::lit;
    using karma::duplicate;
    using karma::string;
    using karma::_a;
    using karma::_1;
    using karma::_r1;
    using karma::_val;
    using px::ref;
    using px::at_c;

    start = duplicate // aspect is set to golden ratio, for sanity's sake
          [ lit("digraph {\n  rankdir=\"BT\"; overlap=false; splines=true;\n")
         << (*node)
         << (*dependencies)
         << "}\n"
          ];
    
    // FIXME: handle each optional link collection, e.g. formatting, etc
    node = node_id << "label=\"" << string << "\"];\n"
        << skip[links] << skip[links] << skip[links];
    
    dependencies = skip[node_id] << skip[string] << links << links << links;
    
    name = name_id << skip[string] << skip[links] << skip[links] << skip[links];

    // FIXME: style nodes by kind
    node_id = lit("  n") << hash << "_" << hash << "[" << 
              kind(at_c<0>(_val));

    name_id = lit("n") << hash << "_" << hash;
    
    links = *(link(++_a));

    link = lit("  ") << name << " -> " << name << "[" <<
         ( (&relation(ir::INHERITANCE)
            << "color=\"blue\"")
         | (&relation(ir::MEMBERSHIP) 
            << "color=\"green\"")
         | (&relation(ir::PARAMETRIC) 
            << "color=\"red\" label=\"" << lit(_r1) << "\"")
         | (&relation(ir::DEFINITION) 
            << "shape=none weight=0.5 label=\"definition\"")
         | (&relation(ir::DECLARATION) 
            << "shape=none weight=0.5 label=\"declaration\"")
         | (&relation(ir::INSTANTIATION) 
            << "shape=none weight=0.5 label=\"instantiation\"")
         ) << "];\n"; 

    kind = kind_table[_1 = _r1];

    kind_table.add
      (ir::TYPE,                                    "shape=polygon ")
      (ir::CLASS,                                   "shape=triangle ")
      (ir::TEMPLATE | ir::CLASS,                    "shape=square ")
      (ir::TEMPLATE | ir::CLASS | ir::INSTANTIATED, "shape=diamond ")
      (ir::INTEGRAL,                                "shape=circle ")
      (ir::LOCATION,                                "shape=egg ")
    ;
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_CROSS_DOT_GRAMMAR_HXX

