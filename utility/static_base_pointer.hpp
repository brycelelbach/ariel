// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_STATIC_BASE_POINTER_HPP)
#define ARIEL_STATIC_BASE_POINTER_HPP

namespace ariel {

class static_base_pointer {
 private:
  std::size_t const type;

 public:
  template<class Derived>
  static_base_pointer (Derived const& derived):
    type(Derived::id::value) { }

  template<class Derived>
  bool isa (void) {
    return Derived::id::value == type; 
  }

  template<class Derived>
  Derived* cast (void) {
    return static_cast<Derived*>(this);
  }
};

} // ariel

#endif // ARIEL_STATIC_BASE_POINTER_HPP

