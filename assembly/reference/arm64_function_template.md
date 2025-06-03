# ARM64 Function Template - The Universal Patterns

Every ARM64 function follows the same basic structure, regardless of what it actually does. Understanding this template will help you read ANY ARM64 assembly code.

## 🏗️ The Standard Function Structure

```assembly
function_name:
    ; === PROLOGUE (Function Entry) ===
    sub sp, sp, #N           ; 1. Allocate stack space
    stp x29, x30, [sp, #M]   ; 2. Save frame pointer & return address
    add x29, sp, #M          ; 3. Set up new frame pointer

    ; === YOUR CODE GOES HERE ===
    ; (This is where the actual function logic happens)

    ; === EPILOGUE (Function Exit) ===
    ldp x29, x30, [sp, #M]   ; 4. Restore frame pointer & return address
    add sp, sp, #N           ; 5. Deallocate stack space
    ret                      ; 6. Return to caller
```

## 📋 Universal Components Explained

### 1. Stack Allocation: `sub sp, sp, #N`

- **Always happens first**
- **Purpose**: Reserve space for local variables
- **N**: Usually multiple of 16 (ARM64 requires 16-byte stack alignment)
- **Common values**: 16, 32, 48, 64, etc.

### 2. Save Registers: `stp x29, x30, [sp, #offset]`

- **Always happens second**
- **x29**: Frame pointer (points to current function's stack frame)
- **x30**: Link register (return address - where to go when function ends)
- **Why**: These registers might be overwritten, so save them first

### 3. Frame Pointer Setup: `add x29, sp, #offset`

- **Always happens third**
- **Purpose**: Establish a stable reference point in the stack
- **Why**: Even if `sp` changes during function, `x29` stays constant

### 4. Function Body

- **Your actual code goes here**
- **Can be anything**: loops, calculations, function calls, etc.
- **May use additional stack space for local variables**

### 5. Restore Registers: `ldp x29, x30, [sp, #offset]`

- **Always happens before return**
- **Purpose**: Get back the original frame pointer and return address
- **Must match the earlier `stp` instruction**

### 6. Stack Cleanup: `add sp, sp, #N`

- **Always happens before return**
- **Purpose**: Give back the stack space we borrowed
- **Must match the earlier `sub` instruction**

### 7. Return: `ret`

- **Always the last instruction**
- **Purpose**: Jump back to whoever called this function
- **Uses address stored in x30**

## 🎯 Why This Pattern Exists

### Stack Management

- **Problem**: Functions need temporary storage
- **Solution**: Borrow space from the stack, give it back when done
- **Rule**: Always clean up after yourself

### Register Preservation

- **Problem**: Functions might overwrite important registers
- **Solution**: Save them at start, restore at end
- **Rule**: Leave registers the way you found them

### Return Address Tracking

- **Problem**: How does function know where to return?
- **Solution**: Caller puts return address in x30, function preserves it
- **Rule**: Don't lose the return address!

## 📊 Stack Layout Example

```
Before function call:
┌─────────────────┐ ← sp (stack pointer)
│                 │
│   Caller's      │
│   Stack Frame   │
│                 │
└─────────────────┘

After prologue:
┌─────────────────┐ ← original sp
│                 │
│   Caller's      │
│   Stack Frame   │
│                 │
├─────────────────┤ ← x29 (frame pointer)
│ Saved x29, x30  │ ← [sp, #16]
├─────────────────┤
│                 │
│ Local Variables │ ← [sp, #8], [sp, #0]
│                 │
└─────────────────┘ ← sp (new stack pointer)
```

## 🔍 Pattern Variations

### Simple Functions (16-32 bytes)

```assembly
sub sp, sp, #16          ; Small allocation
stp x29, x30, [sp]       ; Save at offset 0
add x29, sp, #0          ; Frame pointer at sp
; ... function body ...
ldp x29, x30, [sp]       ; Restore from offset 0
add sp, sp, #16          ; Deallocate
ret
```

### Complex Functions (48+ bytes)

```assembly
sub sp, sp, #48          ; Larger allocation
stp x29, x30, [sp, #32]  ; Save at higher offset
add x29, sp, #32         ; Frame pointer higher up
; ... function body ...
ldp x29, x30, [sp, #32]  ; Restore from same offset
add sp, sp, #48          ; Deallocate same amount
ret
```

### Functions with Many Variables

```assembly
sub sp, sp, #64          ; Even more space
stp x29, x30, [sp, #48]  ; Save registers
stp x19, x20, [sp, #32]  ; Save additional registers
add x29, sp, #48         ; Set frame pointer
; ... function body ...
ldp x19, x20, [sp, #32]  ; Restore additional registers
ldp x29, x30, [sp, #48]  ; Restore frame registers
add sp, sp, #64          ; Clean up
ret
```

## 🎓 Key Takeaways

1. **Every function follows this pattern** - once you know it, you can read any ARM64 function
2. **The numbers change, the pattern doesn't** - stack size varies, but structure is identical
3. **Prologue and epilogue are mirrors** - what you save, you restore; what you allocate, you deallocate
4. **Your actual code goes in the middle** - the interesting stuff happens between prologue and epilogue
5. **Stack must stay aligned** - ARM64 requires 16-byte alignment, so stack sizes are multiples of 16

## 🚀 Practice Recognition

Now when you see assembly code, you can immediately identify:

- **Lines 1-3**: Standard prologue (setup)
- **Middle section**: The actual algorithm
- **Last 3 lines**: Standard epilogue (cleanup)

This makes reading assembly much easier - you can skip the boilerplate and focus on the logic!
