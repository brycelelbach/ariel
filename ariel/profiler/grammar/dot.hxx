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

#if !defined(ARIEL_PROFILER_DOT_GRAMMAR_HXX)
#define ARIEL_PROFILER_DOT_GRAMMAR_HXX

#include <boost/spirit/include/karma_action.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_nonterminal.hpp>
#include <boost/spirit/include/karma_directive.hpp>
#include <boost/spirit/include/karma_auxiliary.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_operator.hpp>
#include <boost/spirit/include/karma_numeric.hpp>

#include <boost/spirit/include/phoenix.hpp>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector.hpp>

#include <ariel/ir/node.hxx>

namespace karma = boost::spirit::karma;
namespace px = boost::phoenix;
namespace fusion = boost::fusion;

namespace ariel {
namespace profiler {

template<class Iterator>
struct dot_grammar: karma::grammar<Iterator, ir::context(void)> {
 public:
  karma::rule<Iterator, ir::context(void)>
    start;

  karma::rule<Iterator, ir::context(void)>
    context;

  karma::rule<Iterator, ir::node(void)>
    get_node_name, get_node_links;

  karma::rule<Iterator, std::list<ariel::ir::link>(ir::node)>
    links;

  karma::rule<Iterator, ir::link(ir::node)>
    link;

  dot_grammar (void): dot_grammar::base_type(start) {
    start =
      karma::duplicate[
           karma::lit("digraph {") 
        << karma::eol 
        << "rankdir=\"BT\";" 
        << karma::eol 
        << context 
        << karma::eol 
        << (*get_node_links) 
        << karma::eol 
        << "}" 
        << karma::eol
      ];

    context = *(get_node_name << ";" << karma::eol);

    get_node_links = karma::skip[karma::string] << links(karma::_val);
 
    get_node_name = karma::string << karma::skip[links(karma::_val)];

    links = *link(karma::_r1);

    karma::uint_generator<boost::uint_t<8>::fast> meta;

    // the skip here is temporary, we need to modify shape/color
    // of edges in dot according to relationship in ariel IR
    link = get_node_name << " -> " << get_node_name << karma::skip[meta] << ";";
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_DOT_GRAMMAR_HXX

