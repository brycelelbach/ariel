#include "XML/api/Document.hpp"
#include "XML/api/Tree.hpp"

using namespace ariel;
using namespace ariel::XML;

int main (void) {
  Tree root("test");
  
  root.addChild("foo");
  root.addChild("bar");
  root.addChild("gab");

  Document doc(root, llvm::outs());
}
