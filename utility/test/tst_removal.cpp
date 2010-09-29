#include "utility/tst.hpp"

#include <cassert>

using namespace ariel;

int main (void) {
  tst<std::string, int> a;

  std::string foo("foo"),
              bar("bar"),
              dop("dop");

  std::string::iterator foo_it  = foo.begin(),
                        bar_it  = bar.begin();

  a.add(foo.begin(), foo.end(), 5);
  a.insert(bar.begin(), bar.end(), 17);
  a.insert("fubar", 3);
  a.insert(dop, 5);
  a.insert(std::pair<std::string, int>("bario", 12));

  assert(*a.find(foo_it, foo.end()) == 5);
  assert(*a.find(bar_it, bar.end()) == 17);
  assert(*a.find("fubar") == 3);
  assert(*a.find(dop) == 5);
  assert(*a.find("bario") == 12);

  foo_it = foo.begin();
  bar_it = bar.begin();

  a.erase(foo_it, foo.end());
  a.erase(bar_it, bar.end());
  a.erase("fubar");
  a.erase(dop);
  a.erase("bario");
  
  assert(a.find(foo_it, foo.end()) == a.end());
  assert(a.find(bar_it, bar.end()) == a.end());
  assert(a.find("fubar") == a.end());
  assert(a.find(dop) == a.end());
  assert(a.find("bario") == a.end());
}

