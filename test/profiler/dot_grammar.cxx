//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <ariel/profiler/grammar/dot.hxx>

#include <ariel/ir/make_link.hxx>
#include <ariel/ir/make_attribute.hxx>

#include <iostream>

using namespace ariel;

int main (void) {
  typedef std::back_insert_iterator<std::string> iterator;
  typedef profiler::dot_grammar<iterator> grammar; 

  ir::context cont;
  ir::context::iterator A = cont.insert(cont.begin(), ir::node(0)),
                        B = cont.insert(cont.begin(), ir::node(1)),
                        C = cont.insert(cont.begin(), ir::node(2));

  ir::make_attribute(A, "name", "A");
  ir::make_attribute(B, "name", "B");
  ir::make_attribute(C, "name", "C");

  ir::make_link(C, A, ir::INHERITANCE);
  ir::make_link(C, B, ir::INHERITANCE);
  ir::make_link(B, A, ir::INHERITANCE);

  std::string generated;
  iterator sink(generated);
  grammar gram;
  
  if (!karma::generate(sink, gram, cont))
    std::cout << "generation failed\n";

  else
    std::cout << generated;
}

