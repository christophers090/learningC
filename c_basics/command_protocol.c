#include "command_protocol.h"
#include <string.h> // For memcpy and memset
#include <stdio.h>  // For fprintf (for error messages if needed)

// --- Checksum Calculation ---
uint8_t command_calculate_checksum(const uint8_t *data, uint8_t length)
{
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < length; ++i)
    {
        checksum ^= data[i]; // Simple XOR checksum
    }
    return checksum;
}

// --- Helper to prepare a basic packet structure ---
static void prepare_packet_header(CommandPacket *packet, CommandType type, uint8_t payload_len)
{
    if (!packet)
        return;
    memset(packet, 0, sizeof(CommandPacket)); // Zero out the packet initially
    packet->start_byte = PACKET_START_BYTE;
    packet->command_type = type;
    packet->payload_length = payload_len;
}

// --- Command Creation/Serialization Functions ---

bool command_create_set_rudder(CommandPacket *packet, int8_t angle)
{
    if (!packet)
        return false;
    if (sizeof(int8_t) > MAX_PAYLOAD_SIZE)
        return false; // Sanity check

    prepare_packet_header(packet, CMD_SET_RUDDER_ANGLE, sizeof(int8_t));

    // memcpy: copies 'n' bytes from memory area 'src' to memory area 'dest'.
    // Here, we copy the bytes of the 'angle' variable into the packet's payload.
    // (void*) cast for payload is good practice if it was char*, but uint8_t* is fine.
    // &angle gives the memory address of the 'angle' variable.
    memcpy(packet->payload, &angle, sizeof(int8_t));

    // Calculate checksum over the packet *before* the checksum field itself
    // The length includes start_byte, command_type, payload_length, and the actual payload.
    uint8_t checksum_len = sizeof(packet->start_byte) +
                           sizeof(packet->command_type) +
                           sizeof(packet->payload_length) +
                           packet->payload_length;
    packet->checksum = command_calculate_checksum((uint8_t *)packet, checksum_len);
    return true;
}

bool command_create_set_op_mode(CommandPacket *packet, OperationalMode mode)
{
    if (!packet)
        return false;
    // Assuming OperationalMode enum fits in uint8_t for simplicity in payload
    if (sizeof(uint8_t) > MAX_PAYLOAD_SIZE)
        return false;

    prepare_packet_header(packet, CMD_SET_OPERATIONAL_MODE, sizeof(uint8_t));

    uint8_t mode_val = (uint8_t)mode; // Cast enum to uint8_t for payload
    memcpy(packet->payload, &mode_val, sizeof(uint8_t));

    uint8_t checksum_len = sizeof(packet->start_byte) + sizeof(packet->command_type) +
                           sizeof(packet->payload_length) + packet->payload_length;
    packet->checksum = command_calculate_checksum((uint8_t *)packet, checksum_len);
    return true;
}

bool command_create_request_sensor_data(CommandPacket *packet)
{
    if (!packet)
        return false;

    prepare_packet_header(packet, CMD_REQUEST_SENSOR_DATA, 0); // No payload for this command

    uint8_t checksum_len = sizeof(packet->start_byte) + sizeof(packet->command_type) +
                           sizeof(packet->payload_length); // No payload length to add here
    packet->checksum = command_calculate_checksum((uint8_t *)packet, checksum_len);
    return true;
}

// --- Deserialization/Parsing Function ---

bool command_parse_packet(const uint8_t *buffer, uint8_t buffer_length, CommandPacket *parsed_packet)
{
    if (!buffer || !parsed_packet)
        return false;

    // Minimum packet length: start_byte, type, payload_len, checksum (payload can be 0)
    uint8_t min_len = sizeof(parsed_packet->start_byte) +
                      sizeof(parsed_packet->command_type) +
                      sizeof(parsed_packet->payload_length) +
                      sizeof(parsed_packet->checksum);

    if (buffer_length < min_len)
    {
        fprintf(stderr, "Error: Buffer too short to be a valid packet.\n");
        return false;
    }

    if (buffer[0] != PACKET_START_BYTE)
    {
        fprintf(stderr, "Error: Invalid start byte.\n");
        return false;
    }

    // Temporarily copy header to get payload_length
    parsed_packet->start_byte = buffer[0];
    parsed_packet->command_type = buffer[1];
    parsed_packet->payload_length = buffer[2];

    if (parsed_packet->payload_length > MAX_PAYLOAD_SIZE)
    {
        fprintf(stderr, "Error: Payload length in packet exceeds MAX_PAYLOAD_SIZE.\n");
        return false;
    }

    // Check if buffer_length matches expected total packet length
    uint8_t expected_total_length = sizeof(parsed_packet->start_byte) +
                                    sizeof(parsed_packet->command_type) +
                                    sizeof(parsed_packet->payload_length) +
                                    parsed_packet->payload_length +
                                    sizeof(parsed_packet->checksum);

    if (buffer_length != expected_total_length)
    {
        fprintf(stderr, "Error: Buffer length does not match expected packet length based on payload_length field.\n");
        return false;
    }

    // Copy the payload
    // memset payload to 0 before copying, to avoid garbage in unused parts if payload_length < MAX_PAYLOAD_SIZE
    memset(parsed_packet->payload, 0, MAX_PAYLOAD_SIZE);
    memcpy(parsed_packet->payload, &buffer[3], parsed_packet->payload_length);

    // Extract the received checksum
    uint8_t received_checksum = buffer[expected_total_length - 1]; // Last byte

    // Calculate checksum on the received data (excluding the checksum byte itself)
    uint8_t calculated_checksum_len = expected_total_length - sizeof(parsed_packet->checksum);
    uint8_t calculated_checksum = command_calculate_checksum(buffer, calculated_checksum_len);

    if (received_checksum != calculated_checksum)
    {
        fprintf(stderr, "Error: Checksum mismatch. Expected 0x%02X, Got 0x%02X\n", calculated_checksum, received_checksum);
        return false;
    }

    parsed_packet->checksum = received_checksum; // Store the validated checksum
    return true;
}

// --- Payload Extraction Functions ---

bool command_get_rudder_angle_payload(const CommandPacket *packet, int8_t *out_angle)
{
    if (!packet || !out_angle)
        return false;
    if (packet->command_type != CMD_SET_RUDDER_ANGLE)
        return false;
    if (packet->payload_length != sizeof(int8_t))
        return false;

    memcpy(out_angle, packet->payload, sizeof(int8_t));
    return true;
}

bool command_get_op_mode_payload(const CommandPacket *packet, OperationalMode *out_mode)
{
    if (!packet || !out_mode)
        return false;
    if (packet->command_type != CMD_SET_OPERATIONAL_MODE)
        return false;
    if (packet->payload_length != sizeof(uint8_t))
        return false; // Assuming mode fits in uint8_t

    uint8_t mode_val;
    memcpy(&mode_val, packet->payload, sizeof(uint8_t));
    *out_mode = (OperationalMode)mode_val; // Cast back to enum
    return true;
}