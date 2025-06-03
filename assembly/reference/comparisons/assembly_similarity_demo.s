# ==========================================================================
# Assembly Variants Similarity Demo
# Same function implemented in different architectures
# ==========================================================================

# Task: Function that adds two numbers and returns result
# C equivalent: int add(int a, int b) { return a + b; }

# ==========================================================================
# x86-64 (Intel/AMD - AT&T Syntax)
# ==========================================================================
add_x86_att:
    # Arguments: %edi = a, %esi = b
    # Return: %eax
    movl %edi, %eax      # Move first arg to return register
    addl %esi, %eax      # Add second arg
    ret                  # Return

# ==========================================================================
# x86-64 (Intel Syntax - same CPU, different notation!)
# ==========================================================================
# add_x86_intel:
#     ; Arguments: edi = a, esi = b
#     ; Return: eax
#     mov eax, edi       ; Move first arg to return register
#     add eax, esi       ; Add second arg
#     ret                ; Return

# ==========================================================================
# ARM64 (Apple M1/M2, modern phones)
# ==========================================================================
# add_arm64:
#     // Arguments: x0 = a, x1 = b
#     // Return: x0
#     add x0, x0, x1     // Add x1 to x0, store in x0
#     ret                // Return

# ==========================================================================
# ARM32 (Older phones, Raspberry Pi)
# ==========================================================================
# add_arm32:
#     @ Arguments: r0 = a, r1 = b
#     @ Return: r0
#     add r0, r0, r1     @ Add r1 to r0
#     bx lr              @ Return (branch to link register)

# ==========================================================================
# RISC-V
# ==========================================================================
# add_riscv:
#     # Arguments: a0 = a, a1 = b
#     # Return: a0
#     add a0, a0, a1     # Add a1 to a0
#     ret                # Return (actually jalr x0, ra, 0)

# ==========================================================================
# MIPS
# ==========================================================================
# add_mips:
#     # Arguments: $a0 = a, $a1 = b
#     # Return: $v0
#     add $v0, $a0, $a1  # Add arguments, put in return register
#     jr $ra             # Jump to return address

# ==========================================================================
# MORE COMPLEX EXAMPLE: Loop that sums array
# C: int sum_array(int* arr, int len)
# ==========================================================================

# --- x86-64 (AT&T) ---
sum_array_x86:
    # %rdi = array pointer, %esi = length
    xorl %eax, %eax          # sum = 0
    xorl %ecx, %ecx          # i = 0
.L1:
    cmpl %esi, %ecx          # compare i with length
    jge .L2                  # if i >= length, exit
    movl (%rdi,%rcx,4), %edx # load arr[i]
    addl %edx, %eax          # sum += arr[i]
    incl %ecx                # i++
    jmp .L1                  # continue loop
.L2:
    ret                      # return sum in %eax

# --- ARM64 ---
# sum_array_arm64:
#     // x0 = array pointer, x1 = length
#     mov x2, #0           // sum = 0
#     mov x3, #0           // i = 0
# .loop:
#     cmp x3, x1           // compare i with length
#     bge .done            // if i >= length, exit
#     ldr w4, [x0, x3, lsl #2]  // load arr[i]
#     add w2, w2, w4       // sum += arr[i]
#     add x3, x3, #1       // i++
#     b .loop              // continue loop
# .done:
#     mov x0, x2           // return sum
#     ret

# ==========================================================================
# ANALYSIS: How Similar Are They?
# ==========================================================================

# VERY SIMILAR:
# 1. All use registers for arguments and return values
# 2. All have add, load, store, compare, branch instructions
# 3. All use similar loop patterns (initialize, compare, branch)
# 4. All use a stack that grows downward
# 5. All have conditional branches based on comparison

# MAIN DIFFERENCES:
# 1. Register names (rax vs x0 vs r0 vs a0)
# 2. Instruction names (jmp vs b vs jr)
# 3. Syntax style (AT&T vs Intel, % vs no prefix)
# 4. Number of registers (x86: 16, ARM64: 31, RISC-V: 32)
# 5. Addressing modes complexity

# ==========================================================================
# Learning Transfer Rate
# ==========================================================================

# If you know ONE assembly well, learning another is:
# - 70% already done (concepts)
# - 20% learning new syntax/names
# - 10% architecture-specific quirks

# Time to learn:
# First assembly language: 2-4 weeks to be comfortable
# Second assembly language: 2-4 DAYS to be productive
# Third+ assembly language: Few hours to start writing code

# ==========================================================================
# Practical Tips for Learning Multiple Assemblies
# ==========================================================================

# 1. Focus on CONCEPTS first, syntax second
# 2. Make comparison charts:
#    | Concept      | x86-64  | ARM64   | RISC-V  |
#    | Move         | mov     | mov     | mv/li   |
#    | Add          | add     | add     | add     |
#    | Jump         | jmp     | b       | j       |
#    | Compare      | cmp     | cmp     | blt/bge |
#    | Return       | ret     | ret     | ret     |

# 3. Key differences to watch for:
#    - Operand order (AT&T vs Intel)
#    - How conditions work (flags vs direct comparison)
#    - Available addressing modes
#    - Calling conventions

# 4. Same debugging skills work everywhere:
#    - Step through code
#    - Examine registers
#    - Check memory
#    - Understand stack

# ==========================================================================
# Which Skills Transfer Best?
# ==========================================================================

# UNIVERSAL SKILLS (100% transfer):
# - Understanding memory layout
# - Stack operations
# - Function call mechanisms
# - Debugging techniques
# - Optimization principles
# - Security concepts (buffer overflows, etc.)

# PARTIAL TRANSFER (80% transfer):
# - Instruction patterns
# - Register usage strategies
# - Loop optimizations
# - Conditional logic

# ARCHITECTURE SPECIFIC (20% transfer):
# - Exact syntax
# - Special instructions (SIMD, etc.)
# - Specific calling conventions
# - Interrupt handling 