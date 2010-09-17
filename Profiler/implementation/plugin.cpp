// Implements ariel.Profiler as a Clang shared object plugin
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/AST.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Frontend/CompilerInstance.h"

#include "llvm/Support/raw_ostream.h"

using namespace clang;

namespace ariel {

class ProfilerConsumer:
  public ASTConsumer,
  public RecursiveASTVisitor<ProfilerConsumer>
{
};

class ProfilerAction: public PluginASTAction {
 protected:
  void ExecuteAction() {
    CompilerInstance &CI = getCompilerInstance();

    if (hasCodeCompletionSupport() &&
        !CI.getFrontendOpts().CodeCompletionAt.FileName.empty())
      CI.createCodeCompletionConsumer();

    CodeCompleteConsumer *CompletionConsumer = 0;
    if (CI.hasCodeCompletionConsumer())
      CompletionConsumer = &CI.getCodeCompletionConsumer();

    if (!CI.hasSema())
      CI.createSema(usesCompleteTranslationUnit(), CompletionConsumer);

    ParseAST(CI.getSema(), CI.getFrontendOpts().ShowStats);
  }

  ASTConsumer *CreateASTConsumer(CompilerInstance &CI, llvm::StringRef) {
    return new ProfilerConsumer();
  }

  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string>& args) {
    for (unsigned i = 0, e = args.size(); i != e; ++i) {
      llvm::errs() << "Profiler arg = " << args[i] << "\n";

      // Example error handling.
      if (args[i] == "-an-error") {
        Diagnostic &D = CI.getDiagnostics();
        unsigned DiagID = D.getCustomDiagID(
          Diagnostic::Error, "invalid argument '" + args[i] + "'");
        D.Report(DiagID);
        return false;
      }
    }

    if (args.size() && args[0] == "help") {
      PrintHelp(llvm::errs());
    }

    return true;
  }

  void PrintHelp (llvm::raw_ostream& ros) {
    ros << "<insert help here>\n";
  }
};

}

static FrontendPluginRegistry::Add<ariel::ProfilerAction>
X("ariel-profiler", "profile template instantiations");
