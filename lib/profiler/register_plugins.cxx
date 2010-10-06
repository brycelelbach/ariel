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

static clang::FrontendPluginRegistry::Add<plugin<
  naive_dot_writer<dependency_filter> >
> ariel_naive_costs(
  "ariel-naive-costs",
  "Generate DOT output describing template instantiation costs (naive style)"
);

static clang::FrontendPluginRegistry::Add<plugin<
  cross_dot_writer<dependency_filter> >
> ariel_cross_costs(
  "ariel-cross-costs",
  "Generate DOT output describing template instantiation costs (cross style)"
);

