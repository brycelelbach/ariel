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
    get_node;

  karma::rule<Iterator, ir::node(std::size_t)>
    get_name;

  karma::rule<Iterator, ir::unique_id(void)>
    id;

  karma::rule<Iterator, std::vector<ir::link>(std::size_t)>
    links;

  karma::rule<Iterator, ir::link(std::size_t, std::size_t)>
    link;

  std::size_t count;

  naive_dot_grammar (void): naive_dot_grammar::base_type(start), count(0) {
    start =
         karma::lit("digraph {") 
      << karma::eol 
      << "rankdir=\"BT\";" 
      << karma::eol 
      << context 
      << karma::eol 
      << "}" 
      << karma::eol;

    context = *(get_node);

    // FIXME: handle each optional link collection, e.g. formatting, etc
    get_node = 
         karma::lit("n") << id
      << "_" << karma::lit(++px::ref(count))
      << "[label=\"" << karma::string << "\"];"
      << karma::eol
      << links(px::ref(count))
      << links(px::ref(count))
      << links(px::ref(count));
    
    get_name = 
         karma::lit("n") << id 
      << "_" << karma::lit(karma::_r1)
      << karma::skip[karma::string]
      << karma::skip[links(px::ref(count))]
      << karma::skip[links(px::ref(count))]
      << karma::skip[links(px::ref(count))];

    karma::uint_generator<std::size_t> id_element;

    id = id_element << id_element;

    // FIXME: do stuff with the vector size in link, if this link
    // collection is parametric (break into more rules)
    links = *link(karma::_r1, px::size(karma::_val));

    karma::uint_generator<boost::uint_t<8>::fast> meta;

    // FIXME: the skip here is temporary, we need to modify shape/color of edges
    // in dot according to relationship in ariel IR
    link =
         get_name(karma::_r1)
      << " -> "
      << get_name(karma::_r1)
      << karma::skip[meta]
      << ";" << karma::eol;
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_NAIVE_DOT_GRAMMAR_HXX

