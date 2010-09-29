#!/usr/bin/env python

"""
/utility waf build script

(C) Copyright 2010 Bryce Lelbach

Use, modification and distribution of this software is subject to the Boost
Software License, Version 1.0, and the new BSD License.

Boost relative to repository root: /doc/BOOST_LICENSE_1_0.rst
Boost online: http://www.boost.org/LICENSE_1_0.txt
"""

def build(bld):
  bld.new_task_gen(
    features     = ['cxx', 'cprogram'], 
    target       = 'ariel.test.casting',
    includes     = [bld.srcnode.abspath()],
    source       = ['test/casting.cpp'],
    cxxflags     = ['-pedantic', '-Wall']
  );

  bld.new_task_gen(
    features     = ['cxx', 'cprogram'], 
    target       = 'ariel.test.tst_instantiation',
    includes     = [bld.srcnode.abspath()],
    source       = ['test/tst_instantiation.cpp'],
    cxxflags     = ['-pedantic', '-Wall']
  );

  bld.new_task_gen(
    features     = ['cxx', 'cprogram'], 
    target       = 'ariel.test.tst_insertion',
    includes     = [bld.srcnode.abspath()],
    source       = ['test/tst_insertion.cpp'],
    cxxflags     = ['-pedantic', '-Wall']
  );

  bld.new_task_gen(
    features     = ['cxx', 'cprogram'], 
    target       = 'ariel.test.tst_lookup',
    includes     = [bld.srcnode.abspath()],
    source       = ['test/tst_lookup.cpp'],
    cxxflags     = ['-pedantic', '-Wall']
  );

if __name__ == '__main__':
  print '\033[91mError: Waf scripts should not be executed directly.'
  print 'Execute the Waf driver from the top of the repository instead.\033[0m'

