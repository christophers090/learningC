#include <cstdint>  // For uint8_t
#include <iostream> // For testing output
#include <iomanip>  // For std::setw

// Assume bitPosition is always valid (0-7 for uint8_t)

/**
 * @brief Sets the specified bit in the data byte to 1.
 *
 * @param data Reference to the byte to modify.
 * @param bitPosition The position of the bit to set (0-7).
 */

void setBit(uint8_t &data, int pos)
{
    data |= (1 << pos);
}

/**
 * @brief Clears the specified bit in the data byte to 0.
 *
 * @param data Reference to the byte to modify.
 * @param bitPosition The position of the bit to clear (0-7).
 */

void clearBit(uint8_t &data, int pos)
{
    data &= ~(1 << pos);
}

/**
 * @brief Checks if the specified bit in the data byte is set (1).
 *
 * @param data The byte to check (passed by value).
 * @param bitPosition The position of the bit to check (0-7).
 * @return true if the bit is set, false otherwise.
 */

bool isBitSet(uint8_t &data, int pos)
{
    return (data & (1 << pos)) != 0;
}

void printBinary(uint8_t data)
{
    for (int i = 7; i >= 0; --i)
    {
        std::cout << ((data >> i) & 1);
    }
}

int main()
{
    std::cout << "--- Bit Manipulation Tests ---" << std::endl;

    uint8_t testData = 0b10101010; // Start with 170 (binary)

    std::cout << "Initial data: ";
    printBinary(testData);
    std::cout << " (0x" << std::hex << static_cast<int>(testData) << ")" << std::dec << std::endl;

    // Test isBitSet
    std::cout << "Bit 7 set? " << std::boolalpha << isBitSet(testData, 7) << " (Expected: true)" << std::endl;
    std::cout << "Bit 6 set? " << std::boolalpha << isBitSet(testData, 6) << " (Expected: false)" << std::endl;
    std::cout << "Bit 1 set? " << std::boolalpha << isBitSet(testData, 1) << " (Expected: true)" << std::endl;
    std::cout << "Bit 0 set? " << std::boolalpha << isBitSet(testData, 0) << " (Expected: false)" << std::endl;

    // Test setBit
    std::cout << "Setting bit 6..." << std::endl;
    setBit(testData, 6);
    std::cout << "Result:       ";
    printBinary(testData);
    std::cout << " (Expected: 11101010)" << std::endl;
    std::cout << "Setting bit 0..." << std::endl;
    setBit(testData, 0);
    std::cout << "Result:       ";
    printBinary(testData);
    std::cout << " (Expected: 11101011)" << std::endl;
    std::cout << "Setting bit 7 (already set)..." << std::endl;
    setBit(testData, 7);
    std::cout << "Result:       ";
    printBinary(testData);
    std::cout << " (Expected: 11101011)" << std::endl;

    // Test clearBit
    std::cout << "Clearing bit 1..." << std::endl;
    clearBit(testData, 1);
    std::cout << "Result:       ";
    printBinary(testData);
    std::cout << " (Expected: 11101001)" << std::endl;
    std::cout << "Clearing bit 7..." << std::endl;
    clearBit(testData, 7);
    std::cout << "Result:       ";
    printBinary(testData);
    std::cout << " (Expected: 01101001)" << std::endl;
    std::cout << "Clearing bit 6 (already clear)..." << std::endl;
    clearBit(testData, 6);
    std::cout << "Result:       ";
    printBinary(testData);
    std::cout << " (Expected: 01101001)" << std::endl;

    return 0;
}