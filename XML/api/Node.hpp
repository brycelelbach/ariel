#if !defined(ARIEL_XML_NODE_HPP)
#define ARIEL_XML_NODE_HPP

#include "llvm/Support/raw_ostream.h"

namespace ariel {
namespace XML {

class Node {
 public:
  virtual ~Node (void) { }  

  virtual void writeNode (llvm::raw_ostream& out, std::size_t indent = 0) = 0;
};

} // XML
} // ariel

#endif // ARIEL_XML_NODE_HPP

