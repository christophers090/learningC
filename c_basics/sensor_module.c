#include "sensor_module.h" // Include our own header file
#include <stdio.h>         // For printf (standard input/output)
#include <stdlib.h>        // For rand() (standard library for general utilities)
#include <time.h>          // For time() to seed rand()

// --- Static Global Variable (Module-Specific State) ---
// 'static' when used at file scope (outside any function) limits the visibility
// of this variable to this .c file only. It cannot be accessed directly from other files.
static int sensor_initialized = 0; // 0 for false, 1 for true

// --- Function Definitions (Implementations) ---

void sensor_init(void)
{
    // Seed the random number generator once
    // This makes our simulated sensor readings a bit different each run.
    // time(NULL) gets the current time, used as a seed.
    srand(time(NULL));
    sensor_initialized = 1;
    printf("Sensor Module Initialized.\n");
}

SensorData sensor_read_data(void)
{
    SensorData data;

    if (!sensor_initialized)
    {
        printf("Warning: Reading sensor data before initialization!\n");
        // Return zeroed/default data if not initialized
        data.altitude_m = 0.0f;
        data.airspeed_kmh = 0;
        data.temperature_c = 0.0f;
        data.status_flags = SENSOR_STATUS_ERROR; // Indicate an error
        return data;
    }

    // Simulate sensor readings with some randomness
    data.altitude_m = 1000.0f + (rand() % 500) - 250.0f; // Base 1000m +/- 250m
    data.airspeed_kmh = 300 + (rand() % 100) - 50;       // Base 300kmh +/- 50kmh
    data.temperature_c = 15.0f + (rand() % 20) - 10.0f;  // Base 15C +/- 10C

    // Simulate status flags
    data.status_flags = SENSOR_STATUS_OK; // Start with OK
    if (rand() % 10 == 0)
    {                                                   // 10% chance of low battery
        data.status_flags |= SENSOR_STATUS_LOW_BATTERY; // Use bitwise OR to set a flag
    }
    if (rand() % 20 == 0)
    { // 5% chance of general error
        data.status_flags |= SENSOR_STATUS_ERROR;
        data.status_flags &= ~SENSOR_STATUS_OK; // Use bitwise AND with NOT to clear OK flag
    }
    if (rand() % 5 == 0)
    { // 20% chance it needs calibration
        data.status_flags |= SENSOR_STATUS_NEEDS_CAL;
    }

    return data;
}

void sensor_process_status_flags(uint8_t flags)
{
    printf("Sensor Status: ");
    if (flags == 0)
    { // No flags set might mean uninitialized or a problem
        printf("UNKNOWN or NO FLAGS SET\n");
        return;
    }

    // Check each bit using bitwise AND
    if (flags & SENSOR_STATUS_OK)
    {
        printf("[OK] ");
    }
    if (flags & SENSOR_STATUS_LOW_BATTERY)
    {
        printf("[LOW_BATTERY] ");
    }
    if (flags & SENSOR_STATUS_ERROR)
    {
        printf("[ERROR] ");
    }
    if (flags & SENSOR_STATUS_NEEDS_CAL)
    {
        printf("[NEEDS_CALIBRATION] ");
    }
    printf("\n");
}