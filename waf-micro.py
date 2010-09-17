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

import sys
from os.path import join
from os import getcwd

if __name__ == '__main__':
  # check the python version
  if sys.hexversion < 0x203000f:
    raise ImportError("Waf requires Python >= 2.3")

  cwd        = getcwd()
  wafadmin   = join(cwd, 'wafadmin')
  tools      = join(wafadmin, 'Tools')
  thirdparty = join(wafadmin, '3rdparty')

  # add the local waf install to the search path
  sys.path = [wafadmin, tools, thirdparty] + sys.path

  # now we can boostrap waf
  from Scripting import prepare
  from Constants import WAFVERSION 

  # hand things over to waf
  prepare(tools, cwd, WAFVERSION, wafadmin)

  sys.exit(0)

