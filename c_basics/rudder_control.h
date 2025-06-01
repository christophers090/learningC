#ifndef RUDDER_CONTROL_H_
#define RUDDER_CONTROL_H_

#include <stdint.h> // For int8_t

// --- Constants ---
#define RUDDER_MAX_ANGLE 45  // Degrees
#define RUDDER_MIN_ANGLE -45 // Degrees

// --- RudderConfig Structure ---
// Could hold calibration data, limits, etc. in a real system.
// For simplicity, we'll keep it light.
typedef struct
{
    int8_t current_angle_deg; // Current rudder angle in degrees
    // Add other config like: float sensitivity; uint16_t update_rate_hz;
} RudderConfig;

// --- Function Declarations ---

/**
 * @brief Initializes the rudder control system.
 * @param initial_angle The starting angle for the rudder.
 */
void rudder_init(int8_t initial_angle_deg);

/**
 * @brief Sets the rudder to a target angle, applying limits.
 * @param config Pointer to the RudderConfig struct to modify its current_angle_deg.
 * @param target_angle_deg The desired angle for the rudder.
 * @return The actual angle set after applying limits (could be different from target).
 */
int8_t rudder_set_angle(RudderConfig *config, int8_t target_angle_deg);

/**
 * @brief Gets the current angle of the rudder.
 * @param config Pointer to the RudderConfig struct to read its current_angle_deg.
 * @return The current rudder angle in degrees.
 */
int8_t rudder_get_current_angle(const RudderConfig *config); // const pointer as it doesn't modify config

#endif // RUDDER_CONTROL_H_