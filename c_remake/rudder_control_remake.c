#include "rudder_control_remake.h"
#include <stdio.h>

// Removed static global variables, state is managed by the caller
// static uint8_t is_rudder_initialized = 0;
// static RudderInfo rudder;

// Initialize the RudderInfo struct provided by the caller
void rudder_init(RudderInfo *rudder_to_init, int8_t initial_angle)
{
    if (rudder_to_init == NULL)
    {
        fprintf(stderr, "Error: NULL pointer passed to rudder_init\n");
        return;
    }

    int8_t angle_to_set = initial_angle;

    // Apply limits to the initial angle before setting
    if (angle_to_set > MAX_ANGLE)
    {
        angle_to_set = MAX_ANGLE;
    }
    else if (angle_to_set < MIN_ANGLE)
    {
        angle_to_set = MIN_ANGLE;
    }

    // Set the angle in the caller-provided struct
    rudder_to_init->angle = angle_to_set;

    // Initialization complete is implicit by the function returning.
    // The caller now knows the struct they passed is initialized.
    // printf("Rudder Initialized via pointer. Angle set to: %d\n", rudder_to_init->angle);
}

int8_t rudder_set_angle(RudderInfo *rudder, int8_t angle)
{
    // No initialization check here; assumes caller initialized the struct passed in.
    if (rudder == NULL)
    {
        fprintf(stderr, "Error: got null rudder ptr in rudder_set_angle\n");
        return 0; // Return a default/neutral angle on error
    }

    // Clamp the target angle
    int8_t angle_to_set = angle;
    if (angle_to_set > MAX_ANGLE)
    {
        angle_to_set = MAX_ANGLE;
    }
    else if (angle_to_set < MIN_ANGLE)
    {
        angle_to_set = MIN_ANGLE;
    }

    // Set the angle in the caller-provided struct
    rudder->angle = angle_to_set;
    return angle_to_set; // Return the actual angle set
}

int8_t rudder_get_angle(const RudderInfo *rudder)
{
    // No initialization check here.
    if (rudder == NULL)
    {
        fprintf(stderr, "Error: got null rudder ptr in rudder_get_angle\n");
        return 0; // Return a default/neutral angle on error
    }
    return rudder->angle;
}
