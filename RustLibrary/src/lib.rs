#[warn(unused_imports)]
#[warn(non_snake_case)]
#[warn(non_camel_case_types)]

use std::os::raw::{c_char, c_int};
use std::ffi::CStr;

#[unsafe(no_mangle)]
pub extern "C" fn RustPrint(a : c_int, b : c_int) {
    println!("{}", a + b);
} 