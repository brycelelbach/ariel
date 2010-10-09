//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(FANGED_CMDLINE_STDERR_BOUND_PRINTER_HXX)
#define FANGED_CMDLINE_STDERR_BOUND_PRINTER_HXX

#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>

#include <llvm/Support/raw_ostream.h>

namespace fanged {
namespace cmdline {

// A wrapper class for TextDiagnosticPrinter, binding one of it's
// ctor arguments to allow it to be used as a template parameter
// to the compiler class without specialization of compiler.
class stderr_bound_printer: public clang::TextDiagnosticPrinter {
 public:
  stderr_bound_printer (clang::DiagnosticOptions const& diags):
    clang::TextDiagnosticPrinter(llvm::errs(), diags) { }

  virtual ~stderr_bound_printer (void) { }
};

} // cmdline 
} // fanged

#endif // FANGED_CMDLINE_STDERR_BOUND_PRINTER_HXX
