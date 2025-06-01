# Simple demo to show file types
.section .text
    .global _start

_start:
    movq $42, %rax      # Put 42 in return register
    movq $60, %rax      # System call: exit
    movq $0, %rdi       # Exit status: 0
    syscall 