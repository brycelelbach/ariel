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

  karma::rule<Iterator, ir::context(std::size_t)>
    context_nodes, context_links;

  karma::rule<Iterator, ir::node(void)>
    get_name;

  karma::rule<Iterator, ir::node(std::size_t)>
    get_node, get_links;

  karma::rule<Iterator, ir::unique_id(void)>
    id;

  karma::rule<Iterator, std::vector<ir::link>(void)>
    links, local_links;

  karma::rule<Iterator, ir::link(std::size_t)>
    print_link, link, local_link;

  karma::uint_generator<std::size_t>
    id_element;

  karma::uint_generator<boost::uint_t<8>::fast>
    meta;

  std::size_t count;

  naive_dot_grammar (void): naive_dot_grammar::base_type(start) {
    using karma::skip;
    using karma::eol;
    using karma::lit;
    using karma::duplicate;
    using karma::string;
    using karma::_r1;
    using karma::_val;
    using px::size;
    using px::ref;

    start = //duplicate
      /*[*/ lit("digraph {") 
     << eol 
     << "rankdir=\"BT\";" 
     << eol 
     << context_nodes(ref(count) = 0)
     << eol 
//     << context_links(ref(count) = 0)
     << eol 
     << "}" 
     << eol
     /* ]*/;

    context_nodes = *(get_node(++ref(count)));
    
//    context_links = *(get_links(++ref(count)));

    get_node = id << "[label=\"" << string << "\"];" << eol
            << local_links << local_links << local_links;
    
    get_name = id << skip[string]
            << skip[local_links] << skip[local_links] << skip[local_links];

    // FIXME: handle each optional link collection, e.g. formatting, etc
 //   get_links = skip[id] << skip[string]
   //          << links << links << links;

    id = lit("n") << lit(ref(count)) << "_" << id_element << "_" << id_element;
    
    // FIXME: do stuff with the vector size in link, if this link
    // collection is parametric (break into more rules)
   // links = *link(size(_val));

    local_links = *link(size(_val));

    // FIXME: the skip here is temporary, we need to modify shape/color of edges
    // in dot according to relationship in ariel IR
    link = duplicate[print_link(_r1) << local_link(_r1)];
   
    print_link = get_name << " -> " << get_name << skip[meta] << ";" << eol;
 
    local_link = skip[get_name] << get_node(0) << skip[meta];
  }
};

} // profiler
} // ariel

#endif // ARIEL_PROFILER_NAIVE_DOT_GRAMMAR_HXX

