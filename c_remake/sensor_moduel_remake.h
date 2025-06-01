#ifndef SENSOR_H
#define SENSOR_H

#define SENSOR_OK (1 << 0)
#define SENSOR_LOW_BAT (1 << 1)
#define SENSOR_OVERHEAT (1 << 2)

#include <stdint.h>

typedef struct
{
    float altitude_m;
    uint16_t airspeed_kmh;
    float temp_c;
    uint8_t status_flags;
} SensorData;

void sensor_init(void);

SensorData sensor_read_data(void);

void sensor_process_status_flags(uint8_t flags);

#endif