#include <vector>
#include <iostream>

#include <boost/mpl/size_t.hpp>

#include "utility/static_base_pointer.hpp"

using namespace ariel;

template<class Derived> class base {
 public:
  void interface (void) {
    static_cast<Derived*>(this)->implementation();
  }
};

class foo: public base<foo>, public static_base_pointer {
 public:
  typedef boost::mpl::size_t<0> id;

  foo (void): static_base_pointer(*this) { }
  
  void implementation (void) {
    std::cout << "foo\n";
  }
};

class bar: public base<bar>, public static_base_pointer {
 public:
  typedef boost::mpl::size_t<1> id;

  bar (void): static_base_pointer(*this) { }

  void implementation (void) {
    std::cout << "bar\n";
  }
};

int main (void) {
  std::vector<static_base_pointer*> foos_and_bars;

  foos_and_bars.push_back(new foo());
  foos_and_bars.push_back(new bar());
  foos_and_bars.push_back(new bar());
  foos_and_bars.push_back(new foo());
  foos_and_bars.push_back(new foo());

  static_base_pointer* it = 0;
 
  while (!foos_and_bars.empty()) {
    it = foos_and_bars.back();
    foos_and_bars.pop_back();

    if (!it) continue;

    if (it->isa<foo>()) { 
      foo* f = it->cast<foo>();
      f->interface();
      delete f; // make sure foo data is destroyed
    }
 
    else if (it->isa<bar>()) { 
      bar* b = it->cast<bar>();
      b->interface();
      delete b; // make sure bar data is destroyed
    }

    else delete it; // shouldn't be possible
  }
}
