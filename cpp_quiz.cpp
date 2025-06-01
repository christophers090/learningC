// ==========================================================================
// C++ Quiz for Embedded Systems Roles
// ==========================================================================

// --- Instructions ---
// - Answer conceptual questions in comments below the question (`// ANSWER:`).
// - For implementation questions, write C++ code directly in the designated area.
// - Assume C++11 or later. Include necessary headers.

#include <iostream>  // For basic I/O if needed for testing
#include <vector>    // For STL examples
#include <map>       // For STL examples
#include <string>    // For std::string
#include <memory>    // For smart pointers
#include <cstdint>   // For fixed-width integers
#include <mutex>     // For concurrency example (concept)
#include <atomic>    // For concurrency example (concept)
#include <optional>  // For modern C++ example
#include <stdexcept> // For exceptions

// ==========================================================================
// Section A: Memory Management & RAII
// ==========================================================================

// --- Question A1 (Concept) ---
// Explain the RAII (Resource Acquisition Is Initialization) principle in C++.
// How do `std::unique_ptr` and `std::shared_ptr` embody this principle?
// Contrast this with manual memory management using `new`/`delete` in terms
// of safety and exception handling.
// ANSWER A1:
//

// --- Question A2 (Implementation - Open Ended) ---
// Design and implement a C++ class `SerialPortManager` that safely manages
// a hypothetical OS resource handle (e.g., represented as an `int` file descriptor
// or a `void*` handle). Use RAII principles.
// Requirements:
// - Constructor takes port identifier (e.g., `const std::string&`), attempts to acquire the resource
//   (simulate with a function call or direct assignment). Throw an exception on failure.
// - Destructor automatically releases the resource (if acquired).
// - Ensure the class correctly handles copy and move semantics (prevent copying, allow moving)
//   to maintain clear resource ownership.
// - Provide a method to check if the resource handle is valid.
// - Provide a method to get the underlying handle (for use with C APIs).
// CODE A2:

class SerialPortManager
{
public:
    SerialPortManager(const std::string &portID) : _portID(portID)
    {
        if (portID == "firstPort")
        {
            // try
            // {
            //      data = getData1();
            // }
            // catch(const std::exception& e)
            // {
            //     std::cerr << e.what() << '\n';
            // }
        }
        // ect
        _data = 1;
    }

private:
    std::string _portID;
    int _data;
};

// --- Question A3 (Concept) ---
// What is the "Rule of Zero/Three/Five" in C++? Explain why the move constructor
// and move assignment operator were added in C++11 and how they improve efficiency
// and resource management, especially with classes like `std::unique_ptr` and `std::vector`.
// ANSWER A3:
//

// --- Question A4 (Concept) ---
// Explain the potential danger of using `std::shared_ptr` in data structures with
// cyclic references (e.g., two objects pointing to each other). What C++ smart
// pointer class is typically used to break such ownership cycles? Briefly explain how it works.
// ANSWER A4:
//

// --- Question A5 (Implementation - Open Ended) ---
// Consider a function that reads configuration data from a file into a dynamically allocated buffer.
// Outline the steps involved in implementing this function safely in C++ using RAII
// (e.g., smart pointers for the buffer) to ensure the buffer is always deallocated,
// even if errors occur during file reading or parsing. You don't need to write the full
// file I/O, focus on the memory management aspect.
// PSEUDOCODE / IMPLEMENTATION OUTLINE A5:

// ==========================================================================
// Section B: Classes, Inheritance, and Polymorphism
// ==========================================================================

// --- Question B1 (Concept) ---
// Explain the difference between `struct` and `class` in C++. What are the defaults
// for member access and inheritance? When might you stylistically prefer one over the other?
// ANSWER B1:
//

// --- Question B2 (Concept) ---
// What is the purpose of a `virtual` destructor in a C++ base class?
// Describe a specific problem (e.g., slicing, incomplete cleanup, memory leak)
// that can occur if a base class destructor is *not* virtual when dealing with
// polymorphism and deleting derived objects via base class pointers.
// ANSWER B2:
//

// --- Question B3 (Implementation - Open Ended) ---
// Design and implement a simple C++ class hierarchy for communication interfaces.
// Requirements:
// - An abstract base class `CommunicationInterface` with:
//   - Pure virtual functions: `virtual bool open() = 0;`, `virtual void close() = 0;`,
//     `virtual bool send(const uint8_t* data, size_t length) = 0;`,
//     `virtual int receive(uint8_t* buffer, size_t buffer_size) = 0;` (returns bytes read or -1 on error).
//   - A virtual destructor.
//   - Consider any common data members (protected?) or non-virtual helper functions.
// - A derived class `UartInterface` inheriting from `CommunicationInterface`.
//   - Provide basic implementations (can just print messages or return dummy values) for the virtual functions.
//   - Add members specific to UART (e.g., baud rate, port name).
//   - Implement the constructor.
// - A derived class `SpiInterface` inheriting from `CommunicationInterface`.
//   - Provide basic implementations for the virtual functions.
//   - Add members specific to SPI (e.g., clock speed, chip select ID).
//   - Implement the constructor.
// CODE B3:

// --- Question B4 (Concept) ---
// What do the `override` and `final` keywords signify when used with virtual functions
// in derived classes? What are the benefits of using them in terms of code correctness
// and maintainability?
// ANSWER B4:
//

// --- Question B5 (Concept) ---
// Explain `const`-correctness in C++. Why is it important to mark member functions
// as `const`? How does the compiler enforce it (what happens to the `this` pointer)?
// What is the difference between `const T*`, `T* const`, and `const T* const` for member variables?
// ANSWER B5:
//

// --- Question B6 (Implementation - Open Ended) ---
// Given the `CommunicationInterface` hierarchy from Q B3, write a function
// `void test_interface(CommunicationInterface& interface)` that takes a reference
// to any interface object, attempts to open it, send some dummy data, receive
// (into a small buffer), and then close it. Demonstrate polymorphism.
// CODE B6:

// ==========================================================================
// Section C: STL, Concurrency, and Modern C++
// ==========================================================================

// --- Question C1 (Concept) ---
// Compare `std::vector` and `std::list`. Discuss their internal memory layout
// and the performance implications (Big O notation if possible) for:
//   a) Accessing an element by index (e.g., `vec[i]`)
//   b) Inserting/deleting an element at the beginning or end.
//   c) Inserting/deleting an element in the middle.
//   d) Cache locality.
// ANSWER C1:
// a)
// b)
// c)
// d)

// --- Question C2 (Concept) ---
// Explain the difference between `std::vector::push_back(value)` and
// `std::vector::emplace_back(args...)`. Provide an example scenario where
// `emplace_back` offers a significant performance advantage.
// ANSWER C2:
//

// --- Question C3 (Concept) ---
// Explain the difference between accessing elements in a `std::map<K, V>` using
// `operator[]` versus the `.at()` method. What happens in each case if the key
// does not exist? Which method should you use if you *only* want to check for
// existence or read an existing value without potentially inserting a new one?
// ANSWER C3:
//

// --- Question C4 (Concept) ---
// What is a data race in C++? Briefly describe how `std::mutex` paired with
// `std::lock_guard` or `std::scoped_lock` helps prevent them.
// What is the purpose of `std::atomic` types? How do they provide thread safety
// for simple operations without explicit locking?
// ANSWER C4:
//

// --- Question C5 (Implementation) ---
// Write a simple C++ function template `template<typename Container>`
// `void print_container(const Container& c)` that iterates through any STL-like
// container (supporting range-based for loops or begin/end iterators) and prints
// its elements to `std::cout`, separated by spaces.
// CODE C5:

// --- Question C6 (Concept) ---
// Compare `#define`, `const`, and `constexpr` for defining constants in C++.
// Discuss type safety, scope, and evaluation time (compile time vs. runtime).
// When is `constexpr` particularly useful in embedded or performance-critical code?
// ANSWER C6:
//

// --- Question C7 (Concept) ---
// What is `std::optional<T>` used for? How does it improve upon C-style approaches
// like using `nullptr` for pointers, special return codes, or output parameters
// to indicate the potential absence of a value?
// ANSWER C7:
//

// --- Question C8 (Implementation / Concept - Open Ended) ---
// Consider accessing a memory-mapped hardware register (e.g., a 32-bit control register
// at address `0x40010004`) in C++.
// Design a C++ approach that improves upon simple C-style `#define` macros.
// Consider using:
//  - `constexpr` for the address.
//  - `volatile` keyword (where and why?).
//  - Potentially a lightweight struct or class wrapper.
//  - Bitmask handling (e.g., using `enum class` for flags or `std::bitset` if appropriate).
// Discuss the advantages of your C++ approach in terms of type safety, readability, and maintainability.
// CODE/DESIGN C8:

// ==========================================================================
// End of Quiz
// ==========================================================================

// --- Main Function (Optional - for testing your implementations) ---
// int main() {
//     // You can add code here to test your implementation functions
//     std::cout << "Starting C++ Quiz Tests (Optional)...\n";
//
//     std::cout << "C++ Quiz Tests Complete.\n";
//     return 0;
// }