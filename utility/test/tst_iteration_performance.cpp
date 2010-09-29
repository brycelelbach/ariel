// Copyright 2010 Bryce Lelbach
// Copyright (c) 2001-2010 Joel de Guzman
// 
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "utility/measure.hpp"
#include "utility/tst.hpp"

#include <boost/preprocessor.hpp>

#include <boost/spirit/home/qi/string/tst.hpp>

namespace {
  volatile double global_val;

  struct foreach_functor {
    void operator() (std::string prefix, double val) { 
      global_val = val - global_val;
    }
  };

  struct spirit_test: ariel::test_base {
    void benchmark (void) {
      boost::spirit::qi::tst<char, double> t;

      std::string s0("The"),
                  s1("quick"),
                  s2("brown"),
                  s3("fox"),
                  s4("jumps"),
                  s5("over"),
                  s6("the"),
                  s7("lazy"),
                  s8("dog"),
                  m0("Thyzine"),
                  m1("doggedly"),
                  m2("zeta"),
                  m3("lazily"),
                  m4("jump");

      val = 0;

      #define ADD(z, c, _) t.add(s ## c .begin(), s ## c .end(), ++val);
      BOOST_PP_REPEAT(9, ADD, _)
      #undef ADD

      t.for_each(foreach_functor()); 
    }
  };

  struct ariel_test: ariel::test_base {
    void benchmark (void) {
      ariel::tst<std::string, double> t;

      std::string s0("The"),
                  s1("quick"),
                  s2("brown"),
                  s3("fox"),
                  s4("jumps"),
                  s5("over"),
                  s6("the"),
                  s7("lazy"),
                  s8("dog"),
                  m0("Thyzine"),
                  m1("doggedly"),
                  m2("zeta"),
                  m3("lazily"),
                  m4("jump");

      val = 0;

      #define ADD(z, c, _) t.add(s ## c .begin(), s ## c .end(), ++val);
      BOOST_PP_REPEAT(9, ADD, _)
      #undef ADD

      for (ariel::tst<std::string, double>::iterator it = t.begin(),
                                                     end = t.end();
           it != end; ++it)
      {
        global_val = *it - global_val;
      } 
    }
  };
}

int main (void) {
  ARIEL_TEST_BENCHMARK(
    10000000,  
    (spirit_test)(ariel_test) 
  )
    
  return ariel::live_code != 0;
}

