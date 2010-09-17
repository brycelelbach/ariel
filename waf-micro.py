#!/usr/bin/env python

"""
driver for the waf build system (Ariel waf-light fork)

(C) Copyright 2010 Bryce Lelbach
(C) Copyright 2005-2009 Thomas Nagy

Use, modification and distribution of this software is subject to the Boost
Software License, Version 1.0, and the new BSD License.

Boost relative to repository root: /doc/BOOST_LICENSE_1_0.rst
Boost online: http://www.boost.org/LICENSE_1_0.txt
BSD relative to repository root: /doc/NEW_BSD_LICENSE.txt
BSD online: http://www.opensource.org/licenses/bsd-license.php
"""

from sys import path as syspath
from sys import exit
from sys import hexversion as PYVERSION
from os.path import join, abspath

if __name__ == '__main__':
  # check the python version
  if PYVERSION < 0x203000f:
    raise ImportError("Waf requires Python >= 2.3")

  # we like absolute paths
  cwd        = abspath(getcwd())
  wafadmin   = abspath(join(cwd, 'wafadmin'))
  tools      = abspath(join(wafadmin, 'Tools')
  thirdparty = abspath(join(wafadmin, '3rdparty'))

  # add the local waf install to the search path
  syspath = [wafadmin, tools, thirdparty] + syspath

  # now we can boostrap waf
  from Scripting import prepare
  from Constants import WAFVERSION 

  # hand things over to waf
  prepare(tools, cwd, WAFVERSION, wafadmin)

  exit(0)

