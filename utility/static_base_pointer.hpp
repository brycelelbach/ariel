// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_STATIC_BASE_POINTER_HPP)
#define ARIEL_STATIC_BASE_POINTER_HPP

#include <typeinfo>
#include <cstring>
#include <iostream>

namespace ariel {

class static_base_pointer {
 private:
  char const* type;

 public:
  template<class Derived>
  static_base_pointer (Derived const& derived):
    type(typeid(Derived()).name()) { }

  template<class Derived>
  bool isa (void) {
    return !bool(std::strcmp(typeid(Derived()).name(), type));
  }

  template<class Derived>
  Derived* cast (void) {
    return static_cast<Derived*>(this);
  }
};

} // ariel

#endif // ARIEL_STATIC_BASE_POINTER_HPP

