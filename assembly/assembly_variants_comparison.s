# ==========================================================================
# Assembly Language Variants Comparison
# ==========================================================================

# ==========================================================================
# SAME OPERATION IN DIFFERENT ARCHITECTURES
# ==========================================================================

# Task: Load value 42 into a register, add 10, store result in memory

# --- x86-64 (AT&T Syntax - Linux/macOS) ---
# 64-bit Intel/AMD processors
x86_64_att:
    movq $42, %rax          # Load 42 into rax register
    addq $10, %rax          # Add 10 to rax
    movq %rax, result(%rip) # Store to memory

# --- x86-64 (Intel Syntax - Windows/NASM) ---
# Same processor, different syntax!
# mov rax, 42             # Load 42 into rax (destination first!)
# add rax, 10             # Add 10 to rax
# mov [result], rax       # Store to memory

# --- ARM (32-bit) ---
# Used in phones, Raspberry Pi, etc.
# mov r0, #42             # Load 42 into r0 register
# add r0, r0, #10         # Add 10 to r0
# str r0, [r1]            # Store r0 to address in r1

# --- ARM64 (AArch64) ---
# Modern ARM (Apple M1/M2, newer phones)
# mov x0, #42             # Load 42 into x0 register
# add x0, x0, #10         # Add 10 to x0
# str x0, [x1]            # Store to address in x1

# --- RISC-V ---
# Open-source architecture
# li a0, 42               # Load immediate 42 into a0
# addi a0, a0, 10         # Add immediate 10 to a0
# sw a0, 0(a1)            # Store word to address in a1

# --- MIPS ---
# Classic RISC architecture
# li $t0, 42              # Load 42 into $t0
# addi $t0, $t0, 10       # Add 10 to $t0
# sw $t0, 0($t1)          # Store to address in $t1

# --- AVR (8-bit) ---
# Arduino microcontrollers
# ldi r16, 42             # Load 42 into r16
# subi r16, -10           # Add 10 (subtract -10)
# st X, r16               # Store to address in X register

# ==========================================================================
# WHY SO MANY VARIANTS?
# ==========================================================================

# 1. DIFFERENT DESIGN PHILOSOPHIES:
#    - CISC (Complex): x86 - Many complex instructions
#    - RISC (Reduced): ARM, RISC-V - Fewer, simpler instructions

# 2. DIFFERENT REGISTER COUNTS:
#    - x86-64: 16 general purpose registers
#    - ARM64: 31 general purpose registers
#    - AVR: 32 registers (but 8-bit)

# 3. DIFFERENT WORD SIZES:
#    - 8-bit: AVR (Arduino)
#    - 16-bit: Old x86
#    - 32-bit: ARM32, older x86
#    - 64-bit: x86-64, ARM64

# 4. DIFFERENT INSTRUCTION FORMATS:
#    - x86: Variable length (1-15 bytes)
#    - ARM/RISC-V: Fixed length (32-bit instructions)

# ==========================================================================
# SYNTAX DIFFERENCES (x86-64 AT&T vs Intel)
# ==========================================================================

# Operation         AT&T Syntax              Intel Syntax
# ---------         -----------              -------------
# Move              movq $10, %rax           mov rax, 10
# Add               addq %rbx, %rax          add rax, rbx
# Memory            movq (%rdi), %rax        mov rax, [rdi]
# Indexed           movq 8(%rdi,%rsi,4),%rax mov rax, [rdi+rsi*4+8]
# Jump              jmp *%rax                jmp rax
# Call              call *(%rax)             call [rax]

# ==========================================================================
# WHICH ONE SHOULD YOU LEARN?
# ==========================================================================

# It depends on your goals:
# - Embedded systems → ARM or AVR
# - PC software → x86-64
# - macOS/Linux → AT&T syntax
# - Windows → Intel syntax
# - Learning concepts → Any! The ideas transfer

# The CONCEPTS are the same across all variants:
# - Registers for fast storage
# - Memory for data
# - Instructions for operations
# - Control flow (jumps/branches)
# - Function calls
# - Stack management

.section .data
result: .quad 0 