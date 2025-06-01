// ==========================================================================
// improvement_examples.cpp - C++ Concepts for Embedded Interviews
// ==========================================================================

#include <iostream>  // For console output
#include <vector>    // For std::vector examples
#include <memory>    // For smart pointers (unique_ptr, shared_ptr)
#include <string>    // For std::string
#include <cstdint>   // For fixed-width integers like uint32_t, uintptr_t
#include <stdexcept> // For exceptions (e.g., from bad_alloc)

// --- Helper Class for Destructor Examples ---
class MyResource
{
public:
    int id_;
    MyResource() : id_(0) {};
    MyResource(int id) : id_(id)
    {
        std::cout << "  MyResource [" << id_ << "] Constructor called." << std::endl;
    }
    MyResource(int id, int int2, std::string string) : id_(id) {}
    ~MyResource()
    {
        // Destructor: This is automatically called when the object is destroyed.
        // Crucial for releasing resources (closing files, freeing other memory, etc.)
        std::cout << "  MyResource [" << id_ << "] Destructor called." << std::endl;
    }
    void use() const
    {
        std::cout << "  Using MyResource [" << id_ << "]" << std::endl;
    }
};

// ==========================================================================
// Section 1: Manual Memory Management (new/delete, new[]/delete[])
// ==========================================================================
void manual_memory_management_examples()
{
    std::cout << "\n--- Section 1: Manual Memory Management ---" << std::endl;

    // --- Single Object Allocation ---
    std::cout << "\n* Single Object Allocation *" << std::endl;
    MyResource *singlePtr = nullptr;
    try
    {
        singlePtr = new MyResource(1); // Allocate one object on the heap
        if (singlePtr)
        { // Check if allocation succeeded (optional, new throws on failure)
            singlePtr->use();
        }
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Allocation Failed: " << e.what() << std::endl;
        // Handle allocation failure
    }

    // Deallocate the single object
    // Must use 'delete' (without []) for single objects allocated with 'new'
    std::cout << "Deleting single object..." << std::endl;
    delete singlePtr;
    singlePtr = nullptr; // Good practice to nullify pointer after deletion

    // --- Array Allocation ---
    std::cout << "\n* Array Allocation *" << std::endl;
    MyResource *arrayPtr = nullptr;
    int arraySize = 3;
    try
    {
        arrayPtr = new MyResource[arraySize]; // Allocate an array of objects
                                              // Calls constructor for each element
        if (arrayPtr)
        {
            // Access array elements (example)
            arrayPtr[0].use();
            (arrayPtr + 1)->use(); // Pointer arithmetic also works
        }
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Array Allocation Failed: " << e.what() << std::endl;
        // Handle allocation failure
    }

    // Deallocate the array
    // MUST use 'delete[]' for arrays allocated with 'new[]'
    std::cout << "Deleting array object..." << std::endl;
    delete[] arrayPtr;
    arrayPtr = nullptr;

    // ** CRITICAL POINT: delete vs delete[] **
    // Using 'delete arrayPtr;' (without []) here would be UNDEFINED BEHAVIOR.
    // Why? Because the system wouldn't know how many objects are in the array.
    // It would likely only call the destructor for the *first* element (arrayPtr[0]),
    // leading to resource leaks if ~MyResource did more complex cleanup.
    // It also might free the wrong amount of memory, corrupting the heap.
    // ALWAYS MATCH new with delete, and new[] with delete[].
}

// ==========================================================================
// Section 2: Operator Precedence
// ==========================================================================

void operator_precedence_examples()
{
    std::cout << "\n--- Section 2: Operator Precedence ---" << std::endl;

    double numbers[] = {10.1, 20.2, 30.3}; // Simple C-style array on stack
    double *pNum = numbers;                // Pointer points to the first element

    // Accessing array elements via pointer:
    // The subscript operator [] has higher precedence than dereference *

    // Incorrect attempt (like in question2): *pNum[1]
    // This is parsed as *(pNum[1]). pNum[1] is equivalent to *(pNum + 1),
    // which gets the value 20.2. Then you try to dereference a double ( *(20.2) ),
    // which is meaningless and a compile error.
    // // std::cout << *pNum[1]; // COMPILE ERROR

    // Correct ways to access the element at index 1 (value 20.2):
    std::cout << "pNum[1]: " << pNum[1] << std::endl;         // Preferred array syntax
    std::cout << "*(pNum + 1): " << *(pNum + 1) << std::endl; // Pointer arithmetic equivalent

    // Accessing members via pointers:
    MyResource resObj(99);
    MyResource *resPtr = &resObj;

    // Using arrow operator -> (preferred for pointers)
    std::cout << "ID via ->: " << resPtr->id_ << std::endl;
    resPtr->use();

    // Using dereference (*) and dot (.) operator
    // Parentheses are required because . has higher precedence than *
    // (*resPtr) gets the object, then .id_ accesses the member.
    std::cout << "ID via (*).: " << (*resPtr).id_ << std::endl;
    (*resPtr).use();

    // Incorrect: *resPtr.id_
    // Parsed as *(resPtr.id_). Tries to access member 'id_' of the *pointer* itself
    // (which fails) and then dereference the result.
    // // std::cout << *resPtr.id_; // COMPILE ERROR
}

// ==========================================================================
// Section 3: Range-Based For Loops vs. Raw Pointers/Arrays
// ==========================================================================
void range_based_for_examples()
{
    std::cout << "\n--- Section 3: Range-Based For Loops ---" << std::endl;

    // Works with standard containers like std::vector
    std::vector<int> vec = {10, 20, 30};
    std::cout << "Iterating std::vector: ";
    for (int val : vec)
    { // requires vec.begin() and vec.end()
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Works with C-style arrays allocated on the stack
    int c_array[] = {100, 200, 300};
    std::cout << "Iterating C-style stack array: ";
    for (int val : c_array)
    { // Compiler knows the size, can deduce begin/end
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Does NOT work directly with raw pointers from new[]
    int size = 4;
    double *heap_array = new double[size]{1.1, 2.2, 3.3, 4.4};
    std::cout << "Iterating raw heap array (manual): ";
    for (int i = 0; i < size; ++i)
    { // Manual loop needed
        std::cout << heap_array[i] << " ";
    }
    std::cout << std::endl;

    // Why doesn't range-based for work directly on heap_array?
    // Because a raw pointer (double*) doesn't carry size information and doesn't
    // inherently provide the begin() and end() iterators that range-based for requires.
    // The loop doesn't know where the array ends.
    // // for (double val : heap_array) { // COMPILE ERROR
    // //    std::cout << val << " ";
    // // }

    // Modern C++ solution: std::span (C++20)
    // A span provides a non-owning *view* over a contiguous sequence (like a raw array).
    // #include <span> // Needed if using span
    // std::span<double> heap_span(heap_array, size);
    // std::cout << "Iterating raw heap array via std::span: ";
    // for (double val : heap_span) { // Span provides begin/end
    //     std::cout << val << " ";
    // }
    // std::cout << std::endl;

    delete[] heap_array; // Don't forget cleanup!
}

// ==========================================================================
// Section 4: Modern C++ - Smart Pointers
// ==========================================================================
void smart_pointer_examples()
{
    std::cout << "\n--- Section 4: Smart Pointers ---" << std::endl;

    // Problem: Manual memory management is error-prone (leaks, double delete).
    // Solution: Smart pointers automate deletion using RAII (Resource Acquisition Is Initialization).
    //           Resource is released when the smart pointer object goes out of scope.

    // --- std::unique_ptr ---
    // - Exclusive ownership (only one unique_ptr can own the resource at a time).
    // - Lightweight, almost zero overhead compared to raw pointers.
    // - Cannot be copied, but can be *moved*.
    // - PREFERRED CHOICE when single ownership is sufficient.
    std::cout << "\n* std::unique_ptr (Single Object) *" << std::endl;
    {
        // Use std::make_unique<Type>(constructor_args...) - safer (exception guarantee)
        std::unique_ptr<MyResource> u_ptr1 = std::make_unique<MyResource>(20);

        if (u_ptr1)
        { // Can check if it owns a resource (not null)
            u_ptr1->use();
        }

        // std::unique_ptr<MyResource> u_ptr_copy = u_ptr1; // COMPILE ERROR: Cannot copy unique_ptr

        // Move ownership
        std::unique_ptr<MyResource> u_ptr2 = std::move(u_ptr1);
        std::cout << "Ownership moved." << std::endl;

        if (!u_ptr1)
        { // u_ptr1 is now empty (nullptr)
            std::cout << "u_ptr1 is now null." << std::endl;
        }
        if (u_ptr2)
        {
            u_ptr2->use();
        }
        // u_ptr2 goes out of scope here, automatically calls delete on the MyResource(10)
        std::cout << "u_ptr2 going out of scope..." << std::endl;
    }
    std::cout << "MyResource(10) should be deleted now." << std::endl;

    std::cout << "\n* std::unique_ptr (Array) *" << std::endl;
    {
        int size = 2;
        // Use specific syntax for arrays: std::unique_ptr<Type[]>
        // Use make_unique<Type[]>(size) for arrays (C++20)
        // Or new Type[size] (older C++ versions)
        std::unique_ptr<MyResource[]> u_arr_ptr = std::make_unique<MyResource[]>(size);
        // std::unique_ptr<MyResource[]> u_arr_ptr(new MyResource[size]); // Older way

        if (u_arr_ptr)
        {
            u_arr_ptr[0].use(); // Access elements using []
            u_arr_ptr[1].use();
        }
        // u_arr_ptr goes out of scope here, automatically calls delete[]
        std::cout << "u_arr_ptr going out of scope..." << std::endl;
    }
    std::cout << "Array resources should be deleted now." << std::endl;

    // --- std::shared_ptr ---
    // - Shared ownership (multiple shared_ptrs can own the same resource).
    // - Uses reference counting to track owners.
    // - Resource deleted only when the *last* shared_ptr owning it is destroyed/reset.
    // - Higher overhead than unique_ptr due to reference count management.
    // - Use when shared ownership is genuinely required by the design.
    std::cout << "\n* std::shared_ptr *" << std::endl;
    std::shared_ptr<MyResource> s_ptr1;
    {
        // Use std::make_shared<Type>(constructor_args...) - generally preferred (efficiency)
        std::shared_ptr<MyResource> s_ptr_inner = std::make_shared<MyResource>(20);
        std::cout << "Resource(20) use_count: " << s_ptr_inner.use_count() << std::endl; // Count = 1

        s_ptr1 = s_ptr_inner;                                                                  // Copying is allowed, increments reference count
        std::cout << "Resource(20) use_count after copy: " << s_ptr1.use_count() << std::endl; // Count = 2

        std::shared_ptr<MyResource> s_ptr2 = s_ptr1;                                               // Another copy
        std::cout << "Resource(20) use_count after 2nd copy: " << s_ptr2.use_count() << std::endl; // Count = 3

        s_ptr_inner->use();
        s_ptr1->use();
        s_ptr2->use();

        std::cout << "s_ptr_inner and s_ptr2 going out of scope..." << std::endl;
        // s_ptr_inner goes out of scope (count becomes 2)
        // s_ptr2 goes out of scope (count becomes 1)
    }
    std::cout << "Resource(20) use_count after inner scope: " << s_ptr1.use_count() << std::endl; // Count = 1
    std::cout << "s_ptr1 going out of scope..." << std::endl;
    // s_ptr1 goes out of scope, count becomes 0, resource is deleted.
}

// ==========================================================================
// Section 5: Modern C++ - Constants (const, constexpr, enum class)
// ==========================================================================

// --- #define ---
// Preprocessor text substitution - No type safety, global scope issues
#define MAX_BUFFER_SIZE 1024
#define STATUS_ERROR -1

// --- const ---
// Typed constant, value evaluated at runtime (usually)
const int TIMEOUT_MS = 100;
const double PI = 3.14159;

// --- constexpr ---
// Typed constant, value MUST be evaluatable at COMPILE TIME.
// Often preferred for true constants, allows use in contexts requiring
// compile-time values (e.g., array sizes, template arguments).
constexpr int NUM_SENSORS = 4;
constexpr double GRAVITY_ACCEL = 9.80665;
constexpr uint32_t PERIPHERAL_BASE_ADDR = 0x40010000; // Example address

// --- enum class ---
// Type-safe enumeration, strongly scoped.
// Preferred over plain 'enum' or #defines for related constants.
enum class LedColor : uint8_t
{ // Can specify underlying type
    OFF = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

enum class DeviceState
{
    IDLE,
    CONFIGURING,
    ACTIVE,
    ERROR
};

void constant_examples()
{
    std::cout << "\n--- Section 5: Constants ---" << std::endl;

    int buffer[MAX_BUFFER_SIZE]; // #define works for array size
    buffer[0] = STATUS_ERROR;
    std::cout << "Buffer size (from #define): " << MAX_BUFFER_SIZE << std::endl;

    if (TIMEOUT_MS > 50)
    {
        std::cout << "Timeout (from const): " << TIMEOUT_MS << "ms" << std::endl;
    }

    // int sensorData[NUM_SENSORS]; // constexpr works for array size
    std::cout << "Number of sensors (from constexpr): " << NUM_SENSORS << std::endl;
    std::cout << "Peripheral base (from constexpr): 0x" << std::hex << PERIPHERAL_BASE_ADDR << std::dec << std::endl;

    LedColor color = LedColor::RED;
    DeviceState state = DeviceState::ACTIVE;

    // if (color == 1) {} // COMPILE ERROR: Cannot compare LedColor directly to int
    // if (color == DeviceState::ACTIVE) {} // COMPILE ERROR: Different enum class types

    if (color == LedColor::RED)
    {
        std::cout << "LED color is RED" << std::endl;
    }

    std::cout << "Device state code (needs cast): " << static_cast<int>(state) << std::endl;
}

// ==========================================================================
// Section 6: Hardware Interaction (volatile, struct overlay)
// ==========================================================================

// Assume this struct mirrors the memory layout of a hypothetical Timer peripheral
struct TimerRegisters
{
    volatile uint32_t CTRL;     // Control Register (e.g., start/stop, mode)
    volatile uint32_t STATUS;   // Status Register (e.g., interrupt flags)
    volatile uint32_t COUNT;    // Current Counter Value
    volatile uint32_t PRESCALE; // Clock Prescaler
    // Add padding if necessary to match hardware layout
    // volatile uint32_t RESERVED;
}; // Size of this struct must match the hardware register block size

// Use constexpr for the base address (known at compile time)
constexpr uintptr_t TIMER1_BASE_ADDRESS = 0x40010400; // Example address

void hardware_interaction_examples()
{
    std::cout << "\n--- Section 6: Hardware Interaction ---" << std::endl;

    // Create a pointer to the Timer register block using reinterpret_cast
    // reinterpret_cast is needed to convert the integer address to a pointer type.
    // Note: This assumes the address is valid and mapped on the target hardware!
    TimerRegisters *const TIMER1 = reinterpret_cast<TimerRegisters *>(TIMER1_BASE_ADDRESS);

    // Why 'volatile' is CRITICAL:
    // 1. Prevents Compiler Optimization: Hardware registers can change unexpectedly
    //    (e.g., COUNT increments, STATUS flags set by hardware). 'volatile' forces
    //    the compiler to generate code that reads from or writes to the actual memory
    //    address *every time* it's accessed in the code. Without volatile, the
    //    compiler might cache a value in a CPU register or optimize away reads/
    //    writes it deems unnecessary based *only* on the C++ code flow.
    // 2. Ensures Side Effects: Some registers have side effects on read or write
    //    (e.g., reading a status register might clear flags). 'volatile' ensures
    //    these reads/writes actually happen.

    // Example Interaction (Conceptual - assumes hardware exists):
    std::cout << "Configuring Timer1 at 0x" << std::hex << TIMER1_BASE_ADDRESS << std::dec << std::endl;

    // Write to control register (e.g., enable timer, set mode)
    // The -> operator works because TIMER1 is a pointer to the struct.
    TIMER1->CTRL = (TIMER1->CTRL & ~(0x3 << (0 * 2))) | (0x01 << (0 * 2));
    std::cout << "  Timer CTRL set (write)." << std::endl;

    // Write to prescaler
    TIMER1->PRESCALE = 72; // Example: Divide clock by 72+1
    std::cout << "  Timer PRESCALE set (write)." << std::endl;

    // Read the current count value
    // volatile ensures this reads the actual hardware register value *now*.
    uint32_t current_count = TIMER1->COUNT;
    std::cout << "  Timer COUNT read: " << current_count << std::endl;

    // Read status register (could clear flags as a side effect)
    uint32_t status_flags = TIMER1->STATUS;
    std::cout << "  Timer STATUS read: 0x" << std::hex << status_flags << std::dec << std::endl;
    // Maybe check specific flags: if (status_flags & 0x01) { /* handle flag */ }

    // Writing again to potentially clear flags by reading previously
    // Or maybe just waiting for a change
    // uint32_t status_flags_after = TIMER1->STATUS;

    // ** SUMMARY **
    // - Use struct overlays for logical grouping and named access.
    // - Use constexpr for base addresses.
    // - Use reinterpret_cast to create the initial pointer.
    // - ALWAYS use 'volatile' for the members within the register struct.
}

// ==========================================================================
// Section 7: Debugging Techniques (Conceptual Comments)
// ==========================================================================
void debugging_concepts()
{
    std::cout << "\n--- Section 7: Debugging Techniques (Conceptual) ---" << std::endl;
    // Finding where a variable (e.g., a global `int g_counter = 0;`) gets corrupted:

    // 1. Logging/Printing:
    //    - Add print statements (std::cout, printf, or target-specific logging)
    //      before and after potential modification points.
    //      Example:
    //      std::cout << "Before funcA: g_counter = " << g_counter << std::endl;
    //      funcA();
    //      std::cout << "After funcA: g_counter = " << g_counter << std::endl;
    //    - Helps narrow down *when* the change occurs.
    //    - Can be intrusive and slow down execution.

    // 2. Breakpoints (using a debugger like GDB, LLDB, VS Code Debugger):
    //    - Set breakpoints on lines of code *before* suspected corruption points.
    //    - When the program stops (hits a breakpoint), inspect the variable's value.
    //    - Step through code (Step Over, Step Into, Step Out) line by line,
    //      watching the variable's value change in the debugger's watch window.
    //    - Helps understand the execution flow leading to the change.

    // 3. Watchpoints / Data Breakpoints (Most effective for this specific problem):
    //    - Tell the debugger to monitor a specific memory address (the address of `g_counter`).
    //    - Command example (GDB): `watch g_counter` or `watch *(address_of_g_counter)`
    //    - The debugger will automatically stop execution *exactly* on the line of code
    //      that *writes* to that memory location, immediately identifying the culprit.
    //    - Extremely powerful for tracking down unexpected modifications.

    // 4. Code Review / Searching:
    //    - Use IDE search or command-line tools (grep) to find all occurrences
    //      of the variable name.
    //    - Manually review each instance, looking for assignments (`=`), increments (`++`),
    //      decrements (`--`), or passing by non-const reference/pointer to functions.
    //    - Can be time-consuming but necessary sometimes.

    // 5. Version Control (e.g., `git bisect`):
    //    - If the bug is recent, use `git bisect` to efficiently find the specific
    //      commit that introduced the problem.
    //    - Helps narrow the search space to recent code changes.

    std::cout << "(See comments in the code for debugging technique descriptions)" << std::endl;
}

// ==========================================================================
// Main Function - Calls examples
// ==========================================================================
int main()
{
    manual_memory_management_examples();
    operator_precedence_examples();
    range_based_for_examples();
    smart_pointer_examples();
    constant_examples();
    hardware_interaction_examples();
    debugging_concepts();

    std::cout << "\n--- Example Execution Complete ---" << std::endl;
    return 0;
}