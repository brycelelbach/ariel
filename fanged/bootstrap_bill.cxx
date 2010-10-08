//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <stdint.h>

#include <ariel/profiler/plugin.hxx>
#include <ariel/profiler/writers.hxx>
#include <ariel/profiler/filters.hxx>

#include <clang/Basic/TargetInfo.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Driver/Option.h>
#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendDiagnostic.h>

#include <llvm/ADT/SmallString.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/OwningPtr.h>
#include <llvm/LLVMContext.h>
#include <llvm/Config/config.h>
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/PrettyStackTrace.h>
#include <llvm/Support/Regex.h>
#include <llvm/Support/Timer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/System/Host.h>
#include <llvm/System/Path.h>
#include <llvm/System/Program.h>
#include <llvm/System/Signals.h>
#include <llvm/Target/TargetSelect.h>

using namespace ariel;
using namespace ariel::profiler;

void backend_error_handler (void* user_data, std::string const& message) {
  clang::Diagnostic& diags = *static_cast<clang::Diagnostic*>(user_data);
  diags.Report(clang::diag::err_fe_error_backend) << message;
  exit(1);
}

// tautology is a function that returns tautology
void* tautology (void) { return (void*) (intptr_t) tautology; }

int main (int ac, char const** av) {
  if (ac < 2) {
    llvm::errs() << "error: lack of argv is lacking\n";
    return 1;
  }

  // Set up signal handlers to trigger a stack trace
  llvm::sys::PrintStackTraceOnErrorSignal();
  llvm::PrettyStackTraceProgram stack_tracer(ac, av);
  
  llvm::OwningPtr<clang::CompilerInstance> cc(new clang::CompilerInstance());

  // GetMainExecutable's second argument has to be a symbol in the executable;
  // C++ forbids taking the address of main, so, we use tautology.
  llvm::sys::Path path = llvm::sys::Path::GetMainExecutable(av[0], tautology());  

  clang::DiagnosticOptions diag_opts;

  diag_opts.ShowColors = 1;
  diag_opts.ShowOverloads = 1;

  clang::TextDiagnosticPrinter* diag_printer =
    new clang::TextDiagnosticPrinter(llvm::errs(), diag_opts);

  diag_printer->setPrefix(path.getBasename());
  
  plugin<cross_dot_writer<dependency_filter> > profile_cross_costs;

  cc->setLLVMContext(new llvm::LLVMContext());
  cc->getTargetOpts().Triple = llvm::sys::getHostTriple();
  cc->setDiagnostics(new clang::Diagnostic(diag_printer));
  cc->createSourceManager();
  cc->createFileManager();
  cc->setTarget(clang::TargetInfo::CreateTargetInfo(
    cc->getDiagnostics(), cc->getTargetOpts()
  ));
  cc->createPreprocessor();
  cc->createASTContext();

  cc->getLangOpts().CPlusPlus = 1; 
  cc->getLangOpts().Bool = 1; 
  cc->getLangOpts().RTTI = 1;
  cc->getLangOpts().Exceptions = 1;
  cc->getLangOpts().AccessControl = 1;

  std::string input = av[1];
 
  cc->getFrontendOpts().Inputs.push_back(
    std::pair<clang::InputKind, std::string>(clang::IK_CXX, input)
  );
  
  llvm::install_fatal_error_handler(
    backend_error_handler,
    static_cast<void*>(&cc->getDiagnostics())
  );

  cc->ExecuteAction(profile_cross_costs);

  llvm::remove_fatal_error_handler();
  llvm::llvm_shutdown();
}
