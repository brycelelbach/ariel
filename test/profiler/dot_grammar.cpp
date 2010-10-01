#include "profiler/include/grammar/dot.hpp"

#include <iostream>

using namespace ariel;

int main (void) {
  typedef std::back_insert_iterator<std::string> iterator;
  typedef profiler::dot_grammar<iterator> grammar; 

  ir::context cont;
  ir::context::iterator A = cont.insert(cont.begin(), ir::node("A")),
                        B = cont.insert(cont.begin(), ir::node("B")),
                        C = cont.insert(cont.begin(), ir::node("C"));

  (*C).links.push_back(ir::link(C, A, ir::INHERITANCE));
  (*C).links.push_back(ir::link(C, B, ir::INHERITANCE));
  (*B).links.push_back(ir::link(B, A, ir::INHERITANCE));

  std::string generated;
  iterator sink(generated);
  grammar gram;
  
  if (!karma::generate(sink, gram, cont))
    std::cout << "generation failed\n";

  else
    std::cout << generated;
}

