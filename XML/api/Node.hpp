#if !defined(ARIEL_XML_NODE_HPP)
#define ARIEL_XML_NODE_HPP

#include <string>
#include <list>
#include <map>

namespace ariel {
namespace XML {

class Document;

class Node {
 public:
  Node (std::string const& name, Document& document);

  Node& addChild (std::string const& name);

  bool addAttribute (std::string const& name, std::string const& value);

  void writeNode (void);

 private:
  const std::string                   name;
  Document&                           document;
  std::map<std::string, std::string>  attributes; 
  std::list<Node>                     children;
};

} // XML
} // ariel

#endif // ARIEL_XML_NODE_HPP

