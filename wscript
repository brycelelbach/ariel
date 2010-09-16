# /ariel top-level waf script
#
# (C) Copyright 2010 Bryce Lelbach
#
# Use, modification and distribution is subject to the Boost Software License,
# Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

top = '.'
out = 'build'

def set_options(opt):
  opt.tool_options('compiler_cxx')

  opt.add_option(
    '--llvmdir', 
    action='store',
    default='/usr/local/include/',
    help='LLVM include directory [default: /usr/local/include/]'
  )
  
  opt.add_option(
    '--clangdir',
    action='store',
    default='/usr/local/include/',
    help='Clang include directory [default: /usr/local/include/]'
  )

def configure(conf):
  conf.check_tool('compiler_cxx')

  from Options import options

  conf.env.LLVMPATH  = options.llvmdir
  conf.env.CLANGPATH = options.clangdir

def build(bld):
  bld.recurse('Profiler')
