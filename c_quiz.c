// ==========================================================================
// C Quiz for Embedded Systems Roles
// ==========================================================================

// --- Instructions ---
// - Answer conceptual questions in comments below the question (`// ANSWER:`).
// - For implementation questions, write C code directly in the designated area.
// - Assume standard C11. Include necessary headers if you write functions.

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // For size_t
#include <stdlib.h> // For malloc/free/realloc (use with care!)
#include <string.h> // For string functions (if needed)

// ==========================================================================
// Section A: Memory, Pointers, and Data Representation
// ==========================================================================

// --- Question A1 (Concept) ---
// Explain the difference between the stack, the heap, and the static/global
// data segments (.data, .bss) in C regarding:
//   a) Allocation/Deallocation mechanism (who manages it, when does it happen?)
//   b) Lifetime of variables stored there.
//   c) Typical use cases for each.
//   d) Potential problems associated with each (e.g., stack overflow, memory leaks, fragmentation).
// ANSWER A1:
// a) the stack in FILO it its managed automatically, the heap is manually managed. im not sure about the global ones.
// b) the heap will live untill deleted, stack untill things fall out of scope, global untill the program terminates
// c) stack for smaller things in function calls like ints and bools, heap for larger that need to persist across functioncalls,
// global for thins that need to exist for the entire program
// d) stack is small if you have too many large local variabels or a recursive loop it can overflow.
// heap is unorganized and if it gets too full it can be fragmented with small secitons of unused memory that arent that usefull
// idk for the last one

// --- Question A2 (Concept) ---
// Where are the following typically stored in memory?
//   a) A local variable `int x;` inside `main()`.
//   b) A global variable `int g_count = 10;` outside any function.
//   c) A global variable `static int module_counter = 0;` outside any function.
//   d) Memory allocated by `malloc()`.
//   e) A string literal `"Error Code: %d\n"`.
//   f) The pointer variable itself in `char *ptr = "Hello";` (where ptr is local).
//   g) A local variable `static int call_count = 0;` inside a function.
// ANSWER A2:
// a) stack
// b) managed by the os its outside of the stack and the heap, im not really sure what to call this area
// c) same place as the global but only accessabel by the file, not sure how this is achieved, is there metadata?
// d) heap
// e) i htink the heap but im not sure with the "literal" part
// f) sack
// g) idk, how does it work when you put static inside a funciton?

// --- Question A3 (Implementation) ---
// Write a C function `bool resize_buffer(uint8_t **buffer_ptr, size_t current_size, size_t new_size)`
// that attempts to resize a dynamically allocated buffer pointed to by `*buffer_ptr`.
// - It should handle the case where `*buffer_ptr` is initially `NULL` (allocate new).
// - It should handle `new_size` being 0 (should free the buffer and set `*buffer_ptr` to `NULL`).
// - It should use `realloc()`.
// - It must correctly update the pointer pointed to by `buffer_ptr` (the caller's pointer).
// - It should return `true` on success and `false` on allocation failure.
// - IMPORTANT: Handle potential `realloc` failure where it returns `NULL` - the original
//   buffer should remain valid and pointed to by `*buffer_ptr` in this failure case.
// CODE A3:
bool resize_buffer(uint8_t **buffer_ptr, size_t current_size, size_t new_size)
{
    if (!buffer_ptr)
    {
        return false; // Cannot work with NULL pointer-to-pointer
    }

    if (new_size == 0)
    {
        free(*buffer_ptr); // free(NULL) is safe
        *buffer_ptr = NULL;
        return true;
    }

    // If *buffer_ptr is NULL, realloc acts like malloc
    uint8_t *new_buffer = realloc(*buffer_ptr, new_size);

    if (new_buffer == NULL)
    {
        // Realloc failed, original buffer (*buffer_ptr) is still valid (if it wasn't NULL)
        // Do not change *buffer_ptr
        fprintf(stderr, "Error: Failed to reallocate buffer to size %zu\n", new_size);
        return false;
    }

    // Realloc succeeded, update the caller's pointer
    *buffer_ptr = new_buffer;

    // If we grew the buffer, the new part contains uninitialized data.
    // We might want to zero it out depending on use case, e.g.:
    // if (new_size > current_size && *buffer_ptr != NULL) { // Check needed if current_size wasn't tracked when ptr was NULL
    //    memset(*buffer_ptr + current_size, 0, new_size - current_size);
    // }

    return true;
}

bool resize_buffer2(uint8_t **buffer_ptr, size_t current_size, size_t new_size)
{
    if (buffer_ptr == NULL)
    {
        fprintf(stderr, "null ptr");
        return false;
    }
    if (new_size == 0)
    {
        free(*buffer_ptr);
        *buffer_ptr = NULL;
        return true;
    }

    uint8_t *new_ptr = realloc(*buffer_ptr, new_size);
    if (new_ptr == NULL)
    {
        fprintf(stderr, "failed realloc");
        return false;
    }
    else
    {
        *buffer_ptr = new_ptr;
        if (current_size < new_size)
        {
            memset(new_ptr + current_size, 0, new_size - current_size);
        }
        return true;
    }
}

// --- Question A4 (Concept) ---
// Explain potential issues with the following code snippet and how to fix them:
// ```c
// char *create_error_message(int error_code) {
//     char local_buffer[100];
//     sprintf(local_buffer, "Error occurred: %d", error_code);
//     return local_buffer; // <-- Problem here
// }
// I think the issue here is that we are supposed to return a pointer but im a bit confused,
// if we did return &local_buffer; this would return the pointer to local_buffer but doesnt local
// buffer get removed from the stack after the return? so wouldnt the pointer point to nothing or
// garbage? wouldnt we have to make it a heap buffer? also explain sprintf here, isnt local
// buffer initialized to nothing wouldnt this print garbate?
// void use_message() {
//    char* msg = create_error_message(404);
//    printf("Message: %s\n", msg); // <-- Problem here
// }
// ```
// What C memory concept does this violate? How could this be rewritten safely?
// (Provide at least two safe alternative approaches).
// ANSWER A4:
//

// --- Question A5 (Concept & Implementation) ---
// Explain the difference between `const int *ptr`, `int * const ptr`, and
// `const int * const ptr`. Provide a short code example function for each,
// showing a valid operation and an invalid operation (that would cause a compile error).
// ANSWER A5:
// Explanation:
//
// Code Examples:
void example_const_int_ptr(const int *ptr)
{
    // valid int* newPtr;
    // ptr = newPtr;
    // invalid *prt = 10;
    printf("Value (const int *): %d\n", *ptr);
}

void example_int_const_ptr(int *const ptr)
{
    // opposite as above, can edit the int but cant edit the ptr
    printf("Value (int * const): %d\n", *ptr);
}

void example_const_int_const_ptr(const int *const ptr)
{
    // read only for both
    printf("Value (const int * const): %d\n", *ptr);
}

// --- Question A6 (Concept) ---
// Describe data alignment in C. Why is it important? Why does `sizeof(MyStruct)`
// sometimes return a value larger than the sum of `sizeof()` for all its individual members?
// Give an example struct where padding would likely occur on a typical 32-bit or 64-bit system.
// ANSWER A6:
//

// --- Question A7 (Implementation) ---
// Given `uint32_t control_register;`, write C code snippets using bitwise operators to:
//   a) Set bit 7 to 1, leaving other bits unchanged.
//   b) Clear bit 15 to 0, leaving other bits unchanged.
//   c) Toggle bit 2, leaving other bits unchanged.
//   d) Check if bit 4 is set (result should be true/false or 1/0).
//   e) Set bits 8-11 (inclusive) to the binary value `1010` (decimal 10), clearing them first.
//   f) Extract the value of bits 24-27 (inclusive) into a `uint8_t` variable, right-aligned.
// CODE A7:

uint8_t regesterManipulation(uint32_t *control_regester)
{
    *control_regester |= (1 << 7);

    *control_regester &= ~((uint32_t)1 << 15);

    *control_regester ^= (1 << 2);

    bool is_bit_set = ((*control_regester & (1 << 4)) > 0);
}

// --- Question A8 (Concept) ---
// What is endianness (Big Endian vs. Little Endian)? Imagine you receive a 32-bit unsigned
// integer `0x12345678` over a serial port, byte by byte, starting with the least significant
// byte (LSB). How would you reconstruct the correct `uint32_t` value on a Little Endian machine?
// How would it differ if your machine was Big Endian?
// ANSWER A8: i belive that big endian menas that the most signifigant bit is stored first at a
// the lowest memory address, little endian is reversed. For little endian you would just put
// the first byte in the first memor address the sencond in the next and so on its alrady in
// little endian order, for big endian you would take all the bytes recieved and
// reorder them so they go 4th 3rd 2nd 1st.

// --- Question A9 (Concept) ---
// Explain integer promotion rules in C. Give an example where performing an operation
// on two `uint8_t` variables might produce an unexpected result if the result is
// immediately assigned back to a `uint8_t` without care, especially involving bit shifts.
// ANSWER A9: I think if you have int / float the int will be promoted to a float
// if you did int / int like 2/5 neither would be performed and you would get an int back, 0.
// 0 because it takes the floor of the result not the rounded value (right?). im not sure
// how bit shift is relevent here

// ==========================================================================
// Section B: Structs, Enums, Functions, and Modularity
// ==========================================================================

// --- Question B1 (Concept) ---
// Why are header guards (`#ifndef MY_HEADER_H_ ... #endif`) essential? Describe a scenario
// in a multi-file project where omitting them would cause a compilation error.
// ANSWER B1:

// --- Question B2 (Concept) ---
// Explain the purpose and effect of the `static` keyword when used with:
//   a) A global variable (declared at file scope). How does this aid modularity?
//   b) A local variable (declared inside a function). What is its lifetime and scope?
//   c) A function definition (`static void helper_function() { ... }`).
// ANSWER B2:
// a) Only the file it was declared in has access
// b) Scoped to that function but is stored across function calls
// c) Not sure here please explain

// --- Question B3 (Implementation) ---
// Refactor the following code to use an `enum` for the message types and a `struct`
// to represent the message, improving readability and type safety. Show the enum
// definition, the struct definition, and rewrite the `process_message` function signature
// and its internal switch statement.

#define TYPE_TEMP_READING 1
#define TYPE_PRESSURE_READING 2
#define TYPE_SET_MODE 3

void process_message(int msg_type, int data1, float data2)
{
    switch (msg_type)
    {
    case 1: // TYPE_TEMP_READING
        printf("Temp: %d C\n", data1);
        break;
    case 2: // TYPE_PRESSURE_READING
        printf("Pressure: %.2f Pa\n", data2);
        break;
    case 3: // TYPE_SET_MODE
        printf("Setting mode to %d\n", data1);
        break;
    default:
        printf("Unknown message type\n");
    }
}

#define MAX_DATA_LENGTH 100

typedef enum
{
    TEMP,
    PRESURE,
    SET_MODE,
    DATA_PAYLOAD,
} MessageType;

typedef struct
{
    MessageType type;
    union
    {
        int temp_c;
        float pressure_pa;
        int mode_id;
        struct
        {
            int data[MAX_DATA_LENGTH];
            int length
        } data_payload;
    } payload;
} Message;

void process_message2(const Message *message)
{
    if (!message)
        return;

    switch (message->type)
    {
    case TEMP: // TYPE_TEMP_READING
        printf("Temp: %d C\n", message->payload.temp_c);
        break;
    case PRESURE: // TYPE_PRESSURE_READING
        printf("Pressure: %.2f Pa\n", message->payload.pressure_pa);
        break;
    case SET_MODE: // TYPE_SET_MODE
        printf("Setting mode to %d\n", message->payload.mode_id);
        break;
    default:
        printf("Unknown message type\n");
    }
};

// --- Question B4 (Concept) ---
// In C, how do you typically handle situations where multiple modules might
// conceptually have a function with the same purpose (e.g., `init()`, `get_status()`)?
// Describe the common C convention for avoiding naming collisions.
// ANSWER B4:
//

// --- Question B5 (Implementation - Open Ended) ---
// Design and implement a simple Finite State Machine (FSM) in C for controlling an LED.
// States: OFF, ON, BLINKING.
// Events: BUTTON_PRESS, TIMER_TICK.
// Requirements:
// - Define an `enum` for states and events.
// - Create a function `void led_fsm_init(void)` to set the initial state (OFF).
// - Create a function `void led_fsm_handle_event(LedEvent event)` that updates the
//   state based on the current state and the event:
//     - OFF + BUTTON_PRESS -> ON
//     - ON + BUTTON_PRESS -> BLINKING
//     - BLINKING + BUTTON_PRESS -> OFF
//     - BLINKING + TIMER_TICK -> Toggle LED output (simulate with printf)
// - Maintain the current state using a static variable within the `.c` file.
// - Add necessary includes and potentially a header file declaration.
// (Focus on the state transition logic, not hardware interaction).
// CODE B5:

typedef enum
{
    BUTTON_PRESS,
    TIMER_TICK,
} Events;

typedef enum
{
    OFF,
    ON,
    BLINKING,
} State;

static State LED_state;

void led_fsm_init()
{
    LED_state = OFF;
}

void led_fsm__handle_event(Events event)
{
    switch (event)
    {
    case (BUTTON_PRESS):
        if (LED_state == ON)
        {
            LED_state = BLINKING;
        }
        else if (LED_state == OFF)
        {
            LED_state = ON;
        }
        else if (LED_state == BLINKING)
        {
            LED_state = OFF;
        }
        break;
    case (TIMER_TICK):
        printf("toggling led");
        break;
    }
}

// --- Question B6 (Concept) ---
// What are function pointers in C? Describe two common use cases for them
// in embedded systems (e.g., callbacks, dispatch tables).
// ANSWER B6:
//

// --- Question B7 (Implementation - Open Ended) ---
// Design and implement functions for a simple circular buffer (ring buffer) for `uint8_t` data.
// Requirements:
// - Define a `struct CircularBuffer` containing a data buffer (`uint8_t *buffer`),
//   capacity (`size_t capacity`), head index (`size_t head`), tail index (`size_t tail`),
//   and a flag or counter for fullness (`size_t count` or `bool is_full`).
// - `bool cbuf_init(CircularBuffer *cbuf, size_t capacity)`: Allocates memory for the
//   internal buffer and initializes the struct members. Returns false on allocation failure.
// - `void cbuf_destroy(CircularBuffer *cbuf)`: Frees the allocated buffer memory.
// - `bool cbuf_is_full(const CircularBuffer *cbuf)`: Returns true if the buffer is full.
// - `bool cbuf_is_empty(const CircularBuffer *cbuf)`: Returns true if the buffer is empty.
// - `bool cbuf_write(CircularBuffer *cbuf, uint8_t data)`: Writes data to the buffer
//   at the head position, advances head. Returns false if the buffer is full.
// - `bool cbuf_read(CircularBuffer *cbuf, uint8_t *data_out)`: Reads data from the buffer
//   at the tail position, advances tail. Stores the data in `*data_out`. Returns false
//   if the buffer is empty.
// Handle wrap-around logic for head and tail indices correctly.
// CODE B7:

// ==========================================================================
// Section C: Preprocessor, Error Handling, and Safety
// ==========================================================================

// --- Question C1 (Concept) ---
// Explain the difference between `#if`, `#ifdef`, and `#ifndef` preprocessor directives.
// Provide a use case for each in an embedded context.
// ANSWER C1:
//

// --- Question C2 (Concept) ---
// What are macros with arguments (function-like macros)? Give an example.
// What are some potential dangers or pitfalls of using function-like macros
// compared to actual functions (e.g., multiple evaluation of arguments, operator precedence)?
// ANSWER C2:
//

// --- Question C3 (Concept) ---
// Describe common error handling strategies in C for functions that can fail.
// Discuss the pros and cons of:
//   a) Returning error codes (e.g., -1, 0, specific positive codes).
//   b) Setting a global error variable (like `errno`).
//   c) Using output parameters (pointers) to return status or detailed error info.
// ANSWER C3:
// a)
// b)
// c)

// --- Question C4 (Implementation) ---
// Write a function `bool parse_key_value(const char *line, char *key_out, size_t key_max_len, int *value_out)`
// that parses a string assumed to be in the format "KEY=VALUE" (e.g., "TIMEOUT=100").
// - It should extract the KEY part into `key_out` (up to `key_max_len - 1` chars, always null-terminate).
// - It should convert the VALUE part into an integer and store it in `*value_out`.
// - It should handle potential errors: missing '=', non-numeric value part, key too long.
// - Return `true` on successful parsing, `false` otherwise.
// - You can use functions from `<string.h>` and `<stdlib.h>` (like `strchr`, `atoi`/`strtol`, `strncpy`). Be mindful of their behavior.
// CODE C4:
bool parse_key_value(const char *line, char *key_out, size_t key_max_len, int *value_out)
{
    if (!line || !key_out || key_max_len == 0 || !value_out)
    {
        return false; // Invalid arguments
    }

    const char *equals_ptr = strchr(line, '=');
    if (!equals_ptr)
    {
        return false; // No '=' found
    }

    size_t key_len = equals_ptr - line; // Calculate length of the key part
    if (key_len == 0)
    {
        return false; // Empty key
    }
    if (key_len >= key_max_len)
    {
        fprintf(stderr, "Warning: Key '%s' too long for buffer (max %zu)\n", line, key_max_len - 1);
        key_len = key_max_len - 1; // Truncate, but indicate failure later maybe? Or return false now.
        // Let's return false if key doesn't fit entirely
        return false;
    }

    // Copy the key
    strncpy(key_out, line, key_len);
    key_out[key_len] = '\0'; // Ensure null termination (strncpy might not if src is longer)

    // Parse the value part
    const char *value_ptr = equals_ptr + 1;
    if (*value_ptr == '\0')
    {
        return false; // Empty value part
    }

    char *end_ptr;                                       // For strtol error checking
    long parsed_value = strtol(value_ptr, &end_ptr, 10); // Base 10

    // Check for conversion errors reported by strtol
    // *end_ptr should point to the end of the string if successful
    // errno can be checked for ERANGE if value is out of long range
    if (*end_ptr != '\0')
    {
        // Could also check if value_ptr == end_ptr (no digits converted)
        return false; // Conversion failed (non-numeric characters found)
    }
    // Optional: Check for overflow/underflow if expecting values within int range
    // if (parsed_value > INT_MAX || parsed_value < INT_MIN) { return false; }

    *value_out = (int)parsed_value; // Assign the successfully parsed value
    return true;
}

// --- Question C5 (Concept) ---
// What is MISRA C? What is its primary goal, and in what kind of
// software development is it most commonly applied? Give an example of a
// typical MISRA C rule (conceptual, e.g., related to pointers, dynamic memory, or control flow).
// ANSWER C5:
//

// --- Question C6 (Concept) ---
// In the context of the Joby job description (safety-critical flight systems),
// why is exhaustive testing (unit tests, integration tests, hardware-in-the-loop)
// so critical? How does writing modular C code (like the modules in the example project)
// facilitate better testing?
// ANSWER C6:
//

// ==========================================================================
// End of Quiz
// ==========================================================================