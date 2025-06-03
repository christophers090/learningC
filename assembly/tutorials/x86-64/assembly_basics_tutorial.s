# ==========================================================================
# Assembly Language Tutorial - From Zero to Basic Understanding
# ==========================================================================
# Target: x86-64 (Intel/AMD 64-bit) - macOS/Linux compatible
# Assembler: GNU Assembler (gas) - uses AT&T syntax
# 
# This file teaches assembly from scratch with practical examples.
# Each section builds on the previous one.
# ==========================================================================

.section .data
    # This section contains initialized data (like global variables in C)
    
    # String literals (null-terminated)
    hello_msg:      .asciz "Hello from Assembly!\n"
    number_msg:     .asciz "The number is: %d\n"
    char_msg:       .asciz "Character: %c\n"
    
    # Numbers of different sizes
    my_byte:        .byte 42           # 8-bit value (1 byte)
    my_word:        .word 1234         # 16-bit value (2 bytes)  
    my_long:        .long 123456       # 32-bit value (4 bytes)
    my_quad:        .quad 123456789    # 64-bit value (8 bytes)
    
    # Arrays
    numbers:        .long 10, 20, 30, 40, 50    # Array of 5 32-bit integers
    
.section .bss
    # This section contains uninitialized data (like uninitialized globals in C)
    # Memory is allocated but not given initial values
    
    buffer:         .space 100        # Reserve 100 bytes of uninitialized space
    result:         .space 8          # Reserve 8 bytes for a 64-bit result

.section .text
    # This section contains the actual code (instructions)
    
    .global _start    # Entry point for the program (like main() in C)

# ==========================================================================
# LESSON 1: Basic Program Structure and System Calls
# ==========================================================================

_start:
    # This is where program execution begins
    # Think of this as main() in C
    
    # Let's start with a simple "Hello World"
    # On macOS/Linux, we use system calls to interact with the OS
    
    # System call to write to stdout
    # write(file_descriptor, buffer, count)
    # file_descriptor: 1 = stdout, 2 = stderr
    
    movq $1, %rax           # System call number for write (1)
    movq $1, %rdi           # File descriptor (1 = stdout)
    movq $hello_msg, %rsi   # Address of string to print
    movq $21, %rdx          # Number of bytes to write
    syscall                 # Invoke the system call
    
    # Jump to the next lesson
    jmp lesson2_registers

# ==========================================================================
# LESSON 2: Understanding Registers
# ==========================================================================
# Registers are like super-fast variables built into the CPU
# x86-64 has many registers, here are the most important ones:

lesson2_registers:
    # General Purpose Registers (64-bit):
    # %rax, %rbx, %rcx, %rdx, %rsi, %rdi, %rsp, %rbp
    # %r8, %r9, %r10, %r11, %r12, %r13, %r14, %r15
    
    # Register naming conventions:
    # %rax = 64-bit register
    # %eax = lower 32 bits of %rax  
    # %ax  = lower 16 bits of %rax
    # %al  = lower 8 bits of %rax
    # %ah  = bits 8-15 of %rax
    
    # Let's demonstrate moving data between registers
    movq $100, %rax         # Move immediate value 100 into %rax
    movq %rax, %rbx         # Copy value from %rax to %rbx
    movq $200, %rcx         # Move 200 into %rcx
    
    # Now %rax = 100, %rbx = 100, %rcx = 200
    
    jmp lesson3_arithmetic

# ==========================================================================
# LESSON 3: Basic Arithmetic Operations
# ==========================================================================

lesson3_arithmetic:
    # Addition
    movq $10, %rax          # %rax = 10
    movq $5, %rbx           # %rbx = 5
    addq %rbx, %rax         # %rax = %rax + %rbx = 15
    
    # Subtraction  
    movq $20, %rcx          # %rcx = 20
    subq $7, %rcx           # %rcx = %rcx - 7 = 13
    
    # Multiplication (result goes in %rax, input in %rax and operand)
    movq $6, %rax           # %rax = 6
    movq $4, %rbx           # %rbx = 4
    imulq %rbx, %rax        # %rax = %rax * %rbx = 24
    
    # Increment and Decrement
    incq %rax               # %rax = %rax + 1 = 25
    decq %rax               # %rax = %rax - 1 = 24
    
    jmp lesson4_memory

# ==========================================================================
# LESSON 4: Memory Operations (Loading and Storing)
# ==========================================================================

lesson4_memory:
    # Loading from memory to register
    movq my_quad, %rax      # Load the 64-bit value from my_quad into %rax
    movl my_long, %ebx      # Load the 32-bit value from my_long into %ebx
    movw my_word, %cx       # Load the 16-bit value from my_word into %cx
    movb my_byte, %dl       # Load the 8-bit value from my_byte into %dl
    
    # Storing from register to memory
    movq $999, %rax         # Put 999 in %rax
    movq %rax, result       # Store %rax value into the 'result' memory location
    
    # Working with arrays (indexed addressing)
    # numbers is an array: [10, 20, 30, 40, 50]
    # Each element is 4 bytes (32-bit long)
    
    movl numbers, %eax      # Load first element (index 0): numbers[0] = 10
    movl numbers+4, %ebx    # Load second element (index 1): numbers[1] = 20  
    movl numbers+8, %ecx    # Load third element (index 2): numbers[2] = 30
    
    # More flexible array access using index register
    movq $2, %rsi           # Index = 2
    movl numbers(,%rsi,4), %edx  # Load numbers[2] = 30
    # Formula: base + (index * scale) where scale = size of element
    
    jmp lesson5_control_flow

# ==========================================================================
# LESSON 5: Control Flow (Jumps, Comparisons, Loops)
# ==========================================================================

lesson5_control_flow:
    # Unconditional jump (like goto in C)
    # jmp label
    
    # Conditional jumps (like if statements)
    # First, we need to compare values
    movq $10, %rax
    movq $20, %rbx
    cmpq %rbx, %rax         # Compare %rax with %rbx (sets flags)
    
    # Jump based on comparison results:
    # je  = jump if equal
    # jne = jump if not equal  
    # jl  = jump if less
    # jle = jump if less or equal
    # jg  = jump if greater
    # jge = jump if greater or equal
    
    jl rax_is_smaller       # Jump if %rax < %rbx (10 < 20, so this will jump)
    
    # This won't execute because we jumped above
    movq $999, %rcx
    jmp after_comparison
    
rax_is_smaller:
    movq $111, %rcx         # This will execute
    
after_comparison:
    # Simple loop example (count from 1 to 5)
    movq $1, %rcx           # Counter = 1
    
loop_start:
    cmpq $5, %rcx           # Compare counter with 5
    jg loop_end             # If counter > 5, exit loop
    
    # Loop body (just increment counter)
    incq %rcx               # counter++
    jmp loop_start          # Go back to loop condition
    
loop_end:
    # %rcx now contains 6
    
    jmp lesson6_functions

# ==========================================================================
# LESSON 6: Functions and the Stack
# ==========================================================================

lesson6_functions:
    # The stack is used for:
    # 1. Function calls and returns
    # 2. Local variables
    # 3. Saving/restoring registers
    
    # %rsp = stack pointer (points to top of stack)
    # %rbp = base pointer (frame pointer)
    
    # Calling a function
    movq $42, %rdi          # First argument goes in %rdi
    movq $13, %rsi          # Second argument goes in %rsi
    call add_function       # Call the function (pushes return address)
    # Result comes back in %rax
    
    jmp lesson7_printf

# Simple function that adds two numbers
add_function:
    # Function prologue (set up stack frame)
    pushq %rbp              # Save old base pointer
    movq %rsp, %rbp         # Set new base pointer
    
    # Function body
    addq %rsi, %rdi         # Add second arg to first arg
    movq %rdi, %rax         # Put result in %rax (return value)
    
    # Function epilogue (clean up stack frame)
    popq %rbp               # Restore old base pointer
    ret                     # Return to caller (pops return address)

# ==========================================================================
# LESSON 7: Calling C Library Functions (printf)
# ==========================================================================

lesson7_printf:
    # We can call C library functions from assembly!
    # This makes output much easier than raw system calls
    
    # Print a number using printf
    movq $number_msg, %rdi  # First argument: format string
    movq $42, %rsi          # Second argument: the number to print
    movq $0, %rax           # %rax = number of vector registers used (0 for us)
    call printf             # Call C printf function
    
    # Print a character
    movq $char_msg, %rdi    # Format string
    movq $65, %rsi          # ASCII value for 'A'
    movq $0, %rax
    call printf
    
    jmp lesson8_bitwise

# ==========================================================================
# LESSON 8: Bitwise Operations
# ==========================================================================

lesson8_bitwise:
    movq $0b11110000, %rax  # Binary: 11110000 (240 in decimal)
    movq $0b10101010, %rbx  # Binary: 10101010 (170 in decimal)
    
    # Bitwise AND
    movq %rax, %rcx
    andq %rbx, %rcx         # %rcx = %rax & %rbx = 10100000 (160)
    
    # Bitwise OR
    movq %rax, %rdx
    orq %rbx, %rdx          # %rdx = %rax | %rbx = 11111010 (250)
    
    # Bitwise XOR
    movq %rax, %r8
    xorq %rbx, %r8          # %r8 = %rax ^ %rbx = 01011010 (90)
    
    # Bitwise NOT
    movq %rax, %r9
    notq %r9                # %r9 = ~%rax = 00001111 (15) for low byte
    
    # Bit shifts
    movq $8, %r10           # 8 = 00001000
    shlq $2, %r10           # Shift left by 2: 00100000 = 32
    shrq $1, %r10           # Shift right by 1: 00010000 = 16
    
    jmp lesson9_addressing

# ==========================================================================
# LESSON 9: Advanced Addressing Modes
# ==========================================================================

lesson9_addressing:
    # x86-64 has very flexible addressing modes
    # General form: displacement(base, index, scale)
    # Effective address = base + (index * scale) + displacement
    
    # Examples with our numbers array: [10, 20, 30, 40, 50]
    
    # Direct addressing
    movl numbers, %eax      # numbers[0] = 10
    
    # Base + displacement
    movl numbers+4, %eax    # numbers[1] = 20
    
    # Base + index * scale
    movq $2, %rbx           # index = 2
    movl numbers(,%rbx,4), %eax  # numbers[2] = 30 (scale=4 for 32-bit ints)
    
    # Base + index * scale + displacement
    movq $1, %rbx           # index = 1  
    movl numbers+8(,%rbx,4), %eax  # numbers[1+2] = numbers[3] = 40
    
    # Using base register too
    movq $numbers, %rcx     # base = address of numbers
    movq $1, %rbx           # index = 1
    movl (%rcx,%rbx,4), %eax     # numbers[1] = 20
    
    jmp program_exit

# ==========================================================================
# LESSON 10: Program Exit
# ==========================================================================

program_exit:
    # Exit the program cleanly
    movq $60, %rax          # System call number for exit (60)
    movq $0, %rdi           # Exit status (0 = success)
    syscall                 # Call the kernel

# ==========================================================================
# COMPARISON WITH C CODE
# ==========================================================================
# Here's how some assembly concepts relate to C:

# C Code:                   Assembly Equivalent:
# --------                  --------------------
# int x = 10;              movq $10, %rax
# x = y;                   movq %rbx, %rax  
# x = x + 5;               addq $5, %rax
# if (x > 10) {...}        cmpq $10, %rax; jg label
# while (x < 100) {...}    loop: cmpq $100, %rax; jge end; ...; jmp loop; end:
# x = array[i];            movl array(,%rsi,4), %eax
# function(a, b);          movq a, %rdi; movq b, %rsi; call function

# ==========================================================================
# KEY CONCEPTS SUMMARY
# ==========================================================================

# 1. REGISTERS: Fast storage built into CPU
#    - %rax, %rbx, %rcx, %rdx: General purpose
#    - %rsi, %rdi: Often used for function arguments
#    - %rsp: Stack pointer, %rbp: Base pointer

# 2. MEMORY SECTIONS:
#    - .data: Initialized global variables
#    - .bss: Uninitialized global variables  
#    - .text: Program code (instructions)

# 3. INSTRUCTION FORMAT:
#    - opcode + suffix + source, destination
#    - Suffixes: b(byte), w(word), l(long), q(quad)
#    - Example: movq $10, %rax (move quad-word 10 to rax)

# 4. ADDRESSING MODES:
#    - Immediate: $10 (literal value)
#    - Register: %rax (register contents)
#    - Direct: variable (memory location)
#    - Indirect: (%rax) (memory at address in rax)
#    - Indexed: array(,%rsi,4) (array + rsi*4)

# 5. CONTROL FLOW:
#    - jmp: Unconditional jump
#    - cmp + conditional jump: if statements
#    - call/ret: Function calls
#    - Loops: combination of cmp + conditional jumps

# 6. FUNCTION CALLING CONVENTION (System V ABI):
#    - Arguments: %rdi, %rsi, %rdx, %rcx, %r8, %r9, then stack
#    - Return value: %rax
#    - Caller-saved: %rax, %rcx, %rdx, %rsi, %rdi, %r8-r11
#    - Callee-saved: %rbx, %rbp, %r12-r15

# ==========================================================================
# HOW TO ASSEMBLE AND RUN THIS FILE
# ==========================================================================

# On macOS/Linux:
# 1. Save this file as assembly_tutorial.s
# 2. Assemble: as -64 assembly_tutorial.s -o assembly_tutorial.o
# 3. Link: ld assembly_tutorial.o -o assembly_tutorial -lSystem (macOS)
#    or: gcc assembly_tutorial.o -o assembly_tutorial (Linux)
# 4. Run: ./assembly_tutorial

# Note: Some examples use printf which requires linking with C library
# For a simpler version that only uses system calls, remove printf calls

# ==========================================================================
# NEXT STEPS FOR LEARNING
# ==========================================================================

# 1. Practice writing simple functions in assembly
# 2. Learn about floating-point operations (SSE/AVX instructions)
# 3. Study how C code compiles to assembly (use: gcc -S file.c)
# 4. Learn about optimization and performance considerations
# 5. Explore inline assembly in C/C++ programs
# 6. Study specific CPU architectures (ARM, RISC-V, etc.) 