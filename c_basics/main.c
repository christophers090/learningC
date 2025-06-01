#include <stdio.h>  // For printf
#include <string.h> // For memcmp
// #include <unistd.h> // For sleep() - POSIX specific

#include "sensor_module.h"    // Our sensor module
#include "rudder_control.h"   // Our rudder control module
#include "command_protocol.h" // Our new command protocol module

// Main loop delay (if sleep was used)
// #define MAIN_LOOP_DELAY_S 1

// Helper function to print a packet for debugging
void print_packet_bytes(const CommandPacket *packet)
{
    if (!packet)
        return;
    printf("Packet Bytes (Hex): ");
    const uint8_t *ptr = (const uint8_t *)packet;
    // Calculate total packet size based on its actual content
    size_t packet_total_size = sizeof(packet->start_byte) +
                               sizeof(packet->command_type) +
                               sizeof(packet->payload_length) +
                               packet->payload_length +
                               sizeof(packet->checksum);
    for (size_t i = 0; i < packet_total_size; ++i)
    {
        printf("%02X ", ptr[i]);
    }
    printf("\n");
}

// --- Main Application Logic ---
int main(void)
{
    printf("--- Flight System Simulation Starting ---\n");

    // Initialize modules
    sensor_init();

    // Initialize rudder - get the address of the global config from the rudder module
    // This is a bit of a simplification for this example. A more robust approach might
    // involve the rudder_init function returning a pointer or handle.
    // For now, rudder_init directly sets up its internal static global_rudder_config.
    rudder_init(0); // Start rudder at 0 degrees

    // Get a pointer to the global rudder config to pass to functions
    // This demonstrates how main might interact with a module's state if necessary,
    // although ideally, interaction is purely through the module's API.
    // In rudder_control.c, we have `static RudderConfig global_rudder_config;`
    // We can't access `global_rudder_config` directly from main.c because it's static.
    // So, we need a way to get its state or pass it around. We'll simulate this
    // by creating a local RudderConfig and having rudder_control.c update it when we pass its address.
    // A better way would be for rudder_control to have a function like `RudderConfig* get_rudder_config_instance()`
    // or always pass a pointer to a config struct that main owns.

    // For this example, let's assume rudder_control.c has: `static RudderConfig global_rudder_config;`
    // And rudder_init, rudder_set_angle, rudder_get_current_angle in rudder_control.c implicitly
    // operate on this global_rudder_config or a passed-in one.
    // To interact with it from main, we need to call functions that accept our *local* config
    // or have the module provide a way to get *its* config.

    // Let main own its rudder configuration instance
    RudderConfig main_rudder_state;
    main_rudder_state.current_angle_deg = rudder_get_current_angle(&main_rudder_state); // Initialize with current (which rudder_init set globally)
                                                                                        // This is a bit circular for init. Let's simplify.
                                                                                        // rudder_init already set its internal one to 0.
                                                                                        // Let's just use a local RudderConfig that reflects the system rudder.

    // A more direct way for this example: rudder_init works on its internal static instance.
    // When we call rudder_get/set_angle, we need to pass the address of the instance we care about.
    // Since main wants to control *the* system rudder, we operate on the global one via API.
    // To do this cleanly without direct global access, rudder_init has set up the internal state.
    // We will now create a local RudderConfig to hold this state for interaction if needed.

    // Re-simplifying: rudder_init configures its *internal* static rudder.
    // We will use rudder_get_current_angle with a NULL (or specific pointer in real app)
    // if it was designed to fetch that internal static one. Our current design requires a pointer.

    // Let's assume rudder_control.c's functions will operate on the struct we pass.
    // And rudder_init has initialized its internal global_rudder_config.
    // To keep main.c self-contained regarding the RudderConfig instance it manipulates:
    RudderConfig my_rudder_config;
    rudder_init(0);                                                                   // Initializes the *internal* rudder in rudder_control.c
    my_rudder_config.current_angle_deg = rudder_get_current_angle(&my_rudder_config); // Read initial state into local copy
                                                                                      // This would actually read uninitialized my_rudder_config.current_angle_deg
                                                                                      // The original rudder_init was better here.

    // Let's stick to: rudder_init initializes the one in rudder_control.c
    // And rudder_set_angle/rudder_get_current_angle will take a pointer to that specific instance.
    // Since we can't get global_rudder_config's address directly from rudder_control.c (it's static),
    // we have to trust that rudder_init has set it up. When we call set/get, we need to pass
    // a pointer to the config we want to affect. If there's only one system rudder, the module handles it internally.

    // Corrected approach for main: We create a RudderConfig in main.
    // rudder_init in the module *could* initialize this if we passed its address, or it initializes its own internal one.
    // Our rudder_init initializes its internal static one.
    // rudder_set_angle and rudder_get_current_angle take a pointer. We will pass a pointer to our *main's* rudder config.
    // The functions in rudder_control.c will then update *our* main_rudder_config.

    RudderConfig controlled_rudder;
    // Initialize our local rudder struct based on the module's initialized state (if there was a getter for the global one)
    // Or, just initialize it directly here, and rudder_set_angle will manage its state.
    controlled_rudder.current_angle_deg = 0;
    printf("Main's rudder view initialized to: %d\n", controlled_rudder.current_angle_deg);

    OperationalMode current_op_mode = MODE_STANDBY;
    printf("System starting in MODE_STANDBY.\n");

    // --- Simulate receiving and processing commands ---
    printf("\n--- Command Processing Test ---\n");

    // 1. Create a "Set Rudder Angle" command
    CommandPacket rudder_cmd_packet;
    int8_t desired_angle = 25;
    if (command_create_set_rudder(&rudder_cmd_packet, desired_angle))
    {
        printf("Created CMD_SET_RUDDER_ANGLE packet for angle %d.\n", desired_angle);
        print_packet_bytes(&rudder_cmd_packet);

        // Simulate receiving this packet (as a raw buffer)
        // In reality, this buffer would come from UART, SPI, CAN, etc.
        uint8_t raw_buffer[sizeof(CommandPacket)]; // Max possible size
        size_t actual_packet_size = sizeof(rudder_cmd_packet.start_byte) +
                                    sizeof(rudder_cmd_packet.command_type) +
                                    sizeof(rudder_cmd_packet.payload_length) +
                                    rudder_cmd_packet.payload_length +
                                    sizeof(rudder_cmd_packet.checksum);
        memcpy(raw_buffer, &rudder_cmd_packet, actual_packet_size);

        CommandPacket parsed_rudder_cmd;
        if (command_parse_packet(raw_buffer, actual_packet_size, &parsed_rudder_cmd))
        {
            printf("Successfully parsed rudder command packet.\n");
            if (parsed_rudder_cmd.command_type == CMD_SET_RUDDER_ANGLE)
            {
                int8_t extracted_angle;
                if (command_get_rudder_angle_payload(&parsed_rudder_cmd, &extracted_angle))
                {
                    printf("Extracted angle from payload: %d\n", extracted_angle);
                    rudder_set_angle(&controlled_rudder, extracted_angle);
                    printf("Rudder - Set by command. Current Angle: %d degrees\n", rudder_get_current_angle(&controlled_rudder));
                }
            }
        }
        else
        {
            printf("Failed to parse rudder command packet.\n");
        }
    }

    // 2. Create a "Set Operational Mode" command
    CommandPacket op_mode_cmd_packet;
    OperationalMode target_mode = MODE_ACTIVE_FLIGHT;
    if (command_create_set_op_mode(&op_mode_cmd_packet, target_mode))
    {
        printf("\nCreated CMD_SET_OPERATIONAL_MODE packet for mode %d.\n", target_mode);
        print_packet_bytes(&op_mode_cmd_packet);

        // Simulate receiving and parsing
        uint8_t raw_op_mode_buffer[sizeof(CommandPacket)];
        size_t actual_op_mode_packet_size = sizeof(op_mode_cmd_packet.start_byte) +
                                            sizeof(op_mode_cmd_packet.command_type) +
                                            sizeof(op_mode_cmd_packet.payload_length) +
                                            op_mode_cmd_packet.payload_length +
                                            sizeof(op_mode_cmd_packet.checksum);
        memcpy(raw_op_mode_buffer, &op_mode_cmd_packet, actual_op_mode_packet_size);

        CommandPacket parsed_op_mode_cmd;
        if (command_parse_packet(raw_op_mode_buffer, actual_op_mode_packet_size, &parsed_op_mode_cmd))
        {
            printf("Successfully parsed op mode command.\n");
            if (parsed_op_mode_cmd.command_type == CMD_SET_OPERATIONAL_MODE)
            {
                OperationalMode extracted_mode;
                if (command_get_op_mode_payload(&parsed_op_mode_cmd, &extracted_mode))
                {
                    current_op_mode = extracted_mode;
                    printf("System operational mode set to: %d\n", current_op_mode);
                }
            }
        }
        else
        {
            printf("Failed to parse op mode command.\n");
        }
    }

    // 3. Create a "Request Sensor Data" command
    CommandPacket req_sensor_cmd_packet;
    if (command_create_request_sensor_data(&req_sensor_cmd_packet))
    {
        printf("\nCreated CMD_REQUEST_SENSOR_DATA packet.\n");
        print_packet_bytes(&req_sensor_cmd_packet);
        // Simulate receiving, parsing, and then acting (e.g., sending sensor data back)
        // For this demo, we'll just parse it.
        uint8_t raw_req_sens_buffer[sizeof(CommandPacket)];
        size_t actual_req_sens_packet_size = sizeof(req_sensor_cmd_packet.start_byte) +
                                             sizeof(req_sensor_cmd_packet.command_type) +
                                             sizeof(req_sensor_cmd_packet.payload_length) +
                                             req_sensor_cmd_packet.payload_length +
                                             sizeof(req_sensor_cmd_packet.checksum);
        memcpy(raw_req_sens_buffer, &req_sensor_cmd_packet, actual_req_sens_packet_size);

        CommandPacket parsed_req_sens_cmd;
        if (command_parse_packet(raw_req_sens_buffer, actual_req_sens_packet_size, &parsed_req_sens_cmd))
        {
            if (parsed_req_sens_cmd.command_type == CMD_REQUEST_SENSOR_DATA)
            {
                printf("Received CMD_REQUEST_SENSOR_DATA. (Simulating sending data back...)\n");
                SensorData s_data = sensor_read_data();
                printf("  Sensor - Alt: %.2f m, Speed: %d km/h, Temp: %.1f C\n",
                       s_data.altitude_m, s_data.airspeed_kmh, s_data.temperature_c);
                sensor_process_status_flags(s_data.status_flags);
            }
        }
        else
        {
            printf("Failed to parse request sensor data command.\n");
        }
    }

    // --- Original Simulation Loop (can be run after command tests or integrated) ---
    printf("\n--- Starting Main Simulation Loop ---\n");
    for (int i = 0; i < 3; ++i)
    { // Shortened loop for brevity
        printf("\n--- Cycle %d (OpMode: %d) ---\n", i + 1, current_op_mode);

        if (current_op_mode == MODE_ACTIVE_FLIGHT)
        {
            SensorData current_sensor_data = sensor_read_data();
            printf("Sensor - Altitude: %.2f m, Airspeed: %d km/h, Temp: %.1f C\n",
                   current_sensor_data.altitude_m,
                   current_sensor_data.airspeed_kmh,
                   current_sensor_data.temperature_c);
            sensor_process_status_flags(current_sensor_data.status_flags);

            int8_t target_rudder_angle = 0;
            if (current_sensor_data.airspeed_kmh > 350)
            {
                target_rudder_angle = -10;
            }
            else if (current_sensor_data.airspeed_kmh < 250)
            {
                target_rudder_angle = 10;
            }
            rudder_set_angle(&controlled_rudder, target_rudder_angle);
            printf("Rudder - Current Angle: %d degrees\n", rudder_get_current_angle(&controlled_rudder));

            if (current_sensor_data.status_flags & SENSOR_STATUS_ERROR)
            {
                printf("CRITICAL: SENSOR ERROR DETECTED! (OpMode: %d)\n", current_op_mode);
                // Potentially switch to MODE_STANDBY or MODE_DIAGNOSTIC
            }
        }
        else if (current_op_mode == MODE_STANDBY)
        {
            printf("System in STANDBY. Rudder held at %d. Sensors idle.\n", rudder_get_current_angle(&controlled_rudder));
            // In standby, we might periodically check system health or listen for commands.
        }
        else if (current_op_mode == MODE_DIAGNOSTIC)
        {
            printf("System in DIAGNOSTIC mode. Running self-tests (simulated)...\n");
            // Perform diagnostic routines
        }
        // sleep(MAIN_LOOP_DELAY_S); // If using sleep
    }

    printf("\n--- Flight System Simulation Ended ---\n");
    return 0; // Indicate successful execution
}