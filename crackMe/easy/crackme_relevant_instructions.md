# Key x86-64 Assembly Instructions for keygen.bin Crackme

This file lists assembly instructions relevant to understanding the `keygen.bin` crackme (specifically the `main` and `check_key` functions from the IDA output). This program is a 64-bit Linux ELF.

## 📋 Quick Reference Table

| Instruction    | What It Does                               | Example                                    |
| -------------- | ------------------------------------------ | ------------------------------------------ |
| `push`         | Push value onto stack                      | `push rbp`                                 |
| `pop`          | Pop value from stack                       | `pop rbx`                                  |
| `sub rsp, val` | Allocate stack space                       | `sub rsp, 70h`                             |
| `add rsp, val` | Deallocate stack space                     | `add rsp, 28h`                             |
| `leave`        | Restore caller's stack frame               | `leave`                                    |
| `mov`          | Move data                                  | `mov eax, 0`                               |
| `lea`          | Load Effective Address                     | `lea rdi, s` (s is a label for a string)   |
| `movzx`        | Move with Zero-Extend                      | `movzx eax, byte ptr [rax]`                |
| `movsx`        | Move with Sign-Extend                      | `movsx eax, al`                            |
| `movsxd`       | Move with Sign-Extend (32 to 64-bit)       | `movsxd rdx, eax`                          |
| `add`          | Addition                                   | `add [rbp+var_14], eax`                    |
| `xor`          | Bitwise XOR                                | `xor eax, eax`                             |
| `test`         | Bitwise AND (sets flags, no result stored) | `test eax, eax`                            |
| `cmp`          | Compare (subtracts, sets flags, no result) | `cmp rax, 7`                               |
| `call`         | Call subroutine                            | `call check_key`                           |
| `retn`         | Return from subroutine                     | `retn`                                     |
| `jmp`          | Unconditional jump                         | `jmp short loc_877`                        |
| `jz` / `je`    | Jump if Zero / Equal                       | `jz short loc_91A`                         |
| `jbe` / `jna`  | Jump if Below or Equal (unsigned)          | `cmp rax, 7; jbe short loc_839`            |
| `jb` / `jc`    | Jump if Below (unsigned) / Carry           | `cmp rbx, rax; jb short loc_85D`           |
| `jg` / `jnle`  | Jump if Greater (signed)                   | `cmp [rbp+var_14], 3E7h; jg short loc_8B2` |

## 💻 x86-64 General-Purpose Registers (GPRs)

| Register (64-bit) | Smaller Parts (32/16/8-bit) | Primary Conventional Use & Notes                             |
| ----------------- | --------------------------- | ------------------------------------------------------------ |
| `RAX`             | `EAX`, `AX`, `AL`/`AH`      | Return value; arithmetic.                                    |
| `RBX`             | `EBX`, `BX`, `BL`/`BH`      | General purpose; base pointer (callee-saved).                |
| `RCX`             | `ECX`, `CX`, `CL`/`CH`      | Loop counter. Arg4 (SysV) / Arg1 (MS x64).                   |
| `RDX`             | `EDX`, `DX`, `DL`/`DH`      | Pairs with RAX (e.g., MUL/DIV). Arg3 (SysV) / Arg2 (MS x64). |
| `RSI`             | `ESI`, `SI`, `SIL`          | String source pointer. Arg2 (SysV) / Arg3 (MS x64).          |
| `RDI`             | `EDI`, `DI`, `DIL`          | String destination pointer. Arg1 (SysV) / Arg4 (MS x64).     |
| `RBP`             | `EBP`, `BP`, `BPL`          | Stack frame base pointer (callee-saved).                     |
| `RSP`             | `ESP`, `SP`, `SPL`          | Stack pointer.                                               |
| `R8`              | `R8D`, `R8W`, `R8B`         | General purpose. Arg5 (SysV).                                |
| `R9`              | `R9D`, `R9W`, `R9B`         | General purpose. Arg6 (SysV).                                |
| `R10`             | `R10D`, `R10W`, `R10B`      | General purpose (caller-saved SysV).                         |
| `R11`             | `R11D`, `R11W`, `R11B`      | General purpose (caller-saved SysV).                         |
| `R12`             | `R12D`, `R12W`, `R12B`      | General purpose (callee-saved SysV).                         |
| `R13`             | `R13D`, `R13W`, `R13B`      | General purpose (callee-saved SysV).                         |
| `R14`             | `R14D`, `R14W`, `R14B`      | General purpose (callee-saved SysV).                         |
| `R15`             | `R15D`, `R15W`, `R15B`      | General purpose (callee-saved SysV).                         |

### Special-Purpose Registers

- **RIP (Instruction Pointer):**

  - 64-bit: `RIP`
  - _Purpose_: Holds the memory address of the **next instruction to be executed**. It cannot be accessed directly like GPRs (e.g., you can't do `mov rax, rip`), but it's updated by control flow instructions (`JMP`, `CALL`, `RET`).

- **RFLAGS (Flags Register):**
  - 64-bit: `RFLAGS` (32-bit version is `EFLAGS`)
  - _Purpose_: Contains various status flags, control flags, and system flags that reflect the state of the processor and the outcome of recent operations. Key flags include:
    - **ZF (Zero Flag):** Set if the result of an operation is zero.
    - **SF (Sign Flag):** Set if the result of an operation is negative (MSB is 1).
    - **CF (Carry Flag):** Set if an arithmetic operation resulted in a carry out of or borrow into the most significant bit (unsigned overflow).
    - **OF (Overflow Flag):** Set if a signed arithmetic operation resulted in an overflow (result too large/small to fit).
    - **PF (Parity Flag):** Set if the number of set bits in the LSB of the result is even.
    - **DF (Direction Flag):** Controls the direction of string operations (increment or decrement RSI/RDI).

(Note: This list isn't exhaustive but covers the most frequently encountered registers when reverse engineering user-mode applications.)

## 🔍 Detailed Instruction Breakdown

## Stack Operations

- `push <reg/value>`: Decrements the stack pointer (`rsp`) and stores the value of the register or immediate value onto the top of the stack.
  - Example: `push rbp` (saves the old base pointer)
- `pop <reg>`: Loads a value from the top of the stack into the specified register and then increments the stack pointer (`rsp`).
  - Example: `pop rbx`
- `sub rsp, <immediate_value>`: Subtracts an immediate value from the stack pointer. Used to allocate space on the stack for local variables.
  - Example: `sub rsp, 70h` (allocates 112 bytes)
- `add rsp, <immediate_value>`: Adds an immediate value to the stack pointer. Used to deallocate space previously allocated for local variables.
  - Example: `add rsp, 28h`
- `leave`: Restores the caller's stack frame. Functionally equivalent to `mov rsp, rbp; pop rbp`.

## Data Movement

- `mov <destination>, <source>`: Moves data from the source operand to the destination operand.
  - Examples:
    - `mov rbp, rsp` (register to register)
    - `mov eax, 0` (immediate to register)
    - `mov [rbp+var_8], rax` (register to memory location on stack, `var_8` is an offset from `rbp`)
    - `mov rax, [rbp+s]` (memory location on stack to register, `s` is an offset from `rbp`)
    - `mov rax, fs:28h` (move data from a memory location specified by the `fs` segment register plus an offset, used here for stack canary)
- `lea <destination_reg>, <source_memory_operand>`: Load Effective Address. Calculates the address of the source memory operand and stores this address in the destination register. It does _not_ load the value from the memory location, just the address itself.
  - Example: `lea rdi, s` (loads the memory address of the string labeled `s` into `rdi`)
  - Example: `lea rax, [rbp+var_70]` (loads the address `rbp - 70h` into `rax`)
- `movzx <destination_reg>, <source_reg/memory>`: Move with Zero-Extend. Moves a smaller source operand (e.g., a byte) to a larger destination register and fills the upper bits of the destination with zeros.
  - Example: `movzx eax, byte ptr [rax]` (moves the byte pointed to by `rax` into `eax`, zero-extending it to 32 bits)
- `movsx <destination_reg>, <source_reg/memory>`: Move with Sign-Extend. Moves a smaller source operand to a larger destination register and fills the upper bits of the destination by replicating the sign bit of the source.
  - Example: `movsx eax, al` (sign-extends the 8-bit value in `al` to a 32-bit value in `eax`)
- `movsxd <destination_reg64>, <source_reg32/memory32>`: Move with Sign-Extend Doubleword to Quadword. Sign-extends a 32-bit value to a 64-bit value.
  - Example: `movsxd rdx, eax` (sign-extends the 32-bit value in `eax` to a 64-bit value in `rdx`)

## Arithmetic and Logical Operations

- `add <destination>, <source>`: Adds the source operand to the destination operand and stores the result in the destination.
  - Example: `add rax, rdx`
  - Example: `add [rbp+var_14], eax` (adds `eax` to the dword value at `[rbp+var_14]`)
- `sub <destination>, <source>`: Subtracts the source operand from the destination operand and stores the result in the destination. (Not explicitly in key logic paths of `check_key` but used in stack setup).
- `xor <destination>, <source>`: Performs a bitwise XOR between the source and destination and stores the result in the destination.
  - Example: `xor eax, eax` (common way to set `eax` to 0)
  - Example: `xor rdx, fs:28h` (used in stack canary check)
- `test <operand1>, <operand2>`: Performs a bitwise AND on the two operands but does not store the result. It only sets the CPU flags (like ZF - Zero Flag) based on the result.
  - Example: `test eax, eax` (sets ZF if `eax` is 0, clears ZF otherwise)
- `cmp <operand1>, <operand2>`: Compares two operands. It effectively subtracts operand2 from operand1 but does not store the result. It sets CPU flags based on the outcome.
  - Example: `cmp rax, 7` (compares the value in `rax` with the immediate value 7)
  - Example: `cmp [rbp+var_14], 3E7h` (compares the dword value at `[rbp+var_14]` with 0x3E7)

## Control Flow

- `call <address/label>`: Calls a subroutine. Pushes the address of the instruction following the `call` (the return address) onto the stack and then jumps to the specified address/label.
  - Example: `call _puts`
  - Example: `call check_key`
- `retn` / `ret`: Returns from a subroutine. Pops the return address from the stack and jumps to it.
- `jmp <address/label>`: Unconditional jump to the specified address/label.
  - Example: `jmp short loc_877`
- `jz <address/label>` (or `je`): Jump if Zero (or Jump if Equal). Jumps if the Zero Flag (ZF) is set (ZF=1). Often used after `test` or `cmp`.
  - Example: `jz short loc_91A` (if `test eax, eax` resulted in zero)
- `jbe <address/label>` (or `jna`): Jump if Below or Equal (for unsigned comparison) / Jump if Not Above. Jumps if CF=1 or ZF=1.
  - Example: `cmp rax, 7; jbe short loc_839` (jumps if `rax <= 7`)
- `jb <address/label>` (or `jnae`, `jc`): Jump if Below (for unsigned comparison) / Jump if Not Above or Equal / Jump if Carry. Jumps if the Carry Flag (CF) is set (CF=1).
  - Example: `cmp rbx, rax; jb short loc_85D` (jumps if `rbx < rax` in an unsigned sense)
- `jg <address/label>` (or `jnle`): Jump if Greater (for signed comparison) / Jump if Not Less or Equal. Jumps if ZF=0 AND SF=OF (Sign Flag equals Overflow Flag).
  - Example: `cmp [rbp+var_14], 3E7h; jg short loc_8B2` (jumps if the signed dword at `[rbp+var_14]` is greater than 0x3E7)

## Memory Operand Size Specifiers

- `byte ptr [<address>]`: Indicates that the memory operation at `<address>` should affect 1 byte.
- `word ptr [<address>]`: Indicates that the memory operation at `<address>` should affect 2 bytes (16 bits).
- `dword ptr [<address>]`: Indicates that the memory operation at `<address>` should affect 4 bytes (32 bits).
- `qword ptr [<address>]`: Indicates that the memory operation at `<address>` should affect 8 bytes (64 bits).

## Functions Called (from libc usually)

- `_puts`: Prints a null-terminated string to standard output, followed by a newline.
- `___isoc99_scanf`: Reads formatted input from standard input. `"%s"` reads a sequence of non-whitespace characters.
- `_strlen`: Calculates the length of a null-terminated string (excluding the null terminator).
- `_printf`: Prints formatted output to standard output.
- `_exit`: Terminates the program immediately with a given exit status.
- `___stack_chk_fail`: Called when a stack canary mismatch is detected, indicating a likely buffer overflow. Terminates the program.
