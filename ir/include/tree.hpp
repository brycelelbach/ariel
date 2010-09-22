#if !defined(ARIEL_XML_TREE_HPP)
#define ARIEL_XML_TREE_HPP

#include "llvm/Support/raw_ostream.h"

#include "XML/api/Node.hpp"

#include <string>
#include <list>
#include <map>

namespace ariel {
namespace XML {

class Tree: public Node {
 public:
  Tree (std::string const& name);

  std::list<Tree>::iterator addChild (std::string const& name = "node");

  bool addAttribute (std::string const& name, std::string const& value);

  void changeName (std::string const& newName) { name = newName; }

  void writeNode (llvm::raw_ostream& out, std::size_t indent = 0);

  std::list<Tree>::iterator begin (void) { return children.begin(); }
  std::list<Tree>::const_iterator begin (void) const { return children.begin(); }

  std::list<Tree>::iterator end (void) { return children.end(); }
  std::list<Tree>::const_iterator end (void) const { return children.end(); }

 private:
  std::string                         name;
  std::map<std::string, std::string>  attributes; 
  std::list<Tree>                     children;
};

} // XML
} // ariel

#endif // ARIEL_XML_TREE_HPP

