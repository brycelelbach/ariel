#!/usr/bin/env python

"""
/test/profiler waf build script

(C) Copyright 2010 Bryce Lelbach

Use, modification and distribution of this software is subject to the Boost
Software License, Version 1.0, and the new BSD License.

Boost relative to repository root: /credit/BOOST_LICENSE_1_0.rst
Boost online: http://www.boost.org/LICENSE_1_0.txt
"""

def build(bld):
  pass
#  bld.new_task_gen(
#    features     = ['cxx', 'cprogram'], 
#    source       = 'dot_grammar.cxx',
#    includes     = [bld.srcnode.abspath()],
#    target       = 'dot_grammar',
#    vnum         = bld.env.ARIEL,
#    cxxflags     = ['-Wall', '-pedantic']
#  );

if __name__ == '__main__':
  print '\033[91mError: Waf scripts should not be executed directly.'
  print 'Execute the Waf driver from the top of the repository instead.\033[0m'

