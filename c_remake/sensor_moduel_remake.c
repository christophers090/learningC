#include "sensor_moduel_remake.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int sensor_initialized = 0;

void sensor_init(void)
{
    // not sure what the see time thing does
    srand(time(NULL));
    sensor_initialized = 1;
};

SensorData sensor_read_data(void)
{
    SensorData data;

    // check to see if initialized
    if (!sensor_initialized)
    {
        fprintf(stderr, "sensor not initialized");
        data.airspeed_kmh = 0;
        data.altitude_m = 0;
        data.temp_c = 0;
        data.status_flags = ~SENSOR_OK;
        return;
    }

    // Simulated data
    data.airspeed_kmh = 100 + (rand() % 100);
    data.altitude_m = 50000.0f + (rand() % 10000);
    data.temp_c = (rand() % 200);
    data.status_flags = SENSOR_OK;

    // Simulated flags
    if (data.temp_c > 190)
    {
        data.status_flags &= ~SENSOR_OK;
        data.status_flags |= SENSOR_OVERHEAT;
    }
    if (rand() % 20 == 0)
    {
        data.status_flags &= ~SENSOR_OK;
        data.status_flags |= SENSOR_LOW_BAT;
    }

    return data;
};

void sensor_process_status_flags(uint8_t flags)
{
    if (flags & SENSOR_LOW_BAT)
    {
        fprintf(stderr, "LOW bat");
    }

    if (flags & SENSOR_OVERHEAT)
    {
        fprintf(stderr, "Overheat");
    }

    return;
};
