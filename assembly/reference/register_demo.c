#include <stdio.h>

// Simple function to demonstrate register usage
int add_numbers(int a, int b) {
    int result = a + b;
    return result;
}

int main() {
    int x = 5;
    int y = 10;
    int sum = add_numbers(x, y);
    printf("Sum: %d\n", sum);
    return 0;
}

/*
When you compile this and look at the assembly:

1. main() calls add_numbers() with `bl _add_numbers`
   - CPU automatically puts return address in x30
   
2. add_numbers() starts with:
   - sub sp, sp, #XX     (allocate stack)
   - stp x29, x30, [sp, #XX]  (save old x29 and x30)
   - add x29, sp, #XX    (set new frame pointer)
   
3. add_numbers() ends with:
   - ldp x29, x30, [sp, #XX]  (restore old x29 and x30)
   - add sp, sp, #XX     (deallocate stack)
   - ret                 (jump to address in x30)

The x30 contains the address of the instruction AFTER the `bl _add_numbers` call in main()
*/ 