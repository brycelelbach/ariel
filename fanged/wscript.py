#!/usr/bin/env python

"""
/fanged waf build script

(C) Copyright 2010 Bryce Lelbach

Use, modification and distribution of this software is subject to the Boost
Software License, Version 1.0, and the new BSD License.

Boost relative to repository root: /credit/BOOST_LICENSE_1_0.rst
Boost online: http://www.boost.org/LICENSE_1_0.txt
"""

def build(bld):
  bld.new_task_gen(
    features     = ['cxx', 'cprogram'], 
    source       = ['bootstrap_bill.cxx'],
    target       = 'fanged',
    install_path = '${PREFIX}/bin/',
    includes     = [bld.srcnode.abspath()],
    libpath      = '/usr/local/lib',

    defines      = [
      '__STDC_LIMIT_MACROS', '__STDC_CONSTANT_MACROS',
      'BOOST_NO_TYPEID', 'BOOST_NO_RTTI'
    ],
    
    cxxflags     = [
      '-fno-strict-aliasing', '-fPIC', '-fno-rtti',
      '-fdiagnostics-show-option', '-pedantic', '-Wall',
    ],

    lib          = [
      'pthread', 'dl', 'm', 'clangFrontend', 'clangSerialization', 'clangDriver',
      'clangCodeGen', 'clangSema', 'clangChecker', 'clangAnalysis',
      'clangRewrite', 'clangAST', 'clangParse', 'clangLex',
      'clangBasic', 'LLVMPIC16Passes', 'LLVMMCDisassembler',
      'LLVMXCoreCodeGen', 'LLVMXCoreAsmPrinter', 'LLVMXCoreInfo',
      'LLVMSystemZCodeGen', 'LLVMSystemZAsmPrinter', 'LLVMSystemZInfo',
      'LLVMSparcCodeGen', 'LLVMSparcAsmPrinter', 'LLVMSparcInfo',
      'LLVMPowerPCCodeGen', 'LLVMPowerPCAsmPrinter', 'LLVMPowerPCInfo',
      'LLVMPTXCodeGen', 'LLVMPTXAsmPrinter', 'LLVMPTXInfo',
      'LLVMPIC16AsmPrinter', 'LLVMPIC16CodeGen', 'LLVMPIC16Info',
      'LLVMMipsAsmPrinter', 'LLVMMipsCodeGen', 'LLVMMipsInfo',
      'LLVMMSP430CodeGen', 'LLVMMSP430AsmPrinter', 'LLVMMSP430Info',
      'LLVMMBlazeAsmPrinter', 'LLVMMBlazeCodeGen', 'LLVMMBlazeInfo',
      'LLVMLinker', 'LLVMipo', 'LLVMInterpreter', 'LLVMInstrumentation',
      'LLVMJIT', 'LLVMExecutionEngine', 'LLVMCppBackend',
      'LLVMCppBackendInfo', 'LLVMCellSPUCodeGen', 'LLVMCellSPUAsmPrinter',
      'LLVMCellSPUInfo', 'LLVMCBackend', 'LLVMCBackendInfo',
      'LLVMBlackfinCodeGen', 'LLVMBlackfinAsmPrinter', 'LLVMBlackfinInfo',
      'LLVMBitWriter', 'LLVMX86Disassembler', 'LLVMX86AsmParser',
      'LLVMX86CodeGen', 'LLVMX86AsmPrinter', 'LLVMX86Info',
      'LLVMAsmParser', 'LLVMARMDisassembler', 'LLVMARMAsmParser',
      'LLVMARMCodeGen', 'LLVMARMAsmPrinter', 'LLVMARMInfo',
      'LLVMArchive', 'LLVMBitReader', 'LLVMAlphaCodeGen',
      'LLVMSelectionDAG', 'LLVMAlphaAsmPrinter', 'LLVMAsmPrinter',
      'LLVMMCParser', 'LLVMCodeGen', 'LLVMScalarOpts', 'LLVMInstCombine',
      'LLVMTransformUtils', 'LLVMipa', 'LLVMAnalysis', 'LLVMTarget',
      'LLVMMC', 'LLVMCore', 'LLVMAlphaInfo', 'LLVMSupport',
      'LLVMSystem'
    ]
  );

if __name__ == '__main__':
  print '\033[91mError: Waf scripts should not be executed directly.'
  print 'Execute the Waf driver from the top of the repository instead.\033[0m'

