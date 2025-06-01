#include <stdio.h>  // For printf, fprintf, stderr
#include <stdlib.h> // For malloc, calloc, realloc, free
#include <string.h> // For memset (to show initialization comparison)

int main()
{
    printf("--- C Dynamic Memory Allocation Examples ---\n");

    // =======================================================
    // 1. malloc: Allocate uninitialized memory
    // =======================================================
    printf("\n--- malloc Example ---\n");

    int *p_int = NULL; // Pointer to hold the address
    size_t num_ints = 5;

    // Allocate memory for 5 integers on the heap.
    // sizeof(int) * num_ints calculates the total bytes needed.
    // malloc returns a void* (generic pointer), so we cast it to int*.
    p_int = (int *)malloc(sizeof(int) * num_ints);

    // **CRITICAL: Always check if malloc succeeded!**
    if (p_int == NULL)
    {
        fprintf(stderr, "Error: malloc failed to allocate memory!\n");
        return 1; // Exit indicating error
    }

    printf("malloc allocated memory for %zu integers at address: %p\n", num_ints, (void *)p_int);

    // **Memory allocated by malloc is UNINITIALIZED (contains garbage)**
    printf("Initial values in malloc'd memory (garbage):\n");
    for (size_t i = 0; i < num_ints; ++i)
    {
        printf("  p_int[%zu] = %d (could be anything)\n", i, p_int[i]);
        // Explicitly initialize if needed
        p_int[i] = i * 10;
    }

    printf("Values after initialization:\n");
    for (size_t i = 0; i < num_ints; ++i)
    {
        printf("  p_int[%zu] = %d\n", i, p_int[i]);
    }

    // **IMPORTANT: Deallocate memory allocated with malloc using free()**
    printf("Freeing malloc'd memory...\n");
    free(p_int);
    p_int = NULL; // Good practice: Avoid dangling pointers

    // =======================================================
    // 2. calloc: Allocate ZERO-INITIALIZED memory
    // =======================================================
    printf("\n--- calloc Example ---\n");

    double *p_double = NULL;
    size_t num_doubles = 3;

    // Allocate memory for 3 doubles on the heap.
    // calloc takes number of elements and size of each element.
    // It returns void* and clears the allocated memory to zero.
    p_double = (double *)calloc(num_doubles, sizeof(double));

    if (p_double == NULL)
    {
        fprintf(stderr, "Error: calloc failed to allocate memory!\n");
        return 1;
    }

    printf("calloc allocated memory for %zu doubles at address: %p\n", num_doubles, (void *)p_double);

    // **Memory allocated by calloc IS zero-initialized**
    printf("Initial values in calloc'd memory (zeroed):\n");
    for (size_t i = 0; i < num_doubles; ++i)
    {
        printf("  p_double[%zu] = %f\n", i, p_double[i]);
    }

    // **IMPORTANT: Deallocate memory allocated with calloc using free()**
    printf("Freeing calloc'd memory...\n");
    free(p_double);
    p_double = NULL;

    // =======================================================
    // 3. realloc: Resize previously allocated memory
    // =======================================================
    printf("\n--- realloc Example ---\n");

    char *p_char_buf = NULL;
    size_t initial_size = 10;
    size_t larger_size = 20;
    size_t smaller_size = 5;

    // Start with malloc (or calloc)
    p_char_buf = (char *)malloc(initial_size);
    if (p_char_buf == NULL)
    {
        fprintf(stderr, "Error: Initial malloc for realloc failed!\n");
        return 1;
    }
    printf("Allocated initial buffer (size %zu) at %p\n", initial_size, (void *)p_char_buf);
    // Initialize it for demonstration
    memset(p_char_buf, 'A', initial_size);

    // **Resize to a LARGER size**
    printf("Attempting to resize to %zu bytes...\n", larger_size);
    // **SAFE REALLOC PATTERN:** Use a temporary pointer!
    char *p_temp = realloc(p_char_buf, larger_size);
    if (p_temp == NULL)
    {
        // **IMPORTANT:** If realloc fails, the ORIGINAL pointer (p_char_buf)
        // is still valid and points to the original memory block.
        // We MUST still free the original block later.
        fprintf(stderr, "Error: realloc to larger size failed! Original buffer still valid.\n");
        // Keep p_char_buf as it is, don't assign p_temp
    }
    else
    {
        // Realloc succeeded. The old block might have been moved.
        // Update our main pointer to the new (potentially moved) block.
        p_char_buf = p_temp;
        printf("Resized to %zu bytes successfully at %p\n", larger_size, (void *)p_char_buf);
        // The original content (first 'initial_size' bytes) is preserved.
        // The *new* part (from index initial_size to larger_size-1) is UNINITIALIZED.
        // Let's initialize the new part
        memset(p_char_buf + initial_size, 'B', larger_size - initial_size);
        printf("Initialized new part of buffer.\n");
    }

    // **Resize to a SMALLER size**
    printf("Attempting to resize to %zu bytes...\n", smaller_size);
    p_temp = realloc(p_char_buf, smaller_size);
    if (p_temp == NULL)
    {
        // Should be unlikely when shrinking, but check anyway.
        fprintf(stderr, "Error: realloc to smaller size failed! Original buffer still valid.\n");
    }
    else
    {
        p_char_buf = p_temp;
        printf("Resized to %zu bytes successfully at %p\n", smaller_size, (void *)p_char_buf);
        // Content is preserved up to the new, smaller size.
    }

    // **Using realloc like free**
    printf("Attempting to resize to 0 bytes (like free)...\n");
    p_temp = realloc(p_char_buf, 0);
    if (p_temp == NULL)
    {
        // Standard says return value might be NULL or a unique ptr
        // that can be safely passed to free(). Best to assume it's freed.
        printf("Resized to 0. Pointer might be NULL now.\n");
        p_char_buf = NULL; // Treat it as freed
    }
    else
    {
        // Or it might return a unique pointer that *must* be freed
        printf("Resized to 0. Got non-NULL pointer %p. Freeing it...\n", (void *)p_temp);
        free(p_temp);
        p_char_buf = NULL;
    }

    // **Using realloc like malloc**
    printf("Using realloc with NULL initial pointer (like malloc)...\n");
    char *p_realloc_as_malloc = NULL;
    p_realloc_as_malloc = realloc(p_realloc_as_malloc, 15); // Same as malloc(15)
    if (p_realloc_as_malloc == NULL)
    {
        fprintf(stderr, "Error: realloc(NULL, ...) failed!\n");
        // Need to free original p_char_buf if realloc to 0 failed above!
        // This error handling gets complicated, shows why RAII is nice.
        free(p_char_buf); // Free the potentially still valid original pointer if previous realloc(0) failed
        return 1;
    }
    else
    {
        printf("realloc(NULL, 15) succeeded at %p.\n", (void *)p_realloc_as_malloc);
        // Don't forget to free this one too!
        free(p_realloc_as_malloc);
    }

    // **IMPORTANT: Ensure final allocated block (if any) is freed**
    // If the realloc to 0 failed, p_char_buf might still hold the memory!
    if (p_char_buf != NULL)
    {
        printf("Freeing final p_char_buf (needed if realloc(0) failed)...\n");
        free(p_char_buf);
    }

    // =======================================================
    // 4. Memory Manipulation Functions (memset, memcpy, memmove)
    // =======================================================
    printf("\n--- Memory Manipulation Functions ---\n");

    // --- memset: Fill a block of memory with a specific byte value ---
    printf("\n* memset Example *\n");
    char mem_buffer[20];
    // Initialize the whole buffer to null terminators for clean printing later
    memset(mem_buffer, '\0', sizeof(mem_buffer));
    strcpy(mem_buffer, "Hello World!"); // Put some initial data
    printf("Original mem_buffer: '%s'\n", mem_buffer);

    // Set the first 5 bytes of mem_buffer to 'X'
    memset(mem_buffer, 'X', 5);
    printf("After memset(mem_buffer, 'X', 5): '%s'\n", mem_buffer);

    // Set a portion of the buffer to zeros
    memset(mem_buffer + 2, 0, 3); // Zero out 3 bytes starting from index 2
    printf("After memset(mem_buffer + 2, 0, 3): 'XX\0\0\0World!' (partial string due to embedded nulls)\n");
    // Printing character by character to show the nulls:
    printf("Char by char: ");
    for (size_t i = 0; i < 12; ++i)
    { // Print relevant part
        if (mem_buffer[i] == '\0')
            printf("[NULL]");
        else
            printf("%c", mem_buffer[i]);
    }
    printf("\n");

    // --- memcpy: Copy a block of memory from a source to a destination ---
    // **IMPORTANT:** Behavior is UNDEFINED if source and destination regions overlap.
    printf("\n* memcpy Example (non-overlapping) *\n");
    char src_data[] = "CopyThis!";
    char dest_data[20];
    memset(dest_data, 0, sizeof(dest_data)); // Clear destination

    printf("Source data: '%s'\n", src_data);
    memcpy(dest_data, src_data, strlen(src_data) + 1); // +1 to include null terminator
    printf("Destination data after memcpy: '%s'\n", dest_data);

    int int_src[] = {10, 20, 30, 40, 50};
    int int_dest[5];
    memcpy(int_dest, int_src, sizeof(int_src)); // Copy entire array of ints
    printf("Copied integers: ");
    for (size_t i = 0; i < 5; ++i)
        printf("%d ", int_dest[i]);
    printf("\n");

    // --- memmove: Copy a block of memory, handles overlapping regions safely ---
    // Use memmove when source and destination might overlap.
    printf("\n* memmove Example (overlapping) *\n");
    char move_buffer[] = "abcdefghij"; // 10 chars + null
    printf("Original move_buffer: '%s'\n", move_buffer);

    // Example 1: Overlap, dest is after src (move_buffer+2 from move_buffer, 5 bytes)
    // Effectively: "ab|cde|fghij" -> "ab|abcde|ij" (conceptually, 'cde' shifts right)
    // Should become "ab cde de ij" -> "ab cde cde ij"
    // move_buffer + 2 = cdefghij
    // move_buffer     = abcdefghij
    // copy from move_buffer (src) to move_buffer + 2 (dest), 5 bytes
    // target: move_buffer becomes "ababcdehij"
    memmove(move_buffer + 2, move_buffer, 5);
    printf("After memmove(move_buffer+2, move_buffer, 5): '%s'\n", move_buffer);
    // Expected: "ababcdehij"

    // Reset buffer for next example
    strcpy(move_buffer, "abcdefghij");
    printf("Reset move_buffer: '%s'\n", move_buffer);
    // Example 2: Overlap, dest is before src (move_buffer from move_buffer+2, 5 bytes)
    // Effectively: "ab|cde|fghij" -> "cde|fghij" (conceptually, 'cde' shifts left)
    // copy from move_buffer + 2 (src = "cdefg...") to move_buffer (dest), 5 bytes
    // target: move_buffer becomes "cdefgefghij" (no, just "cdefghij")
    memmove(move_buffer, move_buffer + 2, 5);
    printf("After memmove(move_buffer, move_buffer+2, 5): '%s'\n", move_buffer);
    // Expected: "cdefgfghij"

    printf("\n--- Differences from C++ new/delete ---\n");
    printf("1. Type Safety: malloc/calloc/realloc return void*, require explicit casts. `new` returns typed pointer.\n");
    printf("2. Initialization: malloc = garbage, calloc = zeros, `new` = calls constructor.\n");
    printf("3. Deallocation: free() just deallocates memory. `delete`/`delete[]` call destructors FIRST, then deallocate.\n");
    printf("4. Operators vs Functions: `new`/`delete` are operators (can be overloaded). malloc/free family are library functions.\n");
    printf("5. Array Size: `free()` doesn't know array size. `delete[]` usually does (implementation dependent).\n");
    printf("6. Error Handling: malloc family returns NULL on failure. `new` throws std::bad_alloc exception (by default).\n");
    printf("7. Zero Size: malloc(0) is implementation-defined (NULL or unique ptr). `new Type[0]` is allowed by standard.\n");

    printf("\n--- C Dynamic Memory Examples Complete ---\n");
    return 0;
}

/*
Differences Summary: C vs C++

Feature          | C (malloc/calloc/realloc/free)       | C++ (new/delete/delete[])
-----------------|--------------------------------------|----------------------------------------
Return Type      | void* (needs cast)                   | Typed pointer (e.g., int*)
Initialization   | malloc: None (garbage)               | Calls constructor (default or custom)
                 | calloc: Zero-initialized             |
Deallocation     | free(): Deallocates memory only       | Calls destructor, then deallocates
Type             | Library Functions                    | Operators (overloadable)
Arrays           | Must track size yourself for free()   | delete[] usually infers size
Error Handling   | Returns NULL                         | Throws std::bad_alloc exception
Zero Size Alloc  | malloc(0): Implementation-defined    | new T[0]: Standard allows
Type Safety      | Low (via void*)                      | High (typed)
Object Lifecycle | No constructor/destructor calls     | Automatic constructor/destructor calls
*/