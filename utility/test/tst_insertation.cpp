#include <iostream>
#include "utility/tst.hpp"

int main (void) {
  ariel::tst<std::string, int> lookup;

  typedef ariel::tst<std::string, int>::value_type kv_pair;

  lookup.insert(kv_pair("foo", 5));
  lookup.insert(kv_pair("bar", 17));
}
