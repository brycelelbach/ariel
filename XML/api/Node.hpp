#if !defined(ARIEL_XML_NODE_HPP)
#define ARIEL_XML_NODE_HPP

#include <string>
#include <list>

namespace ariel {
namespace XML {

class Document;

class Node {
 friend class Document;

 public:
  Node (std::string const& name, Document& document);
  Node (std::string const& name, Node& parent);

  Node& addChild (std::string const& name);
  Node& addSibling (std::string const& name);

  template<typename Value>
  Node& addAttribute (std::string const& name);

 private:
  Document&                 document;
  std::list<Node>           children;
  std::list<Node>::iterator parent;
};

} // XML
} // ariel

#endif // ARIEL_XML_NODE_HPP

