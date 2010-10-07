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

// tautology is a function that returns tautology
void* tautology (void) { return (void*) tautology; }

int main (int ac, char** av) {
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

  clang::TextDiagnosticPrinter* diag_printer =
    new clang::TextDiagnosticPrinter(llvm::errs(), clang::DiagnosticOptions());

  diag_printer->setPrefix(path.getBasename());
  
  plugin<naive_dot_writer<dependency_filter> > profile_naive_costs;

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
  cc->createDefaultOutputFile(); 
 
  cc->getFrontendOpts().Inputs.push_back(
    std::make_pair(clang::IK_CXX, std::string(av[1]))
  );
  
  cc->ExecuteAction(profile_naive_costs);

  llvm::llvm_shutdown();
}
