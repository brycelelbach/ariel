// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#if !defined(ARIEL_ADAPT_ITERATOR_HPP)
#define ARIEL_ADAPT_ITERATOR_HPP

#include <boost/swap.hpp>
#include <boost/call_traits.hpp>
#include <boost/detail/iterator.hpp>

namespace ariel {

struct trivial_iterator_tag { };

// a pointer-like class fulfilling STL TrivialIterator
template<class T>
struct adapt_iterator {
 public:
  T data;

  typedef typename boost::call_traits<T>::param_type param_type;

  // STL iterator_traits
  typedef typename boost::detail::iterator_traits<T>::value_type value_type;
  typedef typename boost::detail::iterator_traits<T>::reference reference;
  typedef typename boost::detail::iterator_traits<T>::pointer pointer;
  typedef typename boost::detail::iterator_traits<T>::difference_type difference_type;
  typedef typename boost::detail::iterator_traits<T>::iterator_category iterator_category;

  // STL DefaultConstructible
  adapt_iterator (void): data() { } 

  adapt_iterator (param_type new_data): data(new_data) { } 

  // STL Assignable
  adapt_iterator (adapt_iterator const& rhs): data(rhs.data) { }
  
  // STL Assignable 
  adapt_iterator& operator= (adapt_iterator const& rhs) {
    data = rhs.data;
    return *this;
  }
 
  // alias for operator=
  adapt_iterator& assign (adapt_iterator const& rhs) { return *this = rhs; } 
 
  // STL Assignable
  void swap (adapt_iterator& rhs) { boost::swap(*this, rhs); }

  // STL EqualityComparable
  bool operator== (adapt_iterator const& rhs) const { return data == rhs.data; }
  
  // STL EqualityComparable
  bool operator!= (adapt_iterator const& rhs) const { return data != rhs.data; }

  // STL TrivialIterator
  reference operator* (void) const { return *const_cast<T&>(data); }

  // alias for operator*
  reference get (void) const { return **this; }
 
  // STL TrivialIterator
  pointer operator-> (void) const { return &**this; }
};

} // ariel

#endif // ARIEL_ADAPT_ITERATOR_HPP

