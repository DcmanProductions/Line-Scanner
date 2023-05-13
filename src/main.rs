use std::ffi::c_char;
use std::io;
use std::io::Read;
use std::fs;

fn main() {
    println!("Hello, world!");



    /// End of application.
    print!("Press any key to continue...");
    let mut buffer = [0; 1];
    let _ = io::stdin().read(&mut buffer);
}
