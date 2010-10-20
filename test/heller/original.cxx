//===------------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Thomas Heller, Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

template <bool Cond, typename Then, typename Else>
struct lazy_if_c {
  typedef typename Then::type type;
};

template <typename Then, typename Else>
struct lazy_if_c<false, Then, Else> {
  typedef typename Else::type type;
};

template <typename Cond, typename Then, typename Else>
struct lazy_if: lazy_if_c<Cond::value, Then, Else> { };

template <bool Cond, typename Then, typename Else>
struct if_c {
  typedef Then type;
};

template <typename Then, typename Else>
struct if_c<false, Then, Else> {
  typedef Else type;
};

template <typename Cond, typename Then, typename Else>
struct if_: if_c<Cond::value, Then, Else> { };

template <typename T>
struct identity {
  typedef T type;
};

template <bool Value> struct bool_{
  static bool const value = Value;
};

typedef bool_<false> false_;
typedef bool_<true> true_;

template <typename T1, typename T2>
struct is_same: false_ { };

template <typename T>
struct is_same<T, T>: true_ { };

int main (void) {
  {
    lazy_if<is_same<float, double>, identity<int>, identity<short> >::type i;
    lazy_if_c<is_same<float, double>::value, identity<int>, identity<short> >::type j;
    
    lazy_if<is_same<float, float>, identity<int>, identity<short> >::type k;
    lazy_if_c<is_same<float, float>::value, identity<int>, identity<short> >::type l;
  }

  {
    if_<is_same<float, double>, int, short>::type i;
    if_c<is_same<float, double>::value, int, short>::type j;
    
    if_<is_same<float, float>, int, short>::type k;
    if_c<is_same<float, float>::value, int, short>::type l;
  }
}
