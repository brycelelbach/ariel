#include "utility/tst.hpp"

using namespace ariel;

int main (void) {
  tst<std::string, int> a;

  std::string foo("foo"),
              bar("bar");

  a.add(foo.begin(), foo.end(), 5);
  a.insert(bar.begin(), bar.end(), 17);
  a.insert("fubar", 3);
  a.insert(std::pair<std::string, int>("bario", 12));
}

