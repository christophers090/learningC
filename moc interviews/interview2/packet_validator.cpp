#include <vector>
#include <cstdint>  // For uint8_t
#include <numeric>  // For std::accumulate (optional, but useful)
#include <iostream> // For main function testing output

/**
 * @brief Validates a simple data packet buffer.
 *
 * @param buffer The received data buffer.
 * @return true if the packet structure and checksum are valid, false otherwise.
 *
 * Packet Structure:
 * - Byte 0:      Start Byte (must be 0xAA)
 * - Byte 1:      Packet Type ID (any value)
 * - Byte 2:      Payload Size (N)
 * - Bytes 3..N+2: Payload Data (N bytes)
 * - Byte N+3:    Checksum (sum of bytes 0 to N+2, ignoring overflow)
 *
 *
 */
// TODO: Implement validation logic here
// Rule 1: Minimum Size check

// Rule 2: Start Byte check

// Rule 3: Packet Size check (using payloadSize byte)

// Rule 4: Checksum calculation and validation

bool validate(const std::vector<uint8_t> &packet)
{
    if (packet.size() < 4)
        return false;
    if (packet.at(0) != 0xAA)
        return false;

    int payloadSize = packet.size() - 4;
    if (payloadSize != packet.at(2))
        return false;

    uint8_t checksum = 0;
    for (size_t i = 0; i < packet.size() - 1; ++i)
    {
        checksum += packet[i];
    }
    if (checksum != packet.back())
        return false;

    return true;
}

void testPacket(const std::vector<uint8_t> &packet, bool expected)
{
    std::cout << "Expected: " << expected << std::endl;
    bool result = validate(packet);
    std::cout << "Actual: " << result << std::endl;
}

int main()
{

    std::cout << "Testing packets";

    testPacket({0xAA, 0x01, 0x02, 0x10, 0x20, 0xDB}, true); // Valid: 0xAA+1+2+0x10+0x20 = 0xDD (Checksum wraps around to 0xDB if needed)
    testPacket({0xAA, 0x02, 0x00, 0xAC}, true);             // Valid: 0xAA+2+0 = 0xAC (No payload)
    testPacket({0xAA, 0xFF, 0x01, 0x55, 0x9F}, true);       // Valid: 0xAA+0xFF+1+0x55 = 0x1FF -> 0xFF, checksum is 0x9F if checksum calculation wraps

    testPacket({}, false);                                   // FAILED: Too small
    testPacket({0xAA, 0x01, 0x00}, false);                   // FAILED: Too small (Min size 4)
    testPacket({0xBB, 0x01, 0x00, 0xBC}, false);             // FAILED: Wrong start byte
    testPacket({0xAA, 0x01, 0x02, 0x10, 0x20}, false);       // FAILED: Size mismatch (payloadSize=2, need 6 bytes total, got 5)
    testPacket({0xAA, 0x01, 0x01, 0x10, 0xBC}, false);       // FAILED: Wrong checksum (0xAA+1+1+0x10 = 0xBC, checksum is BC)
    testPacket({0xAA, 0x01, 0x02, 0x10, 0x20, 0xDD}, false); // FAILED: Wrong checksum (sum = 0xDB, checksum = 0xDD)

    return 0;
}
