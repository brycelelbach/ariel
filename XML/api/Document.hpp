#if !defined(ARIEL_XML_DOCUMENT_HPP)
#define ARIEL_XML_DOCUMENT_HPP

#include "llvm/Support/raw_ostream.h"

#include "XML/api/Node.hpp"

#include <string>

namespace ariel {
namespace XML {

class Node;

class Document {
 friend class Node;

 public:
  Document (
    std::string const& name,
    llvm::raw_ostream& out,
    double version = 1.0,
    std::string encoding = "UTF-8"
  );

  virtual ~Document (void); 

  Node& getRoot (void);

  bool isFinalized (void) const { return finalized; }

  void Finalize (void);

 private:
  std::size_t        indent;
  bool               finalized;
  Node               root;
  llvm::raw_ostream& out;
};

} // XML
} // ariel

#endif // ARIEL_XML_DOCUMENT_HPP

