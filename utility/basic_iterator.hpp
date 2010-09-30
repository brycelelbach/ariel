// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_BASIC_ITERATOR_HPP)
#define ARIEL_BASIC_ITERATOR_HPP

#include <iterator>

#include <boost/swap.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp> 

namespace ariel {

struct trivial_iterator_tag { };

// a pointer-like class fulfilling STL TrivialIterator
template<typename T>
struct basic_iterator {
 public:
  T data;

  typedef typename boost::call_traits<T>::param_type param_type;

  // STL TrivialIterator
  typedef T                                          value_type;

  // STL iterator_traits
  typedef std::ptrdiff_t                             difference_type;
  typedef typename boost::add_pointer<T>::type       pointer;
  typedef typename boost::add_reference<T>::type     reference; 
  typedef trivial_iterator_tag                       iterator_category;

  // STL DefaultConstructible
  basic_iterator (void): data() { } 

  basic_iterator (param_type newdata): data(newdata) { } 

  // STL Assignable
  basic_iterator (basic_iterator const& rhs): data(rhs.data) { }
  
  // STL Assignable 
  basic_iterator& operator= (basic_iterator const& rhs) {
    data = rhs.data;
    return *this;
  }
 
  // alias for operator=
  basic_iterator& assign (basic_iterator const& rhs) {
    return *this = rhs;
  } 
 
  // STL Assignable
  void swap (basic_iterator& rhs) { boost::swap(*this, rhs); }

  // STL EqualityComparable
  bool operator== (basic_iterator const& rhs) const { return data == rhs.data; }
  
  // STL EqualityComparable
  bool operator!= (basic_iterator const& rhs) const { return data != rhs.data; }

  // STL TrivialIterator
  reference operator* (void) const { return const_cast<T&>(data); }

  // alias for operator*
  reference get (void) const { return **this; }
 
  // STL TrivialIterator
  pointer operator-> (void) const { return &data; }
};

} // ariel

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (T),
  (ariel::basic_iterator) (T),
  (T, data)
)

#endif // ARIEL_BASIC_ITERATOR_HPP

