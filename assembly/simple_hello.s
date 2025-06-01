# ==========================================================================
# Simple Assembly Hello World - Actually Runnable!
# ==========================================================================
# This is a minimal assembly program that you can compile and run
# to see assembly in action. Much simpler than the tutorial file.
# ==========================================================================

.section .data
    hello_msg: .asciz "Hello from Assembly!\n"
    msg_len = . - hello_msg - 1    # Calculate length (minus null terminator)

.section .text
    .global _start

_start:
    # Write system call
    # On macOS: syscall numbers are different, but this should work on Linux
    # For macOS, you might need to adjust the syscall numbers
    
    # write(stdout, message, length)
    mov $1, %rax        # sys_write (1 on Linux, 0x2000004 on macOS)
    mov $1, %rdi        # file descriptor (stdout)
    mov $hello_msg, %rsi # message to write
    mov $msg_len, %rdx   # message length
    syscall             # invoke system call
    
    # exit(0)
    mov $60, %rax       # sys_exit (60 on Linux, 0x2000001 on macOS)
    mov $0, %rdi        # exit status
    syscall             # invoke system call

# ==========================================================================
# How to compile and run (Linux):
# as simple_hello.s -o simple_hello.o
# ld simple_hello.o -o simple_hello
# ./simple_hello
#
# For macOS, you might need:
# as simple_hello.s -o simple_hello.o
# ld simple_hello.o -o simple_hello -macosx_version_min 10.7 -lSystem -no_pie
# ./simple_hello
# ========================================================================== 