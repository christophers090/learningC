# Assembly Language Learning Guide

Welcome to assembly language! This folder contains examples to help you learn assembly from scratch.

## Files in this folder:

1. **`assembly_basics_tutorial.s`** - Comprehensive tutorial covering all fundamental assembly concepts
2. **`simple_hello.s`** - Minimal "Hello World" program you can actually compile and run
3. **`c_to_assembly_examples.c`** - C code that you can compile to assembly to see the relationship
4. **`README.md`** - This guide

## Getting Started

### What is Assembly Language?

Assembly language is a low-level programming language that's one step above machine code. Each assembly instruction corresponds directly to a machine instruction that the CPU can execute. It's like having direct control over the processor.

**Why learn assembly?**

- Understand how computers really work at the hardware level
- Debug and optimize performance-critical code
- Embedded systems programming often requires assembly knowledge
- Reverse engineering and security analysis
- It makes you a better programmer by understanding what's "under the hood"

### Key Concepts (from your C/C++ background):

| C/C++ Concept     | Assembly Equivalent                     |
| ----------------- | --------------------------------------- |
| Variables         | Registers and memory locations          |
| `int x = 10;`     | `movq $10, %rax`                        |
| `if (x > 5)`      | `cmpq $5, %rax; jg label`               |
| `while (x < 100)` | Loop with `cmp` and conditional jumps   |
| Function calls    | `call` instruction + calling convention |
| Arrays            | Memory with calculated offsets          |
| Pointers          | Memory addresses in registers           |

## How to Run the Examples

### Option 1: Simple Hello World (Recommended first step)

```bash
# Navigate to the assembly folder
cd assembly

# Assemble the simple hello program
as simple_hello.s -o simple_hello.o

# Link it (macOS)
ld simple_hello.o -o simple_hello -macosx_version_min 10.7 -lSystem -no_pie

# Or link it (Linux)
ld simple_hello.o -o simple_hello

# Run it
./simple_hello
```

### Option 2: See How C Compiles to Assembly

```bash
# Compile the C file to assembly (don't optimize so it's readable)
gcc -S -O0 c_to_assembly_examples.c

# Look at the generated assembly
cat c_to_assembly_examples.s

# Compare the C code with the assembly output
# This is incredibly educational!
```

### Option 3: Study the Tutorial

Open `assembly_basics_tutorial.s` in your text editor and read through it. It's heavily commented and explains each concept step by step.

## Understanding the Syntax

Assembly uses **AT&T syntax** (common on macOS/Linux):

```assembly
movq $10, %rax          # Move immediate value 10 into register rax
movq %rax, %rbx         # Move value from rax to rbx
addq %rbx, %rax         # Add rbx to rax, store result in rax
```

**Key syntax rules:**

- `$` prefix = immediate value (literal number)
- `%` prefix = register name
- Source comes first, destination comes second
- Instruction suffixes: `b` (byte), `w` (word), `l` (long), `q` (quad)

## Important Registers (x86-64)

| Register | Purpose                        | C Function Call Usage  |
| -------- | ------------------------------ | ---------------------- |
| `%rax`   | General purpose, return values | Function return value  |
| `%rdi`   | General purpose                | 1st function argument  |
| `%rsi`   | General purpose                | 2nd function argument  |
| `%rdx`   | General purpose                | 3rd function argument  |
| `%rcx`   | General purpose                | 4th function argument  |
| `%rbx`   | General purpose                | Callee-saved           |
| `%rsp`   | Stack pointer                  | Points to top of stack |
| `%rbp`   | Base pointer                   | Frame pointer          |

## Learning Path

1. **Start with `simple_hello.s`** - Get something running
2. **Read `assembly_basics_tutorial.s`** - Learn the concepts
3. **Experiment with `c_to_assembly_examples.c`** - See C→Assembly translation
4. **Write your own simple assembly functions**
5. **Learn about inline assembly in C/C++**

## Common Beginner Mistakes

1. **Forgetting instruction suffixes** - Use `movq` for 64-bit, `movl` for 32-bit, etc.
2. **Wrong operand order** - Remember: source first, destination second
3. **Not understanding calling conventions** - Function arguments go in specific registers
4. **Stack management errors** - Always balance `push` with `pop`
5. **Forgetting to exit properly** - Always include an exit system call

## Next Steps

Once you're comfortable with these basics:

1. Learn about floating-point instructions (SSE/AVX)
2. Study compiler optimizations (`gcc -O2 -S`)
3. Learn inline assembly for C/C++ programs
4. Explore other architectures (ARM, RISC-V)
5. Study reverse engineering tools (objdump, gdb)

## Debugging Assembly

```bash
# Compile with debug info
gcc -g -O0 your_program.c

# Debug with gdb
gdb ./your_program
(gdb) layout asm          # Show assembly view
(gdb) stepi               # Step one instruction
(gdb) info registers      # Show register values
(gdb) x/10i $pc          # Show next 10 instructions
```

## Resources for Further Learning

- Intel Software Developer Manual (the ultimate reference)
- "Programming from the Ground Up" by Jonathan Bartlett
- Online x86-64 instruction reference
- Compiler Explorer (godbolt.org) - see how C compiles to assembly online

Happy learning! Assembly might seem intimidating at first, but it's incredibly rewarding once you start to understand how the computer really works.
