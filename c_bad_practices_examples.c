#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h> // For bool in C99/C11 if desired, or use int 0/1

// ==========================================================================
// C Bad Practices & Good Alternatives
// ==========================================================================
// This file demonstrates common pitfalls in C programming and suggests
// better, safer ways to achieve the same goals.
// ==========================================================================

// --------------------------------------------------------------------------
// Section 1: Memory Management Errors
// --------------------------------------------------------------------------

// --- 1.1 Bad: Returning a pointer to a local (stack) variable ---
char *bad_get_string_v1()
{
    char local_buffer[50]; // Lives on the stack
    strcpy(local_buffer, "Hello from stack!");
    return local_buffer; // DANGER: local_buffer is deallocated when function returns.
                         // The returned pointer will be a "dangling pointer" pointing to invalid memory.
}

// Good Alternative 1.1.1: Caller provides the buffer
void good_get_string_v1(char *out_buffer, size_t buffer_size, const char *message)
{
    if (!out_buffer || buffer_size == 0)
        return;
    strncpy(out_buffer, message, buffer_size - 1);
    out_buffer[buffer_size - 1] = '\0'; // Ensure null-termination
}

// Good Alternative 1.1.2: Dynamic allocation (caller must free)
char *good_get_string_v2(const char *message)
{
    if (!message)
        return NULL;
    char *heap_buffer = malloc(strlen(message) + 1); // +1 for null terminator
    if (heap_buffer == NULL)
    {
        perror("Failed to allocate memory for string");
        return NULL; // Allocation failed
    }
    strcpy(heap_buffer, message);
    return heap_buffer; // Caller is responsible for calling free() on this pointer
}

// Good Alternative 1.1.3: Using a static local buffer (with limitations)
const char *good_get_string_v3(const char *message_part)
{
    static char static_buffer[100]; // Persists across calls, but shared
    // Be careful with static buffers:
    // 1. Not thread-safe if modified by multiple threads.
    // 2. Subsequent calls will overwrite the buffer.
    // Best for read-only or very controlled usage.
    snprintf(static_buffer, sizeof(static_buffer), "Static: %s", message_part);
    return static_buffer;
}

// --- 1.2 Bad: Forgetting to free dynamically allocated memory (Memory Leak) ---
void bad_memory_leak()
{
    int *numbers = malloc(10 * sizeof(int));
    if (numbers == NULL)
        return;
    for (int i = 0; i < 10; i++)
        numbers[i] = i;
    // `numbers` pointer goes out of scope, but the allocated memory is not freed.
}

// Good: Always free allocated memory
void good_memory_management()
{
    int *numbers = malloc(10 * sizeof(int));
    if (numbers == NULL)
    {
        perror("Failed to allocate numbers");
        return;
    }
    for (int i = 0; i < 10; i++)
        numbers[i] = i * 2;
    // ... use numbers ...
    free(numbers);  // Free the memory when done
    numbers = NULL; // Good practice: nullify pointer after free to prevent accidental use
}

// --- 1.3 Bad: Using memory after it has been freed (Use-After-Free) ---
void bad_use_after_free()
{
    char *str = malloc(20);
    if (!str)
        return;
    strcpy(str, "Test");
    printf("Before free: %s\n", str);
    free(str);
    // str = NULL; // If this line is missing, the next line is a use-after-free
    // printf("After free: %s\n", str); // DANGER: Accessing freed memory (Undefined Behavior)
    // If str was set to NULL, this would likely crash safely (dereferencing NULL).
    // If str was not set to NULL, it might print garbage or crash unpredictably.
}

// Good: Set pointer to NULL after free to prevent accidental reuse
void good_use_after_free_practice()
{
    char *str = malloc(20);
    if (!str)
        return;
    strcpy(str, "Test");
    printf("String: %s\n", str);
    free(str);
    str = NULL; // Set to NULL immediately after freeing

    if (str != NULL)
    { // This check now correctly prevents use
      // printf("This won't print: %s\n", str);
    }
    else
    {
        printf("Pointer is NULL, cannot use.\n");
    }
}

// --- 1.4 Bad: Not checking the return value of malloc/calloc/realloc ---
void bad_null_check_malloc()
{
    // Assuming malloc might fail due to low memory
    int *data = malloc(1000000 * sizeof(int)); // Large allocation
    // if (data == NULL) { /* Handle error */ } // Missing check!
    // data[0] = 123; // CRASH if malloc failed and returned NULL
    if (data)
    { // This check is too late if malloc failed, data[0] would have been accessed
        data[0] = 123;
        printf("Large allocation, data[0] = %d\n", data[0]);
        free(data);
    }
    else
    {
        printf("Large allocation failed (bad_null_check_malloc example shows a flawed check placement).\n");
    }
}

// Good: Always check malloc/calloc/realloc return value
void good_null_check_malloc()
{
    int *data = malloc(1000000 * sizeof(int));
    if (data == NULL)
    {
        perror("Failed to allocate data in good_null_check_malloc");
        // Handle error appropriately (e.g., return error code, exit, try smaller allocation)
        return;
    }
    data[0] = 123;
    printf("Large allocation successful, data[0] = %d\n", data[0]);
    free(data);
}

// --- 1.5 Bad: Buffer Overflow with string functions ---
void bad_buffer_overflow_strcpy()
{
    char small_buffer[10];
    const char *long_string = "This is a very long string that will overflow the buffer";
    // strcpy(small_buffer, long_string); // DANGER: strcpy does not check bounds.
    // It will write past the end of small_buffer,
    // corrupting adjacent memory on the stack.
    printf("Attempted strcpy (likely corrupted stack or crashed)\n");
}

// Good: Use bounded string functions like strncpy, snprintf
void good_bounded_strcpy()
{
    char small_buffer[10];
    const char *long_string = "This is a very long string that will overflow the buffer";

    strncpy(small_buffer, long_string, sizeof(small_buffer) - 1);
    small_buffer[sizeof(small_buffer) - 1] = '\0'; // IMPORTANT: strncpy might not null-terminate
                                                   // if src is longer than or equal to num.
    printf("strncpy result: %s\n", small_buffer);

    // Even better for formatted strings: snprintf
    char another_buffer[10];
    int result = snprintf(another_buffer, sizeof(another_buffer), "Num: %d", 123456789);
    // snprintf always null-terminates if size > 0.
    // It returns the number of chars that *would have been written* if buffer was large enough.
    if (result >= (int)sizeof(another_buffer))
    {
        printf("snprintf: String was truncated. Full length would be %d\n", result);
    }
    printf("snprintf result: %s\n", another_buffer);
}

// --- 1.6 Bad: Using gets() ---
void bad_gets_usage()
{
    char name[20];
    printf("Enter your name: ");
    // gets(name); // EXTREMELY DANGEROUS: gets() has no way to limit input size,
    // leading to easy buffer overflows. It's deprecated and removed from recent C standards.
    printf("NEVER USE gets(). Use fgets instead.\n");
}

// Good: Use fgets for safe string input
void good_fgets_usage()
{
    char name[20];
    printf("Enter your name (fgets): ");
    if (fgets(name, sizeof(name), stdin) != NULL)
    {
        // fgets might include the newline character if there's space. Remove it.
        name[strcspn(name, "\n")] = '\0'; // Find first newline and replace with null
        printf("Hello, %s!\n", name);
    }
    else
    {
        printf("Error reading input or EOF reached.\n");
    }
}

// --------------------------------------------------------------------------
// Section 2: Pointers and Arrays
// --------------------------------------------------------------------------

// --- 2.1 Bad: Confusion between array and pointer in function parameters ---
// void bad_array_sizeof_param(int arr[10]) { // 'int arr[10]' is treated as 'int *arr'
//     printf("Sizeof arr in bad_array_sizeof_param: %zu (this is sizeof(int*), not array)\n", sizeof(arr));
// }
// This example is tricky because `sizeof(arr)` inside the function WILL give `sizeof(int*)`.
// The "bad" part is the *expectation* that it would behave like `sizeof` on an array definition.
// The real bad practice is relying on `sizeof(parameter)` for array size when parameter is a pointer.

// Good: Pass array size explicitly or use a sentinel value
void good_process_array(int *arr, size_t size)
{
    printf("Processing array of size %zu:\n", size);
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// --- 2.2 Bad: Off-by-one errors in loops ---
void bad_off_by_one()
{
    int numbers[5] = {1, 2, 3, 4, 5};
    // Forgetting that array indices are 0 to size-1
    // for (int i = 0; i <= 5; i++) { // i <= 5 goes from 0 to 5 (6 iterations)
    //     printf("%d ", numbers[i]); // numbers[5] is out of bounds
    // }
    printf("Bad off-by-one loop would access out of bounds.\n");
}

// Good: Correct loop bounds
void good_loop_bounds()
{
    int numbers[5] = {1, 2, 3, 4, 5};
    printf("Corrected loop: ");
    for (int i = 0; i < 5; i++)
    { // i < 5 goes from 0 to 4
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

// --- 2.3 Bad: Uninitialized Pointers ---
void bad_uninitialized_pointer()
{
    int *ptr; // ptr is uninitialized, points to a garbage memory location
    // *ptr = 10; // DANGER: Writing to an unknown memory location (Undefined Behavior -> CRASH likely)
    printf("Accessing uninitialized pointer would be UB.\n");
}

// Good: Initialize pointers
void good_initialized_pointer()
{
    int *ptr = NULL; // Initialize to NULL
    int x = 10;

    if (ptr == NULL)
    {
        printf("Pointer is NULL, not safe to dereference yet.\n");
    }

    ptr = &x;  // Now ptr points to a valid memory location
    *ptr = 20; // Safe
    printf("Value pointed to by ptr: %d\n", *ptr);

    // For dynamic allocation:
    int *dyn_ptr = malloc(sizeof(int));
    if (dyn_ptr != NULL)
    {
        *dyn_ptr = 30;
        printf("Value in dyn_ptr: %d\n", *dyn_ptr);
        free(dyn_ptr);
        dyn_ptr = NULL;
    }
    else
    {
        perror("Failed to allocate for dyn_ptr");
    }
}

// --------------------------------------------------------------------------
// Section 3: Function Issues
// --------------------------------------------------------------------------

// --- 3.1 Bad: Ignoring function return values that indicate errors ---
void bad_ignore_return_value()
{
    FILE *fp = fopen("non_existent_file.txt", "r");
    // if (fp == NULL) { /* handle error */ } // Missing check
    // char buffer[100];
    // fgets(buffer, sizeof(buffer), fp); // If fp is NULL, this is UB.
    if (fp)
    { // This check is too late if fopen failed
        printf("File opened (bad_ignore_return_value example shows a flawed check placement).\n");
        fclose(fp);
    }
    else
    {
        printf("fopen failed, but error might not have been handled before use.\n");
    }
}

// Good: Always check return values of functions that can fail
void good_check_return_value()
{
    FILE *fp = fopen("hopefully_exists.txt", "w"); // Try to create/write
    if (fp == NULL)
    {
        perror("Failed to open file in good_check_return_value");
        return; // Exit or handle error
    }
    fprintf(fp, "Hello from good_check_return_value!\n");
    printf("Successfully wrote to file.\n");
    fclose(fp);
}

// --------------------------------------------------------------------------
// Section 4: Type Safety and Conversions
// --------------------------------------------------------------------------

// --- 4.1 Bad: Implicit conversion losing data (e.g., float to int) ---
void bad_implicit_conversion_loss()
{
    float f = 3.14159f;
    int i = f; // Implicit conversion, fractional part is lost
    printf("Float %.5f implicitly converted to int: %d\n", f, i);
}

// Good: Be explicit or aware of conversions
void good_explicit_conversion()
{
    float f = 3.14159f;
    int i = (int)f; // Explicit cast (still loses fraction, but it's deliberate)
    printf("Float %.5f explicitly cast to int: %d\n", f, i);

    // If rounding is needed, use roundf (from math.h, link with -lm)
    // #include <math.h>
    // int rounded_i = (int)roundf(f);
    // printf("Float %.5f rounded to int: %d\n", f, rounded_i);
}

// --- 4.2 Bad: Integer Overflow/Underflow without checks ---
void bad_integer_overflow()
{
    int16_t max_val = 32767; // Max value for signed 16-bit int
    printf("Initial int16_t: %d\n", max_val);
    // max_val = max_val + 1; // Undefined Behavior for signed overflow!
    // For unsigned, it would wrap around.
    printf("Adding 1 to max_val (signed overflow is UB, might wrap or trap): %d (result unpredictable)\n", max_val + 1);

    uint8_t zero_val = 0;
    // zero_val = zero_val - 1; // Wraps around for unsigned types
    printf("Subtracting 1 from uint8_t 0 (wraps around): %u\n", (uint8_t)(zero_val - 1));
}

// Good: Check for potential overflow/underflow or use larger types
void good_integer_overflow_checks()
{
    int16_t val = 30000;
    int16_t increment = 3000;

    // Check before addition for signed overflow
    if ((increment > 0 && val > INT16_MAX - increment) ||
        (increment < 0 && val < INT16_MIN - increment))
    {
        printf("Potential signed overflow detected before adding %d to %d\n", increment, val);
    }
    else
    {
        val += increment;
        printf("Result after checked addition: %d\n", val);
    }

    uint8_t u_val = 250;
    uint8_t u_increment = 10;
    // Check before addition for unsigned overflow (wraparound)
    if (u_val > UINT8_MAX - u_increment)
    {
        printf("Potential unsigned wraparound detected before adding %u to %u\n", u_increment, u_val);
        u_val = (u_val + u_increment); // This will wrap
        printf("Wrapped result: %u\n", u_val);
    }
    else
    {
        u_val += u_increment;
        printf("Result after checked unsigned addition: %u\n", u_val);
    }
}

// --- 4.3 Bad: Comparing signed and unsigned integers ---
void bad_signed_unsigned_compare()
{
    int s_val = -1;
    unsigned int u_val = 1;

    // if (s_val < u_val) { // DANGER: s_val (-1) is promoted to unsigned int.
    // -1 converted to unsigned int becomes a very large positive number.
    // So, this comparison will likely be false.
    //     printf("(-1 < 1) is TRUE as expected (THIS IS WRONG in C due to promotion)\n");
    // } else {
    //     printf("(-1 < 1) is FALSE (due to signed-to-unsigned promotion in C)\n");
    // }
    printf("Comparison -1 < 1U: when -1 is promoted to unsigned, it becomes large, so -1 < 1U is often false.\n");
    // The actual result depends on the size of int and unsigned int.
    // If int is 32-bit, -1 (0xFFFFFFFF) as unsigned is UINT_MAX.
}

// Good: Cast operands to a common type carefully or avoid mixed comparisons
void good_signed_unsigned_compare()
{
    int s_val = -1;
    unsigned int u_val = 1;

    // Option 1: Cast unsigned to signed (if value fits)
    // if (u_val <= INT_MAX)
    // { // Check if u_val can be safely represented as int
    //     if (s_val < (int)u_val)
    //     {
    //         printf("Good compare (cast u_val to int): %d < %d is true\n", s_val, (int)u_val);
    //     }
    //     else
    //     {
    //         printf("Good compare (cast u_val to int): %d < %d is false\n", s_val, (int)u_val);
    //     }
    // }
    // else
    // {
    //     printf("u_val is too large to cast to int for comparison.\n");
    // }

    // Option 2: Cast signed to unsigned (be very careful with negative numbers)
    if (s_val < 0)
    { // If s_val is negative, it will always be "less than" a non-negative u_val
      // in mathematical sense, but not if s_val is promoted to unsigned.
        printf("Good compare (s_val is negative): true that %d < %u\n", s_val, u_val);
    }
    else
    {
        // Both non-negative, safe to promote s_val to unsigned for comparison
        if ((unsigned int)s_val < u_val)
        {
            printf("Good compare (both non-negative, cast s_val): %u < %u is true\n", (unsigned int)s_val, u_val);
        }
        else
        {
            printf("Good compare (both non-negative, cast s_val): %u < %u is false\n", (unsigned int)s_val, u_val);
        }
    }
    // Best: Try to use same-signedness types for comparisons when possible.
}

// --------------------------------------------------------------------------
// Section 5: Preprocessor Misuse
// --------------------------------------------------------------------------

// --- 5.1 Bad: Macros with side effects / multiple evaluations ---
int counter = 0;
int next_val()
{
    return ++counter;
}
// #define BAD_MAX(a, b) ((a) > (b) ? (a) : (b)) // Parentheses around args and whole expr are good
// BUT if args have side effects...
void bad_macro_side_effects()
{
    counter = 0;
    int x = 5;
    // int y = BAD_MAX(x, next_val()); // next_val() might be called twice if x <= next_val()
    // If x=5, next_val() returns 1. 5 > 1. y=5. counter=1. (next_val called once)
    // If x=0, next_val() returns 1. 0 > 1 is false. next_val() called again (returns 2). y=2. counter=2.
    // This unpredictability is bad.
    printf("Using macros with side-effect arguments is dangerous.\n");
}

// Good: Use inline functions (C99+) or static inline functions for type safety and predictable evaluation
static inline int good_max_inline(int a, int b)
{
    return a > b ? a : b;
}
void good_inline_function_use()
{
    counter = 0;
    int x = 0;
    int y = good_max_inline(x, next_val()); // next_val() is called exactly once
    printf("good_max_inline(%d, val_from_next_val) = %d, counter = %d\n", x, y, counter);
}

// --- 5.2 Bad: Missing parentheses in macro definitions ---
#define BAD_PRODUCT(x, y) x *y // Missing parentheses around x, y, and whole expression
void bad_macro_parentheses()
{
    int result = BAD_PRODUCT(2 + 3, 4 + 5); // Expands to: 2 + 3 * 4 + 5 = 2 + 12 + 5 = 19
                                            // Expected (2+3)*(4+5) = 5 * 9 = 45
    printf("BAD_PRODUCT(2+3, 4+5) = %d (Incorrect due to operator precedence)\n", result);

    // Another common issue:
    // #define BAD_IS_BIT_SET(val, bit) val & (1 << bit) == (1 << bit) // Wrong precedence for ==
    // if (BAD_IS_BIT_SET(0b101, 0)) // Expands to 0b101 & (1<<0) == (1<<0) -> 1 & 1 == 1 -> 1 == 1 -> true (Correct here)
    // if (BAD_IS_BIT_SET(0b101, 1)) // Expands to 0b101 & (1<<1) == (1<<1) -> 0b101 & 2 == 2 -> 0 & 2 == 2 -> 0 == 2 -> false (Correct)
    // if (BAD_IS_BIT_SET(0b101, 2)) // Expands to 0b101 & (1<<2) == (1<<2) -> 0b101 & 4 == 4 -> 4 == 4 -> true (Correct)
    // The above IS_BIT_SET actually works due to luck of `&` having higher precedence than `==`.
    // A more insidious example for missing outer parentheses:
    // #define BAD_ADD_ONE(x) x + 1
    // result = 5 * BAD_ADD_ONE(2); // Expands to 5 * 2 + 1 = 10 + 1 = 11. Expected 5 * (2+1) = 15.
}

// Good: Always use parentheses extensively in macros
#define GOOD_PRODUCT(x, y) ((x) * (y))
#define GOOD_IS_BIT_SET(val, bit) (((val) & (1 << (bit))) != 0) // Ensure bitwise AND happens first, then compare
#define GOOD_ADD_ONE(x) ((x) + 1)

void good_macro_parentheses()
{
    int result1 = GOOD_PRODUCT(2 + 3, 4 + 5);
    printf("GOOD_PRODUCT(2+3, 4+5) = %d (Correct)\n", result1);

    uint8_t flags = 0b00000101; // Bit 0 and 2 are set
    if (GOOD_IS_BIT_SET(flags, 0))
        printf("Bit 0 is set (Good)\n");
    if (!GOOD_IS_BIT_SET(flags, 1))
        printf("Bit 1 is NOT set (Good)\n");

    int result2 = 5 * GOOD_ADD_ONE(2);
    printf("5 * GOOD_ADD_ONE(2) = %d (Correct)\n", result2);
}

// --------------------------------------------------------------------------
// Section 6: Control Flow
// --------------------------------------------------------------------------

// --- 6.1 Bad: Assignment in if-condition (often a typo for ==) ---
void bad_assignment_in_if()
{
    int x = 0;
    // if (x = 5) { // This assigns 5 to x, and 5 is true-thy in C. Loop always runs.
    //     printf("x was accidentally assigned in if, and is now %d\n", x);
    // }
    printf("Accidental assignment in 'if' is a common bug.\n");
}

// Good: Use comparison, or be explicit if assignment is intended
void good_comparison_in_if()
{
    int x = 0;
    if (x == 5)
    {
        printf("x is 5\n");
    }
    else
    {
        printf("x (%d) is not 5\n", x);
    }

    // If assignment is truly intended (e.g., checking return of a function that assigns)
    // make it clear:
    int y;
    if ((y = (x > 0 ? 10 : -10)) != 0)
    { // Parentheses around assignment make intent clear
        printf("y was assigned %d and is non-zero.\n", y);
    }
}

// --------------------------------------------------------------------------
// Section 7: Magic Numbers & Readability
// --------------------------------------------------------------------------

// --- 7.1 Bad: Using unnamed "magic numbers" ---
void bad_magic_numbers(int status_code)
{
    if (status_code == 0)
    {
        printf("Status OK.\n");
    }
    else if (status_code == 1)
    {
        printf("Status Warning.\n");
    }
    else if (status_code == 255)
    { // What is 255?
        printf("Critical Error!\n");
    }
}

// Good: Use #define, enums, or const variables for named constants
#define STATUS_OK_DEFINE 0
#define STATUS_WARN_DEFINE 1
#define STATUS_ERROR_CRITICAL_DEFINE 255

typedef enum
{
    STATUS_OK_ENUM = 0,
    STATUS_WARN_ENUM = 1,
    STATUS_ERROR_RETRY_ENUM = 2,
    // ...
    STATUS_CRITICAL_ENUM = 255 // If specific values needed
} StatusCodeEnum;

const int STATUS_OK_CONST = 0;
const int STATUS_WARN_CONST = 1;

void good_named_constants(StatusCodeEnum status_code)
{
    if (status_code == STATUS_OK_ENUM)
    {
        printf("Status OK (enum).\n");
    }
    else if (status_code == STATUS_WARN_ENUM)
    {
        printf("Status Warning (enum).\n");
    }
    else if (status_code == STATUS_CRITICAL_ENUM)
    {
        printf("Critical Error (enum)!\n");
    }
}

// --- Main function to call examples ---
int main()
{
    printf("--- Demonstrating C Bad Practices and Good Alternatives ---\n\n");

    printf("--- Section 1: Memory Management ---\n");
    // 1.1 Returning pointer to local
    char *dangling_str = bad_get_string_v1();
    // Accessing dangling_str here is undefined behavior. It might seem to work, or crash.
    // printf("Dangling string (UB): %s\n", dangling_str); // Don't do this

    char caller_buf[100];
    good_get_string_v1(caller_buf, sizeof(caller_buf), "Hello from caller buffer!");
    printf("Good string (caller_buf): %s\n", caller_buf);

    char *heap_str = good_get_string_v2("Hello from heap!");
    if (heap_str)
    {
        printf("Good string (heap_str): %s\n", heap_str);
        free(heap_str);
    }

    printf("Good string (static_v3_call1): %s\n", good_get_string_v3("first part"));
    printf("Good string (static_v3_call2): %s\n", good_get_string_v3("second part overwrites"));

    // 1.2 Memory Leak
    // bad_memory_leak(); // Call this to leak, but not good for a demo program's cleanliness
    good_memory_management();

    // 1.3 Use-after-free
    bad_use_after_free();
    good_use_after_free_practice();

    // 1.4 Not checking malloc return
    // bad_null_check_malloc(); // Might crash
    good_null_check_malloc();

    // 1.5 Buffer overflow strcpy
    // bad_buffer_overflow_strcpy(); // Might crash or corrupt
    good_bounded_strcpy();

    // 1.6 Using gets
    // bad_gets_usage(); // Don't call, it's dangerous
    // good_fgets_usage(); // Interactive, uncomment to test

    printf("\n--- Section 2: Pointers and Arrays ---\n");
    int my_array[] = {10, 20, 30};
    // bad_array_sizeof_param(my_array); // Demonstrates sizeof(pointer)
    good_process_array(my_array, sizeof(my_array) / sizeof(my_array[0]));
    bad_off_by_one();
    good_loop_bounds();
    bad_uninitialized_pointer();
    good_initialized_pointer();

    printf("\n--- Section 3: Function Issues ---\n");
    bad_ignore_return_value();
    good_check_return_value();

    printf("\n--- Section 4: Type Safety ---\n");
    bad_implicit_conversion_loss();
    good_explicit_conversion();
    bad_integer_overflow();
    good_integer_overflow_checks();
    bad_signed_unsigned_compare();
    good_signed_unsigned_compare();

    printf("\n--- Section 5: Preprocessor ---\n");
    bad_macro_side_effects();
    good_inline_function_use();
    bad_macro_parentheses();
    good_macro_parentheses();

    printf("\n--- Section 6: Control Flow ---\n");
    bad_assignment_in_if();
    good_comparison_in_if();

    printf("\n--- Section 7: Magic Numbers ---\n");
    bad_magic_numbers(1);
    bad_magic_numbers(255);
    good_named_constants(STATUS_WARN_ENUM);
    good_named_constants(STATUS_CRITICAL_ENUM);

    printf("\n\n--- End of Demonstrations ---\n");
    return 0;
}

/*
Further Bad Practices Not Extensively Demoed Above (Conceptual):

9.  Global Variable Overuse:
    -   Bad: Using many global variables for state that could be localized or passed around.
        Makes tracking data flow hard, reduces modularity, increases risk of name clashes.
    -   Good: Minimize globals. Use `static` for file-scope globals. Pass data via parameters
        and return values. Use structs to group related state.

10. Not Using `const` Correctly:
    -   Bad: Functions that don't modify a pointer parameter but don't declare it `const char *p`.
        Not using `const` for variables that shouldn't change.
    -   Good: Use `const` to indicate intent and allow compiler optimizations.
        `const int *ptr` (pointer to const int), `int * const ptr` (const pointer to int),
        `const int * const ptr` (const pointer to const int).

11. Complex Boolean Logic Without Parentheses or Simplification:
    -   Bad: `if (a && b || c && !d)` - hard to read, precedence might be confusing.
    -   Good: `if ((a && b) || (c && !d))` or break into simpler parts/boolean variables.

12. Floating Point Comparisons:
    -   Bad: `if (my_float == 0.0)` - due to precision issues, exact comparison is risky.
    -   Good: `if (fabs(my_float - 0.0) < EPSILON)` where EPSILON is a small tolerance.

13. Division by Zero:
    -   Bad: `int result = x / y;` without checking if `y` is zero.
    -   Good: `if (y != 0) { result = x / y; } else { /* handle error }
`

14. Unclear Variable /
    Function Names : -Bad : `int x,
    y, z;
void f(int a, int b);
` - Good : `int itemCount, totalValue;
void calculate_invoice_total(int customer_id, Order *order_details);`

15. Deeply Nested Control Structures:
    -   Bad: Many nested if/else/for/while blocks. Hard to follow.
    -   Good: Refactor into smaller functions. Use early exits/returns.

16. Platform-Dependent Code Without Abstraction:
    -   Bad: Sprinkling `#ifdef _WIN32 ... #else ... #endif` everywhere.
    -   Good: Abstract platform differences into separate files/functions (e.g., a `platform_sleep_ms()` function).

17. Bit-fields with Unspecified Widths or Signedness (Portability Issues):
    -   Bad: `struct
{
    int field_a : 3;
    signed int field_b : 1;
} my_bits;` - behavior can vary.
    -   Good: Use explicit unsigned types for bit-fields (e.g., `unsigned int field_a: 3;`) and be
        aware of compiler-specific packing and alignment. Often, manual bit-masking with uintN_t is more portable.
*/