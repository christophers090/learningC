#ifndef GPS_MODUEL_H_
#define GPS_MODUEL_H_

#define GPS_FLAG_REG_1 (0x1 << 0)
#define GPS_FLAG_REG_2 (0x1 << 1)
#define GPS_FLAG_REG_3 (0x1 << 2)
#define GPS_FLAG_REG_4 (0x1 << 3)

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t status_flags;
    uint64_t lat_reading;
    uint64_t long_reading;
} gps_moduel;

uint64_t gps_get_reading_lat(const gps_moduel *gps);

uint64_t gps_get_reading_lng(const gps_moduel *gps);

void setStatusFlag(gps_moduel *const gps, int reg, bool active);

#endif