#!/usr/bin/env python

"""
top-level waf build script

(C) Copyright 2010 Bryce Lelbach

Use, modification and distribution of this software is subject to the Boost
Software License, Version 1.0.

Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
Online: http://www.boost.org/LICENSE_1_0.txt
"""

from time import strftime

top       = '.'
out       = 'build'
APPNAME   = 'ariel'
VERSION   = strftime('%y.%m.%d')
LOCAL_CXX = 'c++'

def set_options(opt):
  opt.tool_options('compiler_cxx')

  opt.add_option(
    '--llvmdir', 
    action  = 'store',
    default = '/usr/local/include/',
    help    = 'LLVM include directory [default: /usr/local/include/]'
  )
  
  opt.add_option(
    '--clangdir',
    action  = 'store',
    default = '/usr/local/include/',
    help    = 'clang include directory [default: /usr/local/include/]'
  )

def configure(conf):
  conf.check_tool('compiler_cxx')

  conf.env.__ARIEL__ = VERSION 
  conf.env.__ariel__ = VERSION
  conf.env.ARIEL     = VERSION
  conf.env.ariel     = VERSION

  from Options import options

  conf.env.LLVMPATH  = options.llvmdir
  conf.env.CLANGPATH = options.clangdir

  conf.env.CXX = [LOCAL_CXX]
  conf.env.CXXFLAGS  += ['-g']

def build(bld):
  bld.recurse('lib/profiler')

if __name__ == '__main__':
  print '\033[91mError: Waf scripts should not be executed directly.'
  print 'Execute the Waf driver from the top of the repository instead.\033[0m'

