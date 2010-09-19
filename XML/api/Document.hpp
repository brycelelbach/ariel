#if !defined(ARIEL_XML_DOCUMENT_HPP)
#define ARIEL_XML_DOCUMENT_HPP

#include "llvm/Support/raw_ostream.h"

#include <string>

namespace ariel {
namespace XML {

class Node;

class Document {
 public:
  enum BufferPolicy {
    BufferNothing,
    BufferTags,
    BufferDocument
  };

  Document (
    std::string const& root, llvm::raw_ostream& out,
    BufferPolicy policy = BufferNothing
  );

  Node& getRoot (void);

  void finalize (void); 

 private:
  Node               root;
  llvm::raw_ostream& out;
  BufferPolicy       policy;
};

} // XML
} // ariel

#endif // ARIEL_XML_DOCUMENT_HPP

