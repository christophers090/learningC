# ARM64 Instructions Guide - Understanding Your Assembly Code

This guide explains every ARM64 instruction in your `main_function_assembly.s` file.

## 📋 Quick Reference Table

| Instruction | What It Does         | Example                                                 |
| ----------- | -------------------- | ------------------------------------------------------- |
| `sub`       | Subtract             | `sub sp, sp, #32` → sp = sp - 32                        |
| `stp`       | Store Pair           | `stp x29, x30, [sp, #16]` → Store x29 and x30 to memory |
| `add`       | Add                  | `add x29, sp, #16` → x29 = sp + 16                      |
| `stur`      | Store Unscaled       | `stur wzr, [x29, #-4]` → Store zero to memory           |
| `mov`       | Move/Load            | `mov w8, #1337` → w8 = 1337                             |
| `str`       | Store                | `str w8, [sp, #8]` → Store w8 to memory                 |
| `b`         | Branch (jump)        | `b 0x100003f58` → Jump to address                       |
| `ldr`       | Load                 | `ldr w8, [sp, #8]` → Load from memory to w8             |
| `subs`      | Subtract & Set flags | `subs w9, w8, #1` → w9 = w8 - 1, set flags              |
| `cset`      | Conditional Set      | `cset w8, eq` → w8 = 1 if equal, 0 if not               |
| `tbnz`      | Test Bit & Branch    | `tbnz w8, #0, addr` → Jump if bit 0 is not zero         |
| `adrp`      | Address Page         | `adrp x0, page` → Load page address                     |
| `bl`        | Branch with Link     | `bl printf` → Call function                             |
| `ldp`       | Load Pair            | `ldp x29, x30, [sp, #16]` → Load two values             |
| `ret`       | Return               | `ret` → Return from function                            |

## 🔍 Detailed Instruction Breakdown

### Memory Management Instructions

#### `sub sp, sp, #32`

- **Purpose**: Allocate stack space
- **What it does**: Subtract 32 from stack pointer
- **Why**: Creates room for local variables
- **C equivalent**: Entering a function with local variables

#### `stp x29, x30, [sp, #16]`

- **Purpose**: Save frame pointer and return address
- **What it does**: Store x29 and x30 to stack at offset 16
- **Why**: Function prologue - save caller's state
- **x29**: Frame pointer (like %rbp in x86)
- **x30**: Link register (return address)

#### `add x29, sp, #16`

- **Purpose**: Set up new frame pointer
- **What it does**: x29 = current stack pointer + 16
- **Why**: Establishes stack frame for this function

### Data Movement Instructions

#### `mov w8, #1337`

- **Purpose**: Load immediate value
- **What it does**: Put the number 1337 into register w8
- **C equivalent**: `int x = 1337;`
- **Note**: `w8` is 32-bit version of `x8`

#### `str w8, [sp, #8]`

- **Purpose**: Store register to memory
- **What it does**: Store w8 to stack at offset 8
- **Why**: Save the variable `x` to stack memory
- **Memory location**: Stack pointer + 8 bytes

#### `ldr w8, [sp, #8]`

- **Purpose**: Load from memory to register
- **What it does**: Load value from stack offset 8 into w8
- **C equivalent**: Reading the variable `x`

### Arithmetic Instructions

#### `subs w9, w8, #1`

- **Purpose**: Subtract and set condition flags
- **What it does**: w9 = w8 - 1, and set flags based on result
- **C equivalent**: `x--` (the decrement part)
- **Flags**: Sets zero flag if result is 0

#### `subs w8, w8, #0`

- **Purpose**: Test if value is zero
- **What it does**: w8 = w8 - 0 (no change), but sets flags
- **Why**: Check if original value was zero
- **C equivalent**: Testing `x` in `while(x--)`

### Control Flow Instructions

#### `b 0x100003f58`

- **Purpose**: Unconditional branch (jump)
- **What it does**: Jump to address 0x100003f58
- **C equivalent**: `goto` or loop continuation

#### `tbnz w8, #0, 0x100003f84`

- **Purpose**: Test bit and branch if not zero
- **What it does**: If bit 0 of w8 is not zero, jump to address
- **Why**: Exit loop if condition is met
- **C equivalent**: `if (condition) break;`

#### `bl 0x100003f94`

- **Purpose**: Branch with link (function call)
- **What it does**: Call function at address, save return address in x30
- **C equivalent**: `printf("ayo\n");`

### Condition Handling

#### `cset w8, eq`

- **Purpose**: Conditional set based on flags
- **What it does**: w8 = 1 if equal flag is set, 0 otherwise
- **Why**: Convert condition flags to boolean value
- **Context**: Used after `subs` to test if value was zero

### Function Exit

#### `ldp x29, x30, [sp, #16]`

- **Purpose**: Restore saved registers
- **What it does**: Load x29 and x30 from stack
- **Why**: Function epilogue - restore caller's state

#### `add sp, sp, #32`

- **Purpose**: Deallocate stack space
- **What it does**: Add 32 to stack pointer
- **Why**: Clean up local variables

#### `ret`

- **Purpose**: Return from function
- **What it does**: Jump to address in x30 (link register)
- **C equivalent**: `return 0;`

## 🎯 Register Usage in Your Code

| Register | Purpose in Your Code                        |
| -------- | ------------------------------------------- |
| `w8`     | Holds the variable `x` and temporary values |
| `w9`     | Holds `x-1` (decremented value)             |
| `x0`     | First argument to printf (string address)   |
| `x29`    | Frame pointer (stack frame base)            |
| `x30`    | Return address (where to go after function) |
| `sp`     | Stack pointer (top of stack)                |
| `wzr`    | Zero register (always contains 0)           |

## 🔄 How the Loop Works

1. **Initialize**: `mov w8, #1337` → x = 1337
2. **Store**: `str w8, [sp, #8]` → Save x to memory
3. **Loop start**: `ldr w8, [sp, #8]` → Load x
4. **Decrement**: `subs w9, w8, #1` → Calculate x-1
5. **Save new value**: `str w9, [sp, #8]` → Store x-1
6. **Test original**: `subs w8, w8, #0` → Test if original x was 0
7. **Set flag**: `cset w8, eq` → w8 = 1 if x was 0
8. **Branch if zero**: `tbnz w8, #0, exit` → Exit if x was 0
9. **Call printf**: `bl printf` → Print "ayo"
10. **Loop back**: `b loop_start` → Repeat

This implements the C code `while(x--)` perfectly - it decrements x and continues while the original value was not zero!
