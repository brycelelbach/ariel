#include "XML/api/Document.hpp"

#include "llvm/Support/Format.h"

using namespace ariel;
using namespace ariel::XML;

Document::Document (
  std::string const& name, llvm::raw_ostream& out, 
  double version, std::string encoding
):
  indent(0),
  finalized(false),
  root(name, *this),
  out(out)
{
  out << "<?xml version=\""
      << llvm::format("%1.1lf", version)
      << "\" encoding=\""
      << encoding
      << "\"?>\n";
}

Document::~Document (void) {
  if (!finalized) {
    root.writeNode();
    finalized = true;
  }
}

Node& Document::getRoot (void) {
  return root;
}

void Document::Finalize (void) {
  if (!finalized) {
    root.writeNode();
    finalized = true;
  }
}
