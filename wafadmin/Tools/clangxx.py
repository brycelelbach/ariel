#!/usr/bin/env python
# encoding: utf-8
# Thomas Nagy, 2006 (ita)
# Ralf Habacker, 2006 (rh)
# Yinon Ehrlich, 2009
# Bryce Lelbach, 2010

import os, sys
import Configure, Options, Utils
import ccroot, ar
from Configure import conftest

@conftest
def find_clangxx(conf):
	cxx = conf.find_program(['clang++'], var='CXX', mandatory=True)
	cxx = conf.cmd_to_list(cxx)
	ccroot.get_cc_version(conf, cxx, gcc=True)
	conf.env.CXX_NAME = 'clang'
	conf.env.CXX      = cxx

@conftest
def clangxx_common_flags(conf):
	v = conf.env

	# CPPFLAGS CXXDEFINES _CXXINCFLAGS _CXXDEFFLAGS
	v['CXXFLAGS_DEBUG']      = ['-g']
	v['CXXFLAGS_RELEASE']    = ['-O2']

	v['CXX_SRC_F']           = ''
	v['CXX_TGT_F']           = ['-c', '-o', ''] # shell hack for -MD
	v['CPPPATH_ST']          = '-I%s' # template for adding include paths

	# linker
	if not v['LINK_CXX']: v['LINK_CXX'] = v['CXX']
	v['CXXLNK_SRC_F']        = ''
	v['CXXLNK_TGT_F']        = ['-o', ''] # shell hack for -MD

	v['LIB_ST']              = '-l%s' # template for adding libs
	v['LIBPATH_ST']          = '-L%s' # template for adding libpaths
	v['STATICLIB_ST']        = '-l%s'
	v['STATICLIBPATH_ST']    = '-L%s'
	v['RPATH_ST']            = '-Wl,-rpath,%s'
	v['CXXDEFINES_ST']       = '-D%s'

	v['SONAME_ST']           = '-Wl,-h,%s'
	v['SHLIB_MARKER']        = '-Wl,-Bdynamic'
	v['STATICLIB_MARKER']    = '-Wl,-Bstatic'
	v['FULLSTATIC_MARKER']   = '-static'

	# program
	v['program_PATTERN']     = '%s'

	# shared library
	v['shlib_CXXFLAGS']      = ['-fPIC', '-DPIC'] # avoid using -DPIC, -fPIC aleady defines the __PIC__ macro
	v['shlib_LINKFLAGS']     = ['-shared']
	v['shlib_PATTERN']       = 'lib%s.so'

	# static lib
	v['staticlib_LINKFLAGS'] = ['-Wl,-Bstatic']
	v['staticlib_PATTERN']   = 'lib%s.a'

def detect(conf):
	conf.find_clangxx()
	conf.clangxx_common_flags()
	conf.cxx_load_tools()
	conf.cxx_add_flags()

