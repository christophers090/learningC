# Assembly Language Learning Guide

Welcome to assembly language! This folder contains organized examples and tutorials to help you learn assembly from scratch.

## 📁 Folder Structure

```
assembly/
├── README.md                    # This guide
├── tutorials/                   # Step-by-step learning materials
│   ├── x86-64/                 # Intel/AMD 64-bit tutorials
│   │   └── assembly_basics_tutorial.s
│   └── arm64/                  # Apple Silicon (M1/M2) tutorials
│       └── arm64_mac_tutorial.s
├── examples/                    # Practical examples
│   ├── basic/                  # Simple starter examples
│   │   └── simple_hello.s
│   └── c-to-asm/              # C code compiled to assembly
│       ├── c_to_assembly_examples.c
│       └── c_to_assembly_examples.s
├── exercises/                   # Hands-on learning exercises
│   ├── learn_with_objdump.c   # objdump tutorial exercise
│   ├── learn_with_objdump.o   # Compiled object file
│   └── learn_with_objdump     # Executable for analysis
└── reference/                   # Reference materials
    ├── file_types_demo.s       # Understanding .s vs .o files
    └── comparisons/            # Architecture comparisons
        ├── assembly_variants_comparison.s
        └── assembly_similarity_demo.s
```

## 🚀 Getting Started

### 1. **Start Here**: Choose Your Architecture

- **Apple Silicon Mac (M1/M2)**: `tutorials/arm64/arm64_mac_tutorial.s`
- **Intel/AMD PC**: `tutorials/x86-64/assembly_basics_tutorial.s`

### 2. **Try a Simple Example**

```bash
cd examples/basic/
# Follow compilation instructions in simple_hello.s
```

### 3. **See C→Assembly Translation**

```bash
cd examples/c-to-asm/
gcc -S -O0 c_to_assembly_examples.c
# Compare the .c file with the generated .s file
```

### 4. **Practice with objdump**

```bash
cd exercises/
objdump -d learn_with_objdump | grep -A 20 "<main>:"
```

## 📚 Learning Path

| Step | What to Do                | Files to Use                     |
| ---- | ------------------------- | -------------------------------- |
| 1    | **Learn basics**          | `tutorials/[your-arch]/`         |
| 2    | **Try simple example**    | `examples/basic/simple_hello.s`  |
| 3    | **See C translation**     | `examples/c-to-asm/`             |
| 4    | **Practice analysis**     | `exercises/learn_with_objdump.*` |
| 5    | **Compare architectures** | `reference/comparisons/`         |

## 🔧 Compilation Quick Reference

### ARM64 (Apple Silicon)

```bash
# Assemble and link
as file.s -o file.o
ld file.o -o file -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -arch arm64

# Or use GCC
gcc file.s -o file
```

### x86-64 (Intel/AMD)

```bash
# Assemble and link
as file.s -o file.o
ld file.o -o file

# Or use GCC
gcc file.s -o file
```

### Analysis Tools

```bash
# Disassemble
objdump -d program

# Debug
gdb program
(gdb) disassemble main
```

## 🎯 What Each Folder Contains

### `tutorials/`

Complete step-by-step tutorials that teach concepts from scratch. Start here if you're new to assembly.

### `examples/`

Practical, runnable examples that demonstrate specific concepts. Good for hands-on practice.

### `exercises/`

Interactive learning exercises where you analyze and reverse-engineer code. Great for developing skills.

### `reference/`

Comparison charts, architecture differences, and reference materials. Use when you need to look something up.

## 🔍 Key Concepts You'll Learn

- **Registers**: CPU's built-in super-fast variables
- **Memory Operations**: Loading and storing data
- **Control Flow**: Jumps, loops, and conditionals
- **Function Calls**: How functions work at the assembly level
- **Stack Management**: How local variables and function calls are managed
- **Addressing Modes**: Different ways to access memory

## 🌟 Pro Tips

1. **Start with your native architecture** (ARM64 for M1/M2 Macs)
2. **Use `objdump` frequently** to see how C compiles to assembly
3. **Don't memorize instructions** - focus on understanding concepts
4. **Practice with simple programs** before tackling complex ones
5. **Use debuggers** (`gdb`, `lldb`) to step through code

## 📖 Next Steps

Once comfortable with basics:

1. Learn inline assembly in C/C++
2. Study compiler optimizations
3. Explore SIMD instructions (SSE/AVX, NEON)
4. Try reverse engineering challenges
5. Learn other architectures

Happy learning! Assembly might seem intimidating at first, but it's incredibly rewarding once you understand how the computer really works.
