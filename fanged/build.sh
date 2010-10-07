clang++ -I/home/wash/ariel/  \
  -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS \
  -fno-rtti -fPIC \
  -L/usr/local/lib \
  -lpthread -ldl -lm main.cxx -o main \
  -lclangFrontend -lclangSerialization -lclangDriver \
  -lclangCodeGen -lclangSema -lclangChecker -lclangAnalysis \
  -lclangRewrite -lclangAST -lclangParse -lclangLex -lclangBasic \
  -lLLVMPIC16Passes -lLLVMMCDisassembler -lLLVMXCoreCodeGen -lLLVMXCoreAsmPrinter -lLLVMXCoreInfo -lLLVMSystemZCodeGen -lLLVMSystemZAsmPrinter -lLLVMSystemZInfo -lLLVMSparcCodeGen -lLLVMSparcAsmPrinter -lLLVMSparcInfo -lLLVMPowerPCCodeGen -lLLVMPowerPCAsmPrinter -lLLVMPowerPCInfo -lLLVMPTXCodeGen -lLLVMPTXAsmPrinter -lLLVMPTXInfo -lLLVMPIC16AsmPrinter -lLLVMPIC16CodeGen -lLLVMPIC16Info -lLLVMMipsAsmPrinter -lLLVMMipsCodeGen -lLLVMMipsInfo -lLLVMMSP430CodeGen -lLLVMMSP430AsmPrinter -lLLVMMSP430Info -lLLVMMBlazeAsmPrinter -lLLVMMBlazeCodeGen -lLLVMMBlazeInfo -lLLVMLinker -lLLVMipo -lLLVMInterpreter -lLLVMInstrumentation -lLLVMJIT -lLLVMExecutionEngine -lLLVMCppBackend -lLLVMCppBackendInfo -lLLVMCellSPUCodeGen -lLLVMCellSPUAsmPrinter -lLLVMCellSPUInfo -lLLVMCBackend -lLLVMCBackendInfo -lLLVMBlackfinCodeGen -lLLVMBlackfinAsmPrinter -lLLVMBlackfinInfo -lLLVMBitWriter -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86AsmPrinter -lLLVMX86Info -lLLVMAsmParser -lLLVMARMDisassembler -lLLVMARMAsmParser -lLLVMARMCodeGen -lLLVMARMAsmPrinter -lLLVMARMInfo -lLLVMArchive -lLLVMBitReader -lLLVMAlphaCodeGen -lLLVMSelectionDAG -lLLVMAlphaAsmPrinter -lLLVMAsmPrinter -lLLVMMCParser -lLLVMCodeGen -lLLVMScalarOpts -lLLVMInstCombine -lLLVMTransformUtils -lLLVMipa -lLLVMAnalysis -lLLVMTarget -lLLVMMC -lLLVMCore -lLLVMAlphaInfo -lLLVMSupport -lLLVMSystem
