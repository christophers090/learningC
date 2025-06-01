// ==========================================================================
// bitwise_operations_tutorial.cpp - Understanding Bit Manipulation in C++
// ==========================================================================

#include <iostream>
#include <cstdint> // For fixed-width types like uint8_t
#include <iomanip> // For std::setw, std::setfill
#include <bitset>  // For easy binary printing

// Helper function to print binary representation clearly
void printBits(uint8_t value, const std::string &label = "")
{
    if (!label.empty())
    {
        std::cout << std::setw(15) << std::left << label << ": ";
    }
    std::cout << std::bitset<8>(value)
              << " (Decimal: " << static_cast<int>(value)
              << ", Hex: 0x" << std::hex << static_cast<int>(value) << std::dec << ")"
              << std::endl;
}

int main()
{
    std::cout << "====== Bitwise Operations Tutorial ======" << std::endl;

    // --- Concept 1: Binary Representation ---
    std::cout << "\n--- Concept 1: Binary Representation ---" << std::endl;
    // Computers store data using bits (binary digits), which are either 0 or 1.
    // Integer types (like int, uint8_t) are represented as a sequence of these bits.
    // For uint8_t (unsigned 8-bit integer), there are 8 bits.
    // Each bit position has a place value (a power of 2):
    // Bit Position:  7   6   5   4   3   2   1   0
    // Place Value: 128  64  32  16   8   4   2   1

    uint8_t num1 = 85; // Example value
    // Binary of 85: 0*128 + 1*64 + 0*32 + 1*16 + 0*8 + 1*4 + 0*2 + 1*1 = 64 + 16 + 4 + 1 = 85
    // Binary representation: 01010101
    printBits(num1, "num1 (85)");

    uint8_t num2 = 0b00110011;       // Using 0b prefix for binary literal (C++14)
    printBits(num2, "num2 (0b...)"); // Decimal 51

    uint8_t num3 = 0xF0; // Using 0x prefix for hexadecimal literal
    // Hex F = Binary 1111, Hex 0 = Binary 0000
    // So 0xF0 = 11110000
    printBits(num3, "num3 (0xF0)"); // Decimal 240

    // --- Concept 2: Bitwise Operators ---
    std::cout << "\n--- Concept 2: Bitwise Operators ---" << std::endl;
    // These operators work directly on the individual bits of their operands.

    uint8_t a = 0b01010101; // 85
    uint8_t b = 0b00110011; // 51
    printBits(a, "a");
    printBits(b, "b");

    // 1. Bitwise AND (&)
    //    Result bit is 1 only if *both* corresponding input bits are 1.
    //    Truth Table: 0&0=0, 0&1=0, 1&0=0, 1&1=1
    //      01010101 (a)
    //    & 00110011 (b)
    //    ----------
    //      00010001 (result)
    printBits(a & b, "a & b"); // Decimal 17
    //    *Use Case: Often used for masking - checking or clearing specific bits.*

    // 2. Bitwise OR (|)
    //    Result bit is 1 if *either* (or both) corresponding input bits are 1.
    //    Truth Table: 0|0=0, 0|1=1, 1|0=1, 1|1=1
    //      01010101 (a)
    //    | 00110011 (b)
    //    ----------
    //      01110111 (result)
    printBits(a | b, "a | b"); // Decimal 119
    //    *Use Case: Often used for setting specific bits.*

    // 3. Bitwise XOR (^)
    //    Result bit is 1 if the corresponding input bits are *different*.
    //    Truth Table: 0^0=0, 0^1=1, 1^0=1, 1^1=0
    //      01010101 (a)
    //    ^ 00110011 (b)
    //    ----------
    //      01100110 (result)
    printBits(a ^ b, "a ^ b"); // Decimal 102
    //    *Use Case: Often used for toggling specific bits.*

    // 4. Bitwise NOT (~)
    //    Inverts all bits of its *single* operand (0 becomes 1, 1 becomes 0).
    //    Also known as the bitwise complement operator.
    //      01010101 (a)
    //    ----------
    //    ~ 10101010 (result)
    printBits(~a, "~a"); // Decimal 170
    //    *Use Case: Often used in combination with & to create masks for clearing bits.*

    // 5. Left Shift (<<)
    //    Shifts all bits of the left operand to the *left* by the number of positions
    //    specified by the right operand. Fills vacated bits on the right with 0s.
    //    Bits shifted off the left end are discarded.
    //    Equivalent to multiplying by 2 for each shift position (if no overflow).
    //      00110011 (b = 51)
    //    << 1 (shift left by 1)
    //    ----------
    //      01100110 (result = 102)
    printBits(b << 1, "b << 1");
    //      00110011 (b = 51)
    //    << 3 (shift left by 3)
    //    ----------
    //      10011000 (result = 152)
    printBits(b << 3, "b << 3");
    //    *Use Case: Creating bit masks, multiplying by powers of 2.*

    // 6. Right Shift (>>)
    //    Shifts all bits of the left operand to the *right* by the number of positions
    //    specified by the right operand. Bits shifted off the right end are discarded.
    //    For *unsigned* types (like uint8_t), vacated bits on the left are filled with 0s (logical shift).
    //    (For signed types, the behavior can be implementation-defined - arithmetic or logical shift).
    //    Equivalent to integer division by 2 for each shift position.
    //      01010101 (a = 85)
    //    >> 1 (shift right by 1)
    //    ----------
    //      00101010 (result = 42)
    printBits(a >> 1, "a >> 1");
    //      01010101 (a = 85)
    //    >> 2 (shift right by 2)
    //    ----------
    //      00010101 (result = 21)
    printBits(a >> 2, "a >> 2");
    //    *Use Case: Dividing by powers of 2, isolating specific bits.*

    // --- Concept 3: Common Bit Manipulation Tasks ---
    std::cout << "\n--- Concept 3: Common Bit Manipulation Tasks ---" << std::endl;
    uint8_t data = 0b10010110; // Start value
    printBits(data, "Original Data");

    // Task 1: Check if a specific bit is set (e.g., bit 4)
    // Strategy: Use bitwise AND (&) with a 'mask'.
    //   - Create a mask with only the bit we care about set to 1.
    //   - Use left shift (<<) to create the mask: `1 << bitPosition`
    int bitPosToCheck = 4;
    uint8_t maskCheck = (1 << bitPosToCheck); // mask = 00010000
    printBits(maskCheck, "Check Mask (4)");
    //   - AND the data with the mask.
    //       10010110 (data)
    //     & 00010000 (maskCheck)
    //     ----------
    //       00010000 (result)
    //   - If the result is non-zero, the bit was set.
    bool isSet = (data & maskCheck) != 0;
    // Alternatively: bool isSet = (data & (1 << bitPosToCheck));
    std::cout << "Is bit " << bitPosToCheck << " set? " << std::boolalpha << isSet << std::endl;

    bitPosToCheck = 2;
    maskCheck = (1 << bitPosToCheck); // mask = 00000100
    printBits(maskCheck, "Check Mask (2)");
    //       10010110 (data)
    //     & 00000100 (maskCheck)
    //     ----------
    //       00000100 (result)
    isSet = (data & maskCheck) != 0;
    std::cout << "Is bit " << bitPosToCheck << " set? " << std::boolalpha << isSet << std::endl;

    bitPosToCheck = 3;
    maskCheck = (1 << bitPosToCheck); // mask = 00001000
    printBits(maskCheck, "Check Mask (3)");
    //       10010110 (data)
    //     & 00001000 (maskCheck)
    //     ----------
    //       00000000 (result)
    isSet = (data & maskCheck) != 0;
    std::cout << "Is bit " << bitPosToCheck << " set? " << std::boolalpha << isSet << std::endl;

    // Task 2: Set a specific bit (e.g., bit 3)
    // Strategy: Use bitwise OR (|) with a mask.
    //   - Create the mask with only the target bit set (1 << bitPosition).
    int bitPosToSet = 3;
    uint8_t maskSet = (1 << bitPosToSet); // mask = 00001000
    printBits(maskSet, "Set Mask (3)");
    //   - OR the data with the mask. This forces the target bit to 1, leaves others unchanged.
    //       10010110 (data)
    //     | 00001000 (maskSet)
    //     ----------
    //       10011110 (result)
    data = data | maskSet;
    // Shorthand: data |= maskSet; or data |= (1 << bitPosToSet);
    printBits(data, "Data after set 3");

    // Task 3: Clear a specific bit (e.g., bit 1)
    // Strategy: Use bitwise AND (&) with an *inverted* mask.
    //   - Create a mask with only the target bit set (1 << bitPosition).
    int bitPosToClear = 1;
    uint8_t maskClearTarget = (1 << bitPosToClear); // mask = 00000010
    printBits(maskClearTarget, "Clear Tgt Mask(1)");
    //   - Invert the mask using bitwise NOT (~).
    uint8_t maskClear = ~maskClearTarget; // mask = 11111101
    printBits(maskClear, "Clear Mask (1)");
    //   - AND the data with the inverted mask. This forces the target bit to 0, leaves others unchanged.
    //       10011110 (data)
    //     & 11111101 (maskClear)
    //     ----------
    //       10011100 (result)
    data = data & maskClear;
    // Shorthand: data &= maskClear; or data &= ~(1 << bitPosToClear);
    printBits(data, "Data after clear 1");

    // Task 4: Toggle a specific bit (e.g., bit 7)
    // Strategy: Use bitwise XOR (^) with a mask.
    //   - Create the mask with only the target bit set (1 << bitPosition).
    int bitPosToToggle = 7;
    uint8_t maskToggle = (1 << bitPosToToggle); // mask = 10000000
    printBits(maskToggle, "Toggle Mask (7)");
    //   - XOR the data with the mask. If the data bit was 0, 0^1=1. If it was 1, 1^1=0.
    //       10011100 (data)
    //     ^ 10000000 (maskToggle)
    //     ----------
    //       00011100 (result)
    data = data ^ maskToggle;
    // Shorthand: data ^= maskToggle; or data ^= (1 << bitPosToToggle);
    printBits(data, "Data after toggle 7");

    // --- Concept 4: Applying to the Interview Question ---
    std::cout << "\n--- Concept 4: Applying to Interview Question ---" << std::endl;
    // Now you have the building blocks:
    // bool isBitSet(uint8_t data, int bitPosition) {
    //     return (data & (1 << bitPosition)) != 0;
    // }
    // void setBit(uint8_t& data, int bitPosition) {
    //     data |= (1 << bitPosition);
    // }
    // void clearBit(uint8_t& data, int bitPosition) {
    //     data &= ~(1 << bitPosition);
    // }
    std::cout << "(See comments for function implementations)" << std::endl;

    std::cout << "\n====== Tutorial Complete ======" << std::endl;
    return 0;
}