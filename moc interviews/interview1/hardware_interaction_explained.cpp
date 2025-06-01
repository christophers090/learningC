// ==========================================================================
// hardware_interaction_explained.cpp - Deeper Dive into Section 6 Concepts
// ==========================================================================

#include <iostream>
#include <cstdint> // For uint32_t, uintptr_t

//---------------------------------------------------------------------------
// Concept 1: Memory-Mapped I/O (The Big Picture)
//---------------------------------------------------------------------------
// - Microcontrollers (like ARM Cortex-M) don't have separate "I/O ports"
//   like older architectures (e.g., x86 IN/OUT instructions).
// - Instead, the hardware peripherals (Timers, GPIO, UART, SPI, I2C, etc.)
//   are controlled by writing to and reading from specific memory addresses.
// - These addresses are part of the microcontroller's overall memory map,
//   just like RAM or Flash memory, but accessing them talks to hardware logic.
// - The datasheet for the microcontroller defines exactly which addresses
//   correspond to which peripheral and which specific control/status register.

//---------------------------------------------------------------------------
// Concept 2: Problems with Raw Addresses ("Magic Numbers")
//---------------------------------------------------------------------------
// BAD PRACTICE: Directly using a raw number in code.
// void set_gpio_pin_bad() {
//     // What is 0x40020014? Which pin? Which port? Hard to read!
//     // If this address changes (e.g., different chip), you must find all instances.
//     // Very error-prone.
//     *(unsigned int*)0x40020014 = 1;
// }

//---------------------------------------------------------------------------
// Concept 3: Defining Addresses Symbolically (using constexpr)
//---------------------------------------------------------------------------
// SOLUTION: Give addresses meaningful names using compile-time constants.

// Why `uintptr_t`?
// It's an unsigned integer type guaranteed to be large enough to hold a
// memory address (pointer) converted to an integer. This avoids potential
// compiler warnings or issues when storing addresses as plain `int` or `long`.

// `constexpr` ensures the value is known at compile time.
constexpr uintptr_t GPIOA_BASE_ADDRESS = 0x40020000;                               // Base address for GPIO Port A
constexpr uintptr_t GPIOA_ODR_OFFSET = 0x14;                                       // Offset for Output Data Register
constexpr uintptr_t GPIOA_OUTPUT_DATA_REG = GPIOA_BASE_ADDRESS + GPIOA_ODR_OFFSET; // Calculate specific register

// Better, but still requires manual casting and lacks grouping.
void set_gpio_pin_better_but_incomplete()
{
    std::cout << "\n--- Symbolic Address Example ---" << std::endl;
    std::cout << "GPIOA ODR Address: 0x" << std::hex << GPIOA_OUTPUT_DATA_REG << std::dec << std::endl;

    // Accessing still needs casting (and volatile - see next section)
    // *(uint32_t*)GPIOA_OUTPUT_DATA_REG = 1; // Conceptual access
    std::cout << "(Conceptual access using symbolic address)" << std::endl;
}

//---------------------------------------------------------------------------
// Concept 4: The `volatile` Keyword
//---------------------------------------------------------------------------
// PROBLEM: The Compiler Likes to Optimize!
// - Compilers are smart. If they see you write to a memory location but
//   never read it back, they might optimize away the write.
// - If they see you read the same memory location twice without any intervening
//   write *in your C++ code*, they might reuse the value from the first read,
//   assuming it hasn't changed.

// WHY THIS IS BAD FOR HARDWARE REGISTERS:
// 1. Registers Change Externally: A hardware timer's counter register increments
//    on its own. An input data register changes when an external signal changes.
//    The compiler doesn't know this! Reading twice might be necessary to see updates.
// 2. Side Effects: Reading or writing certain registers *causes* something to happen
//    in the hardware (e.g., reading a UART status register might clear the
//    "data ready" flag). These reads/writes MUST occur exactly as written.

// SOLUTION: `volatile`
// - `volatile` tells the compiler: "Warning! This memory location can change
//   at any time for reasons outside the C++ code's direct control, OR accessing
//   it might have side effects."
// - It FORCES the compiler to:
//    a) Perform every single read from the volatile location exactly as coded.
//    b) Perform every single write to the volatile location exactly as coded.
//    c) Not reorder volatile accesses relative to other volatile accesses.
// - It essentially disables certain optimizations for accesses to that specific memory.

// Example of declaring a pointer to a volatile location:
volatile uint32_t *const uart_status_reg = reinterpret_cast<volatile uint32_t *>(0x40011000); // Example UART SR addr

void volatile_example()
{
    std::cout << "\n--- Volatile Example ---" << std::endl;
    std::cout << "UART Status Reg Address: 0x" << std::hex << reinterpret_cast<uintptr_t>(uart_status_reg) << std::dec << std::endl;

    // Conceptual example of reading a status register
    // uint32_t status = *uart_status_reg; // Read 1 - volatile forces actual hardware read
    // std::cout << "(Read UART status 1)" << std::endl;
    // // ... potentially do something else ...
    // uint32_t status2 = *uart_status_reg; // Read 2 - volatile forces ANOTHER hardware read
    // std::cout << "(Read UART status 2 - may differ from read 1 due to hardware)" << std::endl;
    // // If uart_status_reg was NOT volatile, compiler might optimize this to:
    // // uint32_t status = *uart_status_reg;
    // // uint32_t status2 = status; // <--- Incorrect reuse of value!

    std::cout << "(Conceptual reads using volatile pointer)" << std::endl;
}

//---------------------------------------------------------------------------
// Concept 5: Struct Overlays for Register Blocks
//---------------------------------------------------------------------------
// PROBLEM: Peripherals often have many registers grouped together starting
//          at a base address. Calculating offsets manually is tedious and
//          error-prone. Accessing individual registers by address isn't very readable.

// SOLUTION: Define a C++ `struct` whose members match the layout, names,
//           and sizes of the hardware registers.

// Example: Simplified GPIO Port Register Block
// (Layout based on a typical ARM Cortex-M microcontroller, e.g., STM32)
struct SimpleGpioRegs
{
    volatile uint32_t MODER;   // Mode Register (Offset 0x00)
    volatile uint32_t OTYPER;  // Output Type Register (Offset 0x04)
    volatile uint32_t OSPEEDR; // Output Speed Register (Offset 0x08)
    volatile uint32_t PUPDR;   // Pull-up/Pull-down Register (Offset 0x0C)
    volatile uint32_t IDR;     // Input Data Register (Offset 0x10) - Read Only usually
    volatile uint32_t ODR;     // Output Data Register (Offset 0x14)
    // ... other registers would follow (BSRR, LCKR, AFR etc.)
};
// IMPORTANT: The order, types, and padding (if needed) in the struct MUST
//            exactly match the hardware memory layout described in the datasheet.
//            All members representing hardware registers MUST be marked volatile.

void struct_overlay_example()
{
    std::cout << "\n--- Struct Overlay Example ---" << std::endl;

    // 1. Define the base address (as before)
    constexpr uintptr_t GPIOA_BASE = 0x40020000;

    // 2. Create a pointer of the *struct type* pointing to that base address.
    //    `reinterpret_cast` is necessary to convert the raw address (integer)
    //    into a pointer to our specific struct type.
    SimpleGpioRegs *const GPIOA = reinterpret_cast<SimpleGpioRegs *>(GPIOA_BASE);
    // Note: `GPIOA` itself is a `const` pointer - meaning the pointer `GPIOA` cannot
    // be made to point somewhere else. However, the data it *points to* (the registers)
    // is volatile and can be modified through the pointer.

    std::cout << "GPIOA struct mapped to Address: 0x" << std::hex << GPIOA_BASE << std::dec << std::endl;

    // 3. Access registers using meaningful names via the pointer and arrow operator `->`
    std::cout << "Accessing registers via struct overlay:" << std::endl;

    // Example: Configure Pin 0 as Output
    // Read-modify-write: Clear bits 1:0, then set bit 0 to 1 (binary 01 = Output)
    GPIOA->MODER = (GPIOA->MODER & ~(0x3 << (0 * 2))) | (0x01 << (0 * 2));

    std::cout << "  (Conceptual write to GPIOA->MODER)" << std::endl;

    // Example: Set Pin 0 High
    // GPIOA->ODR |= (1 << 0); // Set bit 0 in Output Data Register
    // std::cout << "  (Conceptual write to GPIOA->ODR)" << std::endl;

    // Example: Read Input Data Register
    // uint32_t inputs = GPIOA->IDR; // Read all input pin states
    // std::cout << "  (Conceptual read from GPIOA->IDR)" << std::endl;

    std::cout << "  (Conceptual register access using struct pointer)" << std::endl;

    // BENEFITS:
    // - Readability: `GPIOA->ODR` is much clearer than `*(volatile uint32_t*)0x40020014`.
    // - Maintainability: Register offsets are handled by the struct layout.
    // - Reduced Errors: Less chance of typos in addresses or offsets.
    // - Grouping: Related registers are logically grouped.
}

// ==========================================================================
// Main Function
// ==========================================================================
int main()
{
    std::cout << "====== Hardware Interaction Explained ======" << std::endl;

    // Demonstrate concepts (conceptual access, addresses printed)
    set_gpio_pin_better_but_incomplete();
    volatile_example();
    struct_overlay_example();

    std::cout << "\n====== End of Explanations ======" << std::endl;
    return 0;
}