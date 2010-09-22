#include "XML/api/Tree.hpp"

#include "XML/api/Document.hpp"

#include <utility>

using namespace ariel;
using namespace ariel::XML;

Tree::Tree (std::string const& name):
  name(name),
  children() { }

std::list<Tree>::iterator Tree::addChild (std::string const& name) {
  Tree child(name);
  children.push_back(child);
  return --children.end();
}

bool Tree::addAttribute (std::string const& name, std::string const& value) {
  return attributes.insert(std::make_pair(name, value)).second;
}

void Tree::writeNode (llvm::raw_ostream& out, std::size_t indent) { 
  out.indent(indent);

  if (attributes.empty()) 
    out << "<" << name;

  else {
    std::map<std::string, std::string>::iterator it = attributes.begin(),
                                                 end = attributes.end();

    out << "<" << name << " " 
               << (*it).first
               << "=\""
               << (*it).second
               << "\"";

    std::size_t localIndent = indent + name.length() + 2; 

    while (++it != end) {
      out << "\n";

      out.indent(localIndent);

      out << (*it).first
          << "=\""
          << (*it).second
          << "\"";
    }
  }

  if (children.empty())
    out << " />\n";

  else {
    out << ">\n";

    for (std::list<Tree>::iterator it = children.begin(), end = children.end();
         it != end; ++it) (*it).writeNode(out, indent + 2);

    out.indent(indent);

    out << "</" << name << ">\n";
  }
}
