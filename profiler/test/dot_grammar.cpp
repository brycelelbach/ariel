#include "profiler/include/grammar/dot.hpp"

#include <iostream>

using namespace ariel;

int main (void) {
  typedef std::back_insert_iterator<std::string> iterator;
  typedef profiler::dot_digraph_grammar<iterator> grammar; 
  typedef std::list<ir::node>::iterator node;

  std::list<ir::node> nodes;

  node A = nodes.insert(nodes.begin(), ir::node());
  node B = nodes.insert(nodes.begin(), ir::node());
  node C = nodes.insert(nodes.begin(), ir::node());

  // struct A { };
  // struct B: A { };
  // struct C: B, virtual A { };

  (*A).name = "A"; 
  (*B).name = "B";
  (*C).name = "C";

  (*C).links.push_back(ir::link(A, ir::UPWARDS, ir::INHERITANCE));
  (*C).links.push_back(ir::link(B, ir::UPWARDS, ir::INHERITANCE));
  (*B).links.push_back(ir::link(A, ir::UPWARDS, ir::INHERITANCE));

  std::string generated;
  iterator sink(generated);
  grammar g;
  
  if (!karma::generate(sink, g, *C))
    std::cout << "generation failed\n";

  else
    std::cout << generated;
}

