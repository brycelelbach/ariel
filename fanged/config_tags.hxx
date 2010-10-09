//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(FANGED_CONFIG_TAGS_HXX)
#define FANGED_CONFIG_TAGS_HXX

#include <clang/Basic/LangOptions.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Frontend/AnalyzerOptions.h>
#include <clang/Frontend/CodeGenOptions.h>
#include <clang/Frontend/DependencyOutputOptions.h>
#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/FrontendOptions.h>
#include <clang/Frontend/HeaderSearchOptions.h>
#include <clang/Frontend/PreprocessorOptions.h>
#include <clang/Frontend/PreprocessorOutputOptions.h>

namespace fanged {
namespace tag {

struct target { typedef clang::TargetOptions type; };
struct frontend { typedef clang::FrontendOptions type; };
struct analyzer { typedef clang::AnalyzerOptions type; };
struct code_generation { typedef clang::CodeGenOptions type; };
struct dependency_output { typedef clang::DependencyOutputOptions type; };
struct diagnostic { typedef clang::DiagnosticOptions type; };
struct header_search { typedef clang::HeaderSearchOptions type; };
struct preprocessor { typedef clang::PreprocessorOptions type; };
struct preprocessor_output { typedef clang::PreprocessorOutputOptions type; };
struct language { typedef clang::LangOptions type; };

} // tag
} // fanged

#endif // FANGED_CONFIG_TAGS_HXX
