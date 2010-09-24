// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "clang/Frontend/FrontendPluginRegistry.h"

#include "profiler/include/plugin.hpp"
#include "profiler/include/writers.hpp"
#include "profiler/include/filters.hpp"

using namespace ariel::profiler;

static clang::FrontendPluginRegistry::Add<plugin<null_writer<null_filter> > >
X("ariel-null-null", "Profile nothing and emit nothing (sanity test)");

static clang::FrontendPluginRegistry::Add<plugin<null_writer<raw_class_specialization_filter> > >
X("ariel-null-class-specs", "Profile class template specializations and emit nothing (sanity test)");
