#include "XML/api/Node.hpp"

#include "XML/api/Document.hpp"

#include <utility>

using namespace ariel;
using namespace ariel::XML;

Node::Node (std::string const& name, Document& document):
  name(name),
  document(document),
  children() { }

Node& Node::addChild (std::string const& name) {
  Node child(name, document);
  children.push_back(child);
  return children.back();
}

bool Node::addAttribute (std::string const& name, std::string const& value) {
  return attributes.insert(std::make_pair(name, value)).second;
}

void Node::writeNode (void) { 
  document.out.indent(document.indent);

  if (attributes.empty()) 
    document.out << "<" << name;

  else {
    std::map<std::string, std::string>::iterator it = attributes.begin(),
                                                 end = attributes.end();

    document.out << "<" << name << " " 
                 << (*it).first
                 << "=\""
                 << (*it).second
                 << "\"\n";

    std::size_t indent = document.indent + name.length() + 1; 

    while (++it != end) {
      document.out.indent(indent);
      document.out << (*it).first
                   << "=\""
                   << (*it).second
                   << "\"\n";
    }

    document.out.indent(document.indent);
  }

  if (children.empty())
    document.out << " />\n";

  else {
    document.out << ">\n";

    document.indent += 2;

    for (std::list<Node>::iterator it = children.begin(), end = children.end();
         it != end; ++it) (*it).writeNode();

    document.indent -= 2;

    document.out.indent(document.indent);

    document.out << "</" << name << ">\n";
  }
}
