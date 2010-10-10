//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(FANGED_MODULE_ACTION_HXX)
#define FANGED_MODULE_ACTION_HXX

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/AST.h>
#include <clang/Frontend/CompilerInstance.h>

namespace fanged {

class module_action: public clang::ASTFrontendAction {
 public:
  virtual void parse_args (clang::CompilerInstance& cc) = 0;
};

} // fanged 

#endif // FANGED_MODULE_ACTION_HXX
