//===-----------------------------------------------------------*- C++ -*-===//
// bootstrap_bill.cxx will load your modules
// 
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <llvm/Support/PrettyStackTrace.h>

#include <fanged/cmdline/compiler.hxx>

// tautology is a function that returns tautology
void* tautology (void) { return (void*) (intptr_t) tautology; }

int main (int const argc, char const** argv) { 
  // set up signal handlers to trigger a stack trace
  llvm::sys::PrintStackTraceOnErrorSignal();

  // instantiate a stack tracer
  llvm::PrettyStackTraceProgram stack_tracer(argc, argv);

  // instantiate the compiler 
  boost::scoped_ptr<fanged::cmdline::compiler<> > cc(
    new fanged::cmdline::compiler<>(argc, argv, tautology())
  );

  llvm::llvm_shutdown();
}
