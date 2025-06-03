// ==========================================================================
// ARM64 (AArch64) Assembly Tutorial for Apple Silicon Macs
// ==========================================================================
// This tutorial is specifically for M1/M2 Macs using ARM64 architecture
// ==========================================================================

.section __TEXT,__text
.global _main
.align 2

// ==========================================================================
// ARM64 BASICS
// ==========================================================================
// ARM64 has 31 general-purpose registers (x0-x30)
// x0-x7:   Function arguments and return values
// x8:      Indirect result location register
// x9-x15:  Temporary registers
// x16-x17: Intra-procedure-call temporary registers
// x18:     Platform register (reserved)
// x19-x28: Callee-saved registers
// x29:     Frame pointer (FP)
// x30:     Link register (LR) - return address
// sp:      Stack pointer
// pc:      Program counter

// Each register can be accessed as:
// - 64-bit: x0, x1, x2, etc.
// - 32-bit: w0, w1, w2, etc. (lower 32 bits)

// ==========================================================================
// Example 1: Basic Operations
// ==========================================================================
_basic_operations:
    // Function prologue
    sub sp, sp, #16          // Allocate 16 bytes on stack
    
    // Load immediate values
    mov x0, #42              // Load 42 into x0
    mov w1, #10              // Load 10 into w1 (32-bit)
    
    // Arithmetic
    add x2, x0, x1           // x2 = x0 + x1
    sub x3, x0, #5           // x3 = x0 - 5
    mul x4, x0, x1           // x4 = x0 * x1
    
    // Store to stack
    str x2, [sp]             // Store x2 at stack pointer
    str w3, [sp, #8]         // Store w3 at sp+8
    
    // Load from stack
    ldr x5, [sp]             // Load from stack pointer
    ldr w6, [sp, #8]         // Load from sp+8
    
    // Function epilogue
    add sp, sp, #16          // Restore stack
    ret                      // Return

// ==========================================================================
// Example 2: Conditionals (If-Else)
// ==========================================================================
_check_number:
    // Input: x0 contains a number
    // Output: x0 = 1 if positive, 0 if zero/negative
    
    cmp x0, #0               // Compare x0 with 0
    ble .Lzero_or_negative   // Branch if less or equal
    
    // Positive case
    mov x0, #1
    ret
    
.Lzero_or_negative:
    mov x0, #0
    ret

// ==========================================================================
// Example 3: Loops
// ==========================================================================
_sum_to_n:
    // Input: x0 = n
    // Output: x0 = sum from 1 to n
    
    mov x1, #0               // sum = 0
    mov x2, #1               // i = 1
    
.Lloop_start:
    cmp x2, x0               // Compare i with n
    bgt .Lloop_end           // If i > n, exit loop
    
    add x1, x1, x2           // sum += i
    add x2, x2, #1           // i++
    b .Lloop_start           // Continue loop
    
.Lloop_end:
    mov x0, x1               // Return sum
    ret

// ==========================================================================
// Example 4: Function Calls
// ==========================================================================
_add_numbers:
    // Input: x0 = first number, x1 = second number
    // Output: x0 = sum
    add x0, x0, x1
    ret

_caller_example:
    // Save link register and frame pointer
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    
    // Call add_numbers(5, 3)
    mov x0, #5
    mov x1, #3
    bl _add_numbers          // Branch with link (saves return address)
    // Result is now in x0
    
    // Restore and return
    ldp x29, x30, [sp], #16
    ret

// ==========================================================================
// Example 5: Working with Arrays
// ==========================================================================
_array_sum:
    // Input: x0 = array pointer, x1 = array length
    // Output: x0 = sum of array elements
    
    mov x2, #0               // sum = 0
    mov x3, #0               // i = 0
    
.Larray_loop:
    cmp x3, x1               // Compare i with length
    bge .Larray_done         // If i >= length, done
    
    ldr w4, [x0, x3, lsl #2] // Load array[i] (i * 4 bytes)
    add w2, w2, w4           // sum += array[i]
    add x3, x3, #1           // i++
    b .Larray_loop
    
.Larray_done:
    mov x0, x2               // Return sum
    ret

// ==========================================================================
// Example 6: Hello World with System Calls
// ==========================================================================
.section __TEXT,__cstring
hello_msg: .asciz "Hello from ARM64 Assembly!\n"

.section __TEXT,__text
_print_hello:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    
    // Call printf
    adrp x0, hello_msg@PAGE
    add x0, x0, hello_msg@PAGEOFF
    bl _printf
    
    ldp x29, x30, [sp], #16
    ret

// ==========================================================================
// Main Function
// ==========================================================================
_main:
    // Save frame
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    
    // Print hello
    bl _print_hello
    
    // Test sum function
    mov x0, #10
    bl _sum_to_n
    // x0 now contains sum 1+2+...+10 = 55
    
    // Return 0
    mov x0, #0
    
    // Restore frame
    ldp x29, x30, [sp], #16
    ret

// ==========================================================================
// ARM64 vs x86-64 Comparison
// ==========================================================================
// Operation          ARM64                    x86-64 (AT&T)
// ---------          -----                    -------------
// Move               mov x0, #42              movq $42, %rax
// Add                add x0, x1, x2           addq %rbx, %rax
// Load               ldr x0, [x1]             movq (%rdi), %rax
// Store              str x0, [x1]             movq %rax, (%rdi)
// Compare            cmp x0, x1               cmpq %rbx, %rax
// Branch             b label                  jmp label
// Conditional        beq label                je label
// Call               bl function              call function
// Return             ret                      ret

// ==========================================================================
// Key Differences from x86-64:
// ==========================================================================
// 1. More registers (31 vs 16)
// 2. Fixed instruction size (32 bits)
// 3. Load/store architecture (can't do memory-to-memory ops)
// 4. Cleaner, more regular instruction set
// 5. Condition flags set explicitly (not implicitly by most instructions)

// ==========================================================================
// To compile and run:
// as arm64_mac_tutorial.s -o arm64_mac_tutorial.o
// ld arm64_mac_tutorial.o -o arm64_mac_tutorial -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -arch arm64
// ./arm64_mac_tutorial
// ========================================================================== 