// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_STATIC_BASE_POINTER_HPP)
#define ARIEL_STATIC_BASE_POINTER_HPP

#if !defined(ARIEL_UNIQUE_ID_TYPE)
  #include <boost/integer.hpp>
  #define ARIEL_UNIQUE_ID_TYPE boost::uint_t<16>::fast
#endif // ARIEL_UNIQUE_ID_TYPE

namespace ariel {

class static_base_pointer {
 private:
  ARIEL_UNIQUE_ID_TYPE const type;

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

