use crate::prelude::{LLVMContextRef, LLVMModuleRef};

// Functions from our assembly wrappers, since the C interface doesn't have them
// (wrappers/assembly.cpp).
extern "C" {
    pub fn LLVMParseAssemblyString(
        input_data: *const ::libc::c_char,
        input_data_length: ::libc::size_t,
        data_layout_str: *const ::libc::c_char,
        data_layout_str_len: ::libc::size_t,
        context: LLVMContextRef,
    ) -> LLVMModuleRef;
}
