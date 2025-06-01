#ifndef COMMAND_PROTOCOL_H_
#define COMMAND_PROTOCOL_H_

#include <stdint.h>  // For fixed-width integers
#include <stdbool.h> // For bool type

// --- Constants ---
#define MAX_PAYLOAD_SIZE 16    // Maximum size of the command payload in bytes
#define PACKET_START_BYTE 0xAA // Defines the start of a command packet

// --- Command Types ---
// 'enum' creates a set of named integer constants.
// Good for representing a fixed set of states or types.
typedef enum
{
    CMD_UNKNOWN = 0,
    CMD_SET_RUDDER_ANGLE = 1,     // Command to set the rudder angle
    CMD_REQUEST_SENSOR_DATA = 2,  // Command to request current sensor data
    CMD_SET_OPERATIONAL_MODE = 3, // Command to set system operational mode (e.g., standby, active)
    // Add more commands as needed
} CommandType;

// --- Operational Modes (Example for CMD_SET_OPERATIONAL_MODE) ---
typedef enum
{
    MODE_STANDBY = 0,
    MODE_ACTIVE_FLIGHT = 1,
    MODE_DIAGNOSTIC = 2,
} OperationalMode;

// --- Command Packet Structure ---
// This struct represents the data that would be transmitted/received.
// In a real protocol, byte alignment and padding would be critical concerns (using __attribute__((packed)) or #pragma pack).
// For simplicity, we're not focusing heavily on that here but it's a key embedded topic.
typedef struct
{
    uint8_t start_byte;                // Should always be PACKET_START_BYTE
    uint8_t command_type;              // One of CommandType values
    uint8_t payload_length;            // Actual length of data in the payload array
    uint8_t payload[MAX_PAYLOAD_SIZE]; // Data specific to the command type
    uint8_t checksum;                  // Simple checksum for data integrity
} CommandPacket;

// --- Function Declarations ---

/**
 * @brief Calculates a simple XOR checksum for a block of data.
 * @param data Pointer to the data buffer.
 * @param length The number of bytes in the data buffer to checksum.
 * @return The calculated 8-bit checksum.
 */
uint8_t command_calculate_checksum(const uint8_t *data, uint8_t length);

/**
 * @brief Creates and serializes a CMD_SET_RUDDER_ANGLE command into a packet.
 * @param packet Pointer to the CommandPacket struct to be filled.
 * @param angle The target rudder angle (e.g., int8_t).
 * @return True if successful, false if payload is too large or packet is NULL.
 */
bool command_create_set_rudder(CommandPacket *packet, int8_t angle);

/**
 * @brief Creates and serializes a CMD_SET_OPERATIONAL_MODE command into a packet.
 * @param packet Pointer to the CommandPacket struct to be filled.
 * @param mode The target operational mode (OperationalMode enum).
 * @return True if successful, false if packet is NULL.
 */
bool command_create_set_op_mode(CommandPacket *packet, OperationalMode mode);

/**
 * @brief Creates and serializes a CMD_REQUEST_SENSOR_DATA command into a packet.
 *        This command might have an empty payload.
 * @param packet Pointer to the CommandPacket struct to be filled.
 * @return True if successful, false if packet is NULL.
 */
bool command_create_request_sensor_data(CommandPacket *packet);

/**
 * @brief Deserializes (parses) a byte buffer into a CommandPacket struct.
 *        Validates start byte, payload length, and checksum.
 * @param buffer Pointer to the raw byte buffer received.
 * @param buffer_length The length of the received buffer.
 * @param A CommandPacket struct that will be filled if deserialization is successful.
 * @return True if parsing is successful and checksum is valid, false otherwise.
 */
bool command_parse_packet(const uint8_t *buffer, uint8_t buffer_length, CommandPacket *parsed_packet);

// --- Functions to extract data from a parsed packet's payload ---
// These demonstrate how to safely get typed data from the generic payload.

/**
 * @brief Extracts the rudder angle from a parsed CMD_SET_RUDDER_ANGLE packet.
 * @param packet Pointer to a successfully parsed CommandPacket.
 * @param out_angle Pointer to an int8_t where the angle will be stored.
 * @return True if the packet is the correct type and payload is valid, false otherwise.
 */
bool command_get_rudder_angle_payload(const CommandPacket *packet, int8_t *out_angle);

/**
 * @brief Extracts the operational mode from a parsed CMD_SET_OPERATIONAL_MODE packet.
 * @param packet Pointer to a successfully parsed CommandPacket.
 * @param out_mode Pointer to an OperationalMode where the mode will be stored.
 * @return True if the packet is the correct type and payload is valid, false otherwise.
 */
bool command_get_op_mode_payload(const CommandPacket *packet, OperationalMode *out_mode);

#endif // COMMAND_PROTOCOL_H_