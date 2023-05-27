#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm-c/Core.h"
#include "llvm-c/IRReader.h"

#include <iostream>

using namespace llvm;

extern "C"
{

    LLVMModuleRef LLVMParseAssemblyString(const char *input_data,
                                          size_t input_data_length,
                                          const char *data_layout_str,
                                          size_t data_layout_str_len,
                                          LLVMContextRef context)
    {
        auto input_sref = StringRef(input_data, input_data_length);
        SMDiagnostic diag;
        Module *m = parseAssemblyString(input_sref, diag, *unwrap(context)).release();

        if (!m)
        {
            diag.print("IR parsing failed: ", errs());
            return NULL;
        }

        auto m_ref = wrap(m);
        auto dl_sref = StringRef(data_layout_str, data_layout_str_len);
        m->setDataLayout(dl_sref);

        return m_ref;
    }
}