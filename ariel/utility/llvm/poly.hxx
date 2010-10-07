//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_PP_POLY_HXX)
#define ARIEL_PP_POLY_HXX

#define ARIEL_IF_NOT_DYN_CAST(Derived, Var, Value)  \
  Derived *Var = llvm::dyn_cast<Derived>(Value);    \
  if (!Var)                                         \
  /**/

#define ARIEL_IF_DYN_CAST(Derived, Var, Value)      \
  Derived *Var = llvm::dyn_cast<Derived>(Value);    \
  if (Var)                                          \
  /**/

#endif // ARIEL_PP_POLY_HXX

