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
RELEASE   = 1
CODENAME  = 'Admiral Ackbar'
VERSION   = strftime('%Y.%m.%d_%H.%M.%S')

def set_options(opt):
  opt.tool_options('clangxx')

def configure(conf):
  conf.check_tool('clangxx')

  conf.env.ARIEL_RELEASE  = RELEASE
  conf.env.ARIEL_CODENAME = CODENAME 
  conf.env.ARIEL_APPNAME  = APPNAME 
  conf.env.ARIEL_VERSION  = VERSION 

def build(bld):
  bld.recurse('bin')

if __name__ == '__main__':
  print '\033[91mError: Waf scripts should not be executed directly.'
  print 'Execute the Waf driver from the top of the repository instead.\033[0m'

