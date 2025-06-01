#ifndef RUDDER_CONTROL_REMAKE_H_
#define RUDDER_CONTROL_REMAKE_H_

#define MAX_ANGLE 45
#define MIN_ANGLE -45

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    int8_t angle;
} RudderInfo;

void rudder_init(RudderInfo *rudder_to_init, int8_t initial_angle);

int8_t rudder_set_angle(RudderInfo *rudder, int8_t angle);

int8_t rudder_get_angle(const RudderInfo *rudder);

#endif