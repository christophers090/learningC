// ==========================================================================
// C to Assembly Examples
// ==========================================================================
// Compile this with: gcc -S -O0 c_to_assembly_examples.c
// This will generate c_to_assembly_examples.s showing the assembly output
// Use -O0 to disable optimizations so the assembly is more readable
// ==========================================================================

#include <stdio.h>

// ==========================================================================
// Example 1: Simple variable assignment
// ==========================================================================
void simple_assignment() {
    int x = 10;        // movl $10, -4(%rbp)
    int y = 20;        // movl $20, -8(%rbp)
    int z = x + y;     // Load x, load y, add them, store in z
}

// ==========================================================================
// Example 2: If statement
// ==========================================================================
void simple_if(int value) {
    if (value > 10) {          // cmpl $10, %edi; jle .L2
        printf("Big number\n"); // call printf
    } else {                   // jmp .L3; .L2:
        printf("Small number\n"); // call printf
    }                          // .L3:
}

// ==========================================================================
// Example 3: Loop
// ==========================================================================
int simple_loop() {
    int sum = 0;               // movl $0, -8(%rbp)
    for (int i = 0; i < 5; i++) {  // Loop setup and condition
        sum += i;              // addl %eax, -8(%rbp)
    }
    return sum;                // movl -8(%rbp), %eax
}

// ==========================================================================
// Example 4: Function call
// ==========================================================================
int add_numbers(int a, int b) {
    return a + b;              // addl %esi, %edi; movl %edi, %eax
}

void call_function() {
    int result = add_numbers(5, 3);  // movl $3, %esi; movl $5, %edi; call add_numbers
}

// ==========================================================================
// Example 5: Array access
// ==========================================================================
void array_example() {
    int arr[5] = {1, 2, 3, 4, 5};    // Initialize array on stack
    int x = arr[2];                   // movl -36(%rbp), %eax (offset calculation)
    arr[1] = 10;                      // movl $10, -44(%rbp)
}

// ==========================================================================
// Example 6: Pointer operations
// ==========================================================================
void pointer_example() {
    int x = 42;                // movl $42, -12(%rbp)
    int *ptr = &x;             // leaq -12(%rbp), %rax; movq %rax, -8(%rbp)
    int y = *ptr;              // movq -8(%rbp), %rax; movl (%rax), %eax
    *ptr = 100;                // movq -8(%rbp), %rax; movl $100, (%rax)
}

// ==========================================================================
// Example 7: Bitwise operations
// ==========================================================================
void bitwise_example() {
    int a = 0xFF;              // movl $255, -16(%rbp)
    int b = 0x0F;              // movl $15, -12(%rbp)
    
    int and_result = a & b;    // andl instruction
    int or_result = a | b;     // orl instruction
    int xor_result = a ^ b;    // xorl instruction
    int shift_left = a << 2;   // sall $2, %eax
    int shift_right = a >> 1;  // sarl $1, %eax
}

// ==========================================================================
// Main function to tie it all together
// ==========================================================================
int main() {
    printf("C to Assembly Examples\n");
    
    simple_assignment();
    simple_if(15);
    simple_if(5);
    
    int loop_result = simple_loop();
    printf("Loop result: %d\n", loop_result);
    
    call_function();
    array_example();
    pointer_example();
    bitwise_example();
    
    return 0;
}

// ==========================================================================
// How to see the assembly:
// ==========================================================================
// 1. Compile to assembly: gcc -S -O0 c_to_assembly_examples.c
// 2. Look at the generated .s file: cat c_to_assembly_examples.s
// 3. Compare the C code above with the assembly output
//
// Key things to look for in the assembly:
// - Function prologues: pushq %rbp; movq %rsp, %rbp
// - Local variables: stored at negative offsets from %rbp
// - Function calls: arguments in %rdi, %rsi, %rdx, etc.
// - Return values: in %rax
// - Conditional jumps: cmp followed by jl, jg, je, etc.
// - Loops: labels and jump instructions
// ========================================================================== 