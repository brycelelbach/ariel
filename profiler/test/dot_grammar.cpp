#include "profiler/include/grammar/dot.hpp"

#include <iostream>

using namespace ariel;
using namespace ariel::profiler;

int main (void) {
  typedef std::back_insert_iterator<std::string> iterator;
  typedef dot_digraph_grammar<iterator> grammar; 

  ir::node n;

  n.name = "node";

  std::string generated;
  iterator sink(generated);
  grammar g;
  
  if (!karma::generate(sink, g, n))
    std::cout << "generation failed\n";

  else
    std::cout << "generated:\n" << generated << "\n";
}

