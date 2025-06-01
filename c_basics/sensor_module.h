#ifndef SENSOR_MODULE_H_
#define SENSOR_MODULE_H_

#include <stdint.h> // For fixed-width integers like uint8_t, int16_t, float is also common

// --- Constants for Sensor Status Flags (Bit Positions) ---
// These #defines demonstrate use of the preprocessor for constants.
// They represent individual bits in a status register.
#define SENSOR_STATUS_OK (1 << 0)          // Bit 0: Sensor is OK
#define SENSOR_STATUS_LOW_BATTERY (1 << 1) // Bit 1: Low battery warning
#define SENSOR_STATUS_ERROR (1 << 2)       // Bit 2: General sensor error
#define SENSOR_STATUS_NEEDS_CAL (1 << 3)   // Bit 3: Sensor needs calibration

// --- SensorData Structure ---
// This 'struct' is a custom data type to group related sensor readings.
// In C, it's common to group data related to a device or a concept this way.
typedef struct
{
    float altitude_m;     // Altitude in meters
    int16_t airspeed_kmh; // Airspeed in km/h
    float temperature_c;  // Temperature in Celsius
    uint8_t status_flags; // A byte to hold various status bits (using #defines above)
} SensorData;

// --- Function Declarations (Prototypes) ---
// These tell the compiler about the functions that will be implemented elsewhere (in sensor_module.c).
// This is key for multi-file projects.

/**
 * @brief Initializes the sensor module.
 * In a real system, this might configure hardware registers.
 */
void sensor_init(void);

/**
 * @brief Simulates reading data from the flight sensor.
 * @return A SensorData struct populated with new readings.
 */
SensorData sensor_read_data(void);

/**
 * @brief Processes and prints messages based on sensor status flags.
 * Demonstrates bitwise operations.
 * @param flags The status_flags byte from SensorData.
 */
void sensor_process_status_flags(uint8_t flags);

#endif // SENSOR_MODULE_H_