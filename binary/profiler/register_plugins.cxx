//===-----------------------------------------------------------*- C++ -*-===//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#include <clang/Frontend/FrontendPluginRegistry.h>

#include <ariel/profiler/plugin.hxx>
#include <ariel/profiler/writers.hxx>
#include <ariel/profiler/filters.hxx>

using namespace ariel::profiler;

static clang::FrontendPluginRegistry::Add<plugin<null_writer<type_dependency_filter> > >
C("ariel-type-dependencies", "Profile template instantiation costs");
