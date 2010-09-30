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

namespace ariel {
namespace profiler {

template<class Iterator>
struct dot_digraph_grammar: karma::grammar<Iterator, ir::node(void)> {
  karma::rule<Iterator, ir::node(void)>
    root, node;

  karma::rule<Iterator, ir::node::link_lookup(void)>
    links;

  karma::rule<Iterator, ir::node::add_link(void)>
    link_pair; 

  karma::rule<Iterator, ir::node::link_array(void)>
    link_array;
  
  karma::rule<Iterator, std::list<ir::link>::iterator(void)>
    link_iterator;

  karma::rule<Iterator, ir::link(void)>
    link;

  karma::rule<Iterator, std::list<ir::node>::iterator(void)>
    node_iterator;
  
  karma::rule<Iterator, ir::node::attribute_lookup(void)>
    attributes;

  karma::rule<Iterator, ir::node::add_attribute(void)> 
    attribute_pair;

  karma::rule<Iterator, ir::node::attribute_type(void)> 
    attribute;

  dot_digraph_grammar (void): dot_digraph_grammar::base_type(root) {
    root = karma::lit("digraph {") << karma::eol << node << "};";

    // ir::node 
    node = karma::string << "[" << -attributes << "];" << karma::eol << -links; 

    // std::map<std::string, std::vector<std::list<ir::link::iterator> >
    links = *link_pair;

    // std::pair<std::string, std::vector<std::list<ir::link>::iterator> > 
    link_pair = karma::string << link_array;

    // std::vector<std::list<ir::link>::iterator>
    link_array = *link_iterator;
    
    // std::list<ir::link>::iterator
    link_iterator = link[karma::_1 = *karma::_val];

    // ir::link
    link = node_iterator[karma::_1 = *karma::_val];

    // std::list<ir::node>::iterator
    node_iterator = node[karma::_1 = *karma::_val];
    
    // std::map<std::string, boost::variant<std::string, boost::intmax_t> >
    attributes = *attribute_pair;

    // std::pair<std::string, boost::variant<std::string, boost::intmax_t> >
    attribute_pair = karma::string << attribute; 

    // boost::variant<std::string, boost::intmax_t> 
    attribute = karma::string | karma::int_generator<boost::intmax_t>();
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_DOT_GRAMMAR_HPP

