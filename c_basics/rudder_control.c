#include "rudder_control.h"
#include <stdio.h> // For printf

// --- Static Global Variable (Module-Specific State) ---
// This will store the actual rudder configuration. In a more complex system,
// you might have an array of these if controlling multiple rudders, or this
// might be dynamically allocated if the number of rudders isn't fixed.
static RudderConfig global_rudder_config; // Our single rudder instance
static int rudder_system_initialized = 0;

// --- Function Definitions ---

void rudder_init(int8_t initial_angle_deg)
{
    // Apply limits to the initial angle
    if (initial_angle_deg > RUDDER_MAX_ANGLE)
    {
        global_rudder_config.current_angle_deg = RUDDER_MAX_ANGLE;
    }
    else if (initial_angle_deg < RUDDER_MIN_ANGLE)
    {
        global_rudder_config.current_angle_deg = RUDDER_MIN_ANGLE;
    }
    else
    {
        global_rudder_config.current_angle_deg = initial_angle_deg;
    }
    rudder_system_initialized = 1;
    printf("Rudder Control Initialized. Angle set to: %d degrees\n", global_rudder_config.current_angle_deg);
}

int8_t rudder_set_angle(RudderConfig *config, int8_t target_angle_deg)
{
    if (!rudder_system_initialized)
    {
        printf("Warning: Rudder control system not initialized!\n");
        if (config != NULL)
        { // Basic null check for pointer
          // Do not modify if not initialized, but ensure it reflects some safe state if possible
          // This part is tricky as config might be uninitialized itself if not handled by caller
          // For this example, we assume rudder_init manages the global_rudder_config exclusively
        }
        return config ? config->current_angle_deg : 0; // Return current or a default
    }

    if (config == NULL)
    {
        printf("Error: RudderConfig pointer is NULL in rudder_set_angle.\n");
        return 0; // Or some error code / default angle
    }

    int8_t actual_angle = target_angle_deg;

    // Apply angle limits
    if (actual_angle > RUDDER_MAX_ANGLE)
    {
        actual_angle = RUDDER_MAX_ANGLE;
        printf("Rudder angle limited to MAX: %d degrees\n", RUDDER_MAX_ANGLE);
    }
    else if (actual_angle < RUDDER_MIN_ANGLE)
    {
        actual_angle = RUDDER_MIN_ANGLE;
        printf("Rudder angle limited to MIN: %d degrees\n", RUDDER_MIN_ANGLE);
    }

    // Update the current angle in the passed-in RudderConfig struct
    // The -> operator is used to access members of a struct via a pointer.
    config->current_angle_deg = actual_angle;

    // For this simple example, we'll also update our global_rudder_config
    // if the passed config happens to be pointing to it. In a more robust system,
    // the function would only operate on the *config it was given.
    if (config == &global_rudder_config)
    {
        // This is just for consistency in this specific example's structure
    }
    else
    {
        // If config was a different RudderConfig instance, only that instance would be updated.
        // printf("Note: A non-global RudderConfig instance was updated.\n");
    }

    return actual_angle;
}

int8_t rudder_get_current_angle(const RudderConfig *config)
{
    if (!rudder_system_initialized)
    {
        printf("Warning: Rudder control system not initialized!\n");
        return 0; // Return a default/neutral angle
    }
    if (config == NULL)
    {
        printf("Error: RudderConfig pointer is NULL in rudder_get_current_angle.\n");
        return 0; // Or some error code / default angle
    }
    // The -> operator is used here as well.
    // Since 'config' is a const RudderConfig*, we can only call const methods
    // or access members in a read-only fashion (which is what we are doing).
    return config->current_angle_deg;
}
