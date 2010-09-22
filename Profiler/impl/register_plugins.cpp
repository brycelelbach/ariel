// Register clang arielProfiler plugins
//
// (C) Copyright 2010 Bryce Lelbach
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt

#include "clang/Frontend/FrontendPluginRegistry.h"

#include "Profiler/api/Plugin.hpp"

using namespace ariel;
using namespace ariel::Profiler;

static clang::FrontendPluginRegistry::Add<Plugin<NullView> >
X("ariel.Profiler.null", "Profile C++ templates (emit nothing)");

