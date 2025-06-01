// ==========================================================================
// embedded_concepts_quiz.cpp - C++ Concepts Quiz for Embedded Roles
// ==========================================================================

#include <iostream>
#include <vector>
#include <memory>  // For smart pointers
#include <cstdint> // For fixed-width integers

// --- Instructions ---
// - Answer the questions in comments below them.
// - For code snippets, fix the // FIX ME lines or fill in the // TODO sections.

// ==========================================================================
// Section 1: Const Correctness & OOP Review
// ==========================================================================

class Sensor
{
    double lastReading_;
    uint32_t readingsCount_;

public:
    Sensor() : lastReading_(0.0), readingsCount_(0) {}

    void recordReading(double reading)
    {
        lastReading_ = reading;
        readingsCount_++;
    }

    // Q1: Why should the following getter function be marked 'const'?
    // Explain the benefit in the context of const-correctness.

    // A: it isnt modifying the class data
    double getLastReading() const
    {
        return lastReading_;
    }

    // Q2: Explain why this function CANNOT be marked 'const'.

    // A: it does edit the underlying data
    uint32_t getAndResetCount()
    {
        uint32_t count = readingsCount_;
        readingsCount_ = 0; // Modifies member variable
        return count;
    }
};

void processSensor(const Sensor &s)
{
    // Q3: If Sensor::getLastReading() was *not* marked const,
    //     would the following line compile? Why or why not?

    // A: it would not, this is because the sensor prop is passed in with the const keyword meaning this function
    // A: promises not to modify the obj, hense only const methods can be called.
    double reading = s.getLastReading();
    std::cout << "Processing reading: " << reading << std::endl;
}

// ==========================================================================
// Section 2: Memory Management (Manual & Smart Pointers)
// ==========================================================================

struct DeviceConfig
{
    int id;
    uint32_t configFlags;
    // Add constructor to allow make_unique with arguments
    DeviceConfig(int i, uint32_t f) : id(i), configFlags(f)
    {
        std::cout << "  DeviceConfig(" << id << ", " << configFlags << ") Constructed.\n";
    }
    // ~DeviceConfig() { std::cout << "DeviceConfig Destructor\n"; } // Assume simple destructor
};

void memory_management_questions()
{
    // Q4: The following code allocates an array. What is wrong with the deallocation?
    //     How should it be fixed?
    {
        std::cout << "\nQ4 Example:\n";
        // DeviceConfig *configArray = new DeviceConfig[5]; // This would require a default constructor
        // For this example, let's assume allocation happened, focus is on delete[]
        DeviceConfig *configArray = reinterpret_cast<DeviceConfig *>(new char[5 * sizeof(DeviceConfig)]); // Simulate allocation without default ctor call
        std::cout << "  (Simulated array allocation done)\n";
        // ... imagine using the array ...
        std::cout << "  Cleaning up configArray...\n";
        // delete configArray; // FIX ME: Incorrect deallocation
        delete[] reinterpret_cast<char *>(configArray); // CORRECT WAY: Must match allocation type (or use delete[] if new Type[] was used)
        std::cout << "  (Conceptual cleanup done)\n";
    }

    // Q5: Briefly explain the concept of RAII (Resource Acquisition Is Initialization)
    //     and how smart pointers like std::unique_ptr utilize it.
    // ANSWER Q5:
    // RAII binds the lifetime of a resource (e.g., heap memory, file handle, lock)
    // to the lifetime of an object. Resource is Acquired in the object's constructor
    // (Initialization) and Released in the object's destructor. Smart pointers
    // acquire the raw pointer in their constructor and call delete/delete[] in their
    // destructor, automating cleanup when the smart pointer object goes out of scope.

    // Q6: You need to dynamically allocate a DeviceConfig object. Only one part
    //     of your system should be responsible for its lifetime. Which smart
    //     pointer (`std::unique_ptr` or `std::shared_ptr`) is more appropriate?
    //     Why?
    // ANSWER Q6: std::unique_ptr. It enforces exclusive ownership, matching the requirement
    //            that only one part is responsible. It's also more lightweight.

    // Q7: Fill in the // TODO lines to correctly create and use a unique_ptr
    //     for a single DeviceConfig object.
    {
        std::cout << "\nQ7 Example (unique_ptr):\n";
        // Initialize directly using std::make_unique
        // Arguments are forwarded to the DeviceConfig constructor
        std::unique_ptr<DeviceConfig> configPtr = std::make_unique<DeviceConfig>(101, 0xFF);

        if (configPtr) // Check if pointer is valid (not null)
        {
            // Access members using ->
            std::cout << "  Smart Ptr Config ID: " << configPtr->id << std::endl;
            std::cout << "  Smart Ptr Config Flags: 0x" << std::hex << configPtr->configFlags << std::dec << std::endl;
        }
        std::cout << "  unique_ptr going out of scope...\n";
        // TODO: What happens automatically when configPtr goes out of scope here?
        //       (No code needed, just understand the concept)
        // A: The unique_ptr's destructor is called, which in turn calls 'delete'
        //    on the managed DeviceConfig object, freeing the memory.
    }

    // --- Raw pointer comparison ---
    DeviceConfig *rawConfigPtr = nullptr; // Declare raw pointer, initialize to null
    {
        std::cout << "\nRaw Pointer Example (Comparison to Q7):\n";
        try
        {
            // 1. Allocate using 'new'
            // Assumes DeviceConfig has a matching constructor
            rawConfigPtr = new DeviceConfig(202, 0xAA);

            if (rawConfigPtr)
            {
                // 2. Use the pointer
                std::cout << "  Raw Ptr Config ID: " << rawConfigPtr->id << std::endl;
                std::cout << "  Raw Ptr Config Flags: 0x" << std::hex << rawConfigPtr->configFlags << std::dec << std::endl;
            }
            // ... code where exceptions might occur ...

            // 3. *** Manually deallocate using 'delete' ***
            std::cout << "  Manually deleting rawConfigPtr...\n";
            delete rawConfigPtr;    // We MUST remember to do this!
            rawConfigPtr = nullptr; // Good practice to avoid dangling pointer
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Raw pointer allocation failed: " << e.what() << std::endl;
            rawConfigPtr = nullptr; // Ensure it's null on failure
        }
        // If an exception occurred before delete, or if delete was forgotten,
        // the memory allocated for DeviceConfig(202, 0xAA) would be leaked.
    }
    // rawConfigPtr is likely nullptr here (unless allocation failed early).
    // Using it without checking if it was successfully deleted would be unsafe.
}

// ==========================================================================
// Section 3: Hardware Interaction (volatile, struct overlays)
// ==========================================================================

// Hypothetical Timer Control Register Bits (for a 16-bit register)
// Bit 0: Timer Enable (TEN)
// Bit 1: Update Interrupt Enable (UIE)
// Bit 7: Auto-Reload Preload Enable (ARPE)
// Bits 8-9: Clock Division (CKD)

struct TimerControlRegs
{
    // Q8: This member represents a hardware register. What keyword is missing
    //     from its declaration, and why is that keyword crucial here?
    volatile uint16_t CR1; // Control Register 1
    volatile uint16_t SR;  // Status Register
    volatile uint16_t CNT; // Counter Register
    // ... other timer registers
};
// ANSWER Q8 (Why): To prevent the compiler from "optimizing" away the property that we want,
// the struct having the correct addresses offset from the base address

void hardware_interaction_questions()
{
    // Q9: Define a constexpr variable `TIMER2_BASE_ADDR` of type uintptr_t
    //     for a hypothetical Timer 2 peripheral located at memory address 0x40000400.
    // constexpr ??? TIMER2_BASE_ADDR = ??? ;

    constexpr uintptr_t TIMER2_BASE_ADDR = 0x40000400;

    // Q10: Using TIMER2_BASE_ADDR and reinterpret_cast, create a non-const pointer
    //      named `TIMER2` that points to the TimerControlRegs structure mapped
    //      at that base address. (The pointer itself shouldn't be const here).
    TimerControlRegs *TIMER2 = reinterpret_cast<TimerControlRegs *>(TIMER2_BASE_ADDR);

    // Q11: Assuming TIMER2 points correctly, write the C++ code to:
    //      a) Enable the timer (set bit 0 of CR1).
    //      b) Enable the update interrupt (set bit 1 of CR1).
    //      Use bitwise operators and the struct pointer access.
    if (TIMER2)
    { // Assume TIMER2 is valid
        TIMER2->CR1 |= (1);
        TIMER2->CR1 |= (1 << 1);
    }
}

// ==========================================================================
// Section 4: Bit Manipulation
// ==========================================================================

void bit_manipulation_questions()
{
    uint16_t configReg = 0b1010000011001100;

    // Q12: Write the C++ code to check if bit 15 is set in configReg.
    //      Store the result (true/false) in a bool variable `isBit15Set`.
    bool isBit15Set = (configReg & (1 << 15)) != 0;

    // Q13: Write the C++ code to clear bit 7 in configReg.
    configReg &= ~(1 << 7);

    // Q14: Write the C++ code to set bits 2 and 3 in configReg simultaneously.
    configReg |= ((1 >> 2) | (1 >> 3));

    // Q15: Write the C++ code to toggle bit 10 in configReg.
    configReg ^= (1 << 10);

    // Conceptual check (no need to print binary here)
    // std::cout << "Bit 15 Set: " << std::boolalpha << isBit15Set << std::endl;
    // std::cout << "Config after clear 7: 0x" << std::hex << configReg << std::endl;
    // std::cout << "Config after set 2&3: 0x" << std::hex << configReg << std::endl;
    // std::cout << "Config after toggle 10: 0x" << std::hex << configReg << std::endl;
}

// ==========================================================================
// Section 5: Concepts (Short Answer)
// ==========================================================================

// Q16: You are interfacing with a UART device. Both your microcontroller
//      and the external device must agree on the communication speed.
//      How is this typically achieved? Does UART have an auto-negotiation
//      mechanism like Ethernet?
// ANSWER Q16:
//

// Q17: A colleague suspects a global status variable is being modified
//      incorrectly somewhere in a large embedded codebase, causing intermittent
//      failures. If you have a debugger (like GDB), what specific debugging
//      feature would be most effective in stopping the program exactly when
//      that variable's memory is written to?
// ANSWER Q17:
//

// ==========================================================================
// Main Function (Optional Execution)
// ==========================================================================
int main()
{
    std::cout << "====== Embedded Concepts Quiz ======" << std::endl;

    // You can optionally call functions here to test snippets if needed,
    // but the primary goal is answering/fixing the code above.
    // memory_management_questions();
    // hardware_interaction_questions(); // Careful with actual hardware access!
    // bit_manipulation_questions();

    std::cout << "\n====== Quiz Setup Complete ======" << std::endl;
    return 0;
}