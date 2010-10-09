
//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(FANGED_CMDLINE_REGISTERED_BUILTINS_HXX)
#define FANGED_CMDLINE_REGISTERED_BUILTINS_HXX

#include <llvm/Support/raw_ostream.h>

#include <boost/preprocessor/seq/for_each.hpp>

#define FANGED_CMDLINE_REGISTERED_BUILTINS \
  ("profile.naive.dot")                    \
  ("profile.cross.dot")                    \
  /**/

namespace fanged {
namespace cmdline {

void list_builtins (llvm::raw_ostream& os) {
  #define M0(r, data, elem) << "  " << elem << "\n"

  os
    BOOST_PP_SEQ_FOR_EACH(M0, _, FANGED_CMDLINE_REGISTERED_BUILTINS)
  ;

  #undef M0
}

} // cmdline
} // fanged

#endif // FANGED_CMDLINE_REGISTERED_BUILTINS_HXX
