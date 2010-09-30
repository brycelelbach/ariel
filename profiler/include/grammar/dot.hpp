// Copyright 2010 Bryce Lelbach
// Copyright (c) 2001-2010 Hartmut Kaiser (this file is derived from spirit examples)
// 
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_PROFILER_DOT_GRAMMAR_HPP)
#define ARIEL_PROFILER_DOT_GRAMMAR_HPP

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/karma_stream.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include "ir/include/node.hpp"

namespace karma = boost::spirit::karma;
namespace px = boost::phoenix;
namespace ascii = boost::spirit::ascii;

namespace ariel {
namespace profiler {

template<class Iterator>
struct dot_digraph_grammar: karma::grammar<Iterator, ir::node(void)> {
  karma::rule<Iterator>
    eol;

  karma::rule<Iterator, ir::node(void)>
    root;

  karma::symbols<std::string, int>
    names;

  karma::rule<Iterator, std::string(void)>
    name;

  karma::rule<Iterator, ir::node(void)>
    node;

  karma::rule<Iterator, ir::link::metadata(void)>
    direction, relation;

  karma::rule<Iterator, ir::node::link_list(void)>
    links;

  karma::rule<Iterator, ir::link(void)>
    link;
  
  karma::rule<Iterator, ir::node::attribute_lookup(void)>
    attributes;

  karma::rule<Iterator, ir::node::add_attribute(void)> 
    attribute_pair;

  karma::rule<Iterator, ir::node::attribute_type(void)> 
    attribute;

  int count;
  int from;
  int to;

  dot_digraph_grammar (void):
    dot_digraph_grammar::base_type(root), count(0), from(0), to(0)
  {
    eol = karma::eol << "  ";

    root  
       = karma::lit("digraph {")
      << eol
      << node
      << karma::eol
      << "};";

    node
       = "n" << karma::lazy(++px::ref(count))
      << " [label=\""
      << karma::string
      << "\" " << attributes << "];"
      << eol
      << links;

    karma::uint_generator<ir::link::metadata> meta;

    direction
       = (
           ( karma::omit[meta(ir::UPWARDS)]
          << "n" << karma::lazy(px::ref(count) - 1)
          << " -> n" << karma::lazy(px::ref(count))
           )
         |
           ( karma::omit[meta(ir::DOWNWARDS)]
          << "n" << karma::lazy(px::ref(count))
          << " -> n" << karma::lazy(px::ref(count) - 1)
           )
         )
      << "["
    ;

    relation
       = (  karma::omit[meta(ir::UNRELATED)]
         | (karma::omit[meta(ir::INHERITANCE)] << "color=\"red\" ")
         | (karma::omit[meta(ir::PARAMETRIC)]  << "color=\"blue\" ")
         | (karma::omit[meta(ir::MEMBERSHIP)]  << "color=\"green\" ")
         )
      << "];"
      << eol
    ;

    links = *link;

    link
       = node
      << direction
      << relation;

    attributes = *attribute_pair;

    attribute_pair
       = karma::string
      << attribute;
 
    attribute
       = karma::string
       | karma::int_generator<boost::intmax_t>();
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_DOT_GRAMMAR_HPP

