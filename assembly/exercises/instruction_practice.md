# ARM64 Instruction Practice Exercise

## 🎯 Goal

Trace through your assembly code step by step to understand exactly what happens.

## 📝 Your Assembly Code (Annotated)

```assembly
_main:
    sub sp, sp, #32          ; 1. Allocate 32 bytes on stack
    stp x29, x30, [sp, #16]  ; 2. Save frame pointer & return address
    add x29, sp, #16         ; 3. Set new frame pointer
    stur wzr, [x29, #-4]    ; 4. Store 0 (return value placeholder)
    mov w8, #1337            ; 5. Load 1337 into w8 (x = 1337)
    str w8, [sp, #8]         ; 6. Store x to stack

.LBB0_1:                     ; LOOP START
    ldr w8, [sp, #8]         ; 7. Load x from stack
    subs w9, w8, #1          ; 8. w9 = x - 1, set flags
    str w9, [sp, #8]         ; 9. Store x-1 back to stack (x--)
    subs w8, w8, #0          ; 10. Test if original x was 0
    cset w8, eq              ; 11. w8 = 1 if x was 0, else 0
    tbnz w8, #0, .LBB0_3     ; 12. If x was 0, exit loop

    adrp x0, l_.str@PAGE     ; 13. Load string address (page)
    add x0, x0, l_.str@PAGEOFF ; 14. Complete string address
    bl _printf               ; 15. Call printf("ayo\n")
    b .LBB0_1                ; 16. Jump back to loop start

.LBB0_3:                     ; LOOP EXIT
    ldur w0, [x29, #-4]      ; 17. Load return value (0)
    ldp x29, x30, [sp, #16]  ; 18. Restore frame pointer & return addr
    add sp, sp, #32          ; 19. Deallocate stack space
    ret                      ; 20. Return to caller
```

## 🔍 Step-by-Step Trace Exercise

Fill in the blanks as you trace through the first few iterations:

### Function Entry (Steps 1-6)

- Stack pointer before: `sp = 0x7ff7bfeff000` (example)
- Stack pointer after step 1: `sp = ___________`
- What's stored at `[sp, #16]`: `___________`
- What's stored at `[sp, #8]` after step 6: `___________`
- Value in w8 after step 5: `___________`

### First Loop Iteration (Steps 7-16)

- Value loaded into w8 (step 7): `___________`
- Value calculated in w9 (step 8): `___________`
- New value stored to stack (step 9): `___________`
- Result of `subs w8, w8, #0` (step 10): flags = `___________`
- Value in w8 after `cset` (step 11): `___________`
- Does `tbnz` branch? (step 12): `___________`
- What function is called? (step 15): `___________`

### Second Loop Iteration

- Value loaded into w8: `___________`
- Value calculated in w9: `___________`
- New value stored to stack: `___________`
- Does loop continue?: `___________`

### When x = 1 (Near End)

- Value loaded into w8: `___________`
- Value calculated in w9: `___________`
- New value stored to stack: `___________`
- Result of testing original x: `___________`
- Does loop continue?: `___________`

### When x = 0 (Final Iteration)

- Value loaded into w8: `___________`
- Value calculated in w9: `___________`
- New value stored to stack: `___________`
- Result of `subs w8, w8, #0`: flags = `___________`
- Value in w8 after `cset`: `___________`
- Does `tbnz` branch?: `___________`

## 🧠 Understanding Questions

1. **Why does the code use both `w8` and `w9`?**
   Answer: **************\_\_\_\_**************

2. **What's the difference between `subs w9, w8, #1` and `subs w8, w8, #0`?**
   Answer: **************\_\_\_\_**************

3. **Why store to memory and then immediately load back?**
   Answer: **************\_\_\_\_**************

4. **What would happen if we used `tbz` instead of `tbnz`?**
   Answer: **************\_\_\_\_**************

5. **How many times will "ayo" be printed?**
   Answer: **************\_\_\_\_**************

## ✅ Answer Key

<details>
<summary>Click to reveal answers</summary>

### Function Entry

- Stack pointer after step 1: `sp = 0x7ff7bfefefe0` (original - 32)
- What's stored at `[sp, #16]`: `x29 and x30 (frame pointer and return address)`
- What's stored at `[sp, #8]` after step 6: `1337`
- Value in w8 after step 5: `1337`

### First Loop Iteration

- Value loaded into w8: `1337`
- Value calculated in w9: `1336`
- New value stored to stack: `1336`
- Result of `subs w8, w8, #0`: `flags = not zero`
- Value in w8 after `cset`: `0` (not equal)
- Does `tbnz` branch?: `No` (bit 0 is 0)
- What function is called?: `printf`

### Understanding Questions

1. **w8 holds original value, w9 holds decremented value**
2. **First does x-1, second tests if original x was 0**
3. **Compiler optimization - could be optimized away**
4. **Loop would exit when x is NOT zero (opposite behavior)**
5. **1337 times**

</details>

## 🚀 Next Steps

Once you understand this, try:

1. Modify the C code to use a different starting value
2. Use `objdump` to see how the assembly changes
3. Try a `for` loop instead of `while` loop
4. Add more variables and see how stack usage changes
