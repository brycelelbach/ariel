// Copyright 2010 Bryce Lelbach
// Copyright (c) 2001-2010 Joel de Guzman
// 
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "utility/measure.hpp"

namespace {
  struct f: ariel::test_base {
    void benchmark (void) {
      val += 5;
    }
  };
}

int main (void) {
  ARIEL_TEST_BENCHMARK(
    10000000,  
    (f)        
  )
    
  return ariel::live_code != 0;
}

