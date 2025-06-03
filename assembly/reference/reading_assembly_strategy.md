# Reading Assembly Strategy - Skip the Boilerplate, Find the Logic

## 🎯 The 3-Step Reading Strategy

### Step 1: Identify the Template

Look for this pattern and **mentally skip it**:

```assembly
function_name:
    sub sp, sp, #XX          ← SKIP (boilerplate)
    stp x29, x30, [sp, #XX]  ← SKIP (boilerplate)
    add x29, sp, #XX         ← SKIP (boilerplate)

    ; === FOCUS HERE ===
    ; This is where your C code logic lives

    ldp x29, x30, [sp, #XX]  ← SKIP (boilerplate)
    add sp, sp, #XX          ← SKIP (boilerplate)
    ret                      ← SKIP (boilerplate)
```

### Step 2: Find the Algorithm

The interesting code is always in the middle. Look for:

- **Loops**: Labels like `.LBB0_1:` with branches back to them
- **Conditionals**: `cmp`, `tbnz`, `tbz`, `b.eq`, `b.ne` instructions
- **Function calls**: `bl` instructions
- **Data manipulation**: `mov`, `add`, `sub`, `mul` with actual values

### Step 3: Map to Your C Code

Once you find the logic, connect it back to your original C code.

## 📋 Pattern Recognition Cheat Sheet

### ✅ What to Focus On

| Pattern                  | Meaning               | C Equivalent               |
| ------------------------ | --------------------- | -------------------------- |
| `mov w8, #1337`          | Load constant         | `int x = 1337;`            |
| `ldr w8, [sp, #8]`       | Read variable         | Using variable `x`         |
| `str w8, [sp, #8]`       | Store variable        | `x = something;`           |
| `subs w9, w8, #1`        | Arithmetic with flags | `x--` or `x-1`             |
| `bl _printf`             | Function call         | `printf(...)`              |
| `.LBB0_1:` + `b .LBB0_1` | Loop                  | `while`, `for`, `do-while` |
| `tbnz w8, #0, .LBB0_3`   | Conditional branch    | `if (condition)`           |

### ❌ What to Ignore (Boilerplate)

| Pattern                | Purpose                 | Skip Because           |
| ---------------------- | ----------------------- | ---------------------- |
| `sub sp, sp, #XX`      | Stack allocation        | Same in every function |
| `stp x29, x30, [...]`  | Save registers          | Same in every function |
| `add x29, sp, #XX`     | Frame pointer setup     | Same in every function |
| `ldp x29, x30, [...]`  | Restore registers       | Same in every function |
| `add sp, sp, #XX`      | Stack cleanup           | Same in every function |
| `ret`                  | Return                  | Same in every function |
| `stur wzr, [x29, #-4]` | Initialize return value | Compiler optimization  |

## 🔍 Your Example Analyzed

```assembly
_main:
    sub sp, sp, #32          ← BOILERPLATE: Skip
    stp x29, x30, [sp, #16]  ← BOILERPLATE: Skip
    add x29, sp, #16         ← BOILERPLATE: Skip
    stur wzr, [x29, #-4]    ← BOILERPLATE: Skip (return value setup)

    mov w8, #1337            ← LOGIC: int x = 1337;
    str w8, [sp, #8]         ← LOGIC: Store x

.LBB0_1:                     ← LOGIC: while loop start
    ldr w8, [sp, #8]         ← LOGIC: Load x
    subs w9, w8, #1          ← LOGIC: Calculate x-1
    str w9, [sp, #8]         ← LOGIC: Store x-1 (x--)
    subs w8, w8, #0          ← LOGIC: Test if original x was 0
    cset w8, eq              ← LOGIC: Convert to boolean
    tbnz w8, #0, .LBB0_3     ← LOGIC: Exit if x was 0

    adrp x0, l_.str@PAGE     ← LOGIC: Load "ayo\n" address
    add x0, x0, l_.str@PAGEOFF ← LOGIC: Complete address
    bl _printf               ← LOGIC: printf("ayo\n");
    b .LBB0_1                ← LOGIC: Loop back

.LBB0_3:                     ← LOGIC: Loop exit point
    ldur w0, [x29, #-4]      ← BOILERPLATE: Load return value
    ldp x29, x30, [sp, #16]  ← BOILERPLATE: Skip
    add sp, sp, #32          ← BOILERPLATE: Skip
    ret                      ← BOILERPLATE: Skip
```

**The actual algorithm is only 10 lines!** The rest is just function housekeeping.

## 🎓 Practice Exercise

Look at this assembly and identify what the C code probably was:

```assembly
_calculate:
    sub sp, sp, #16          ; ?
    stp x29, x30, [sp]       ; ?
    add x29, sp, #0          ; ?

    mov w8, #5               ; ?
    mov w9, #10              ; ?
    add w10, w8, w9          ; ?
    str w10, [sp, #8]        ; ?
    ldr w0, [sp, #8]         ; ?

    ldp x29, x30, [sp]       ; ?
    add sp, sp, #16          ; ?
    ret                      ; ?
```

<details>
<summary>Answer</summary>

**Boilerplate** (lines 2-4, 10-12): Standard function setup/cleanup
**Logic** (lines 5-9):

```c
int calculate() {
    int a = 5;
    int b = 10;
    int result = a + b;
    return result;
}
```

</details>

## 🚀 Key Insight

**90% of assembly code is the same boilerplate pattern.** Once you recognize it, you can focus on the 10% that actually implements your algorithm. This makes assembly much less intimidating!
