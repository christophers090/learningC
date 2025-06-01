#include "gps_moduel.h"
#include <stdio.h>

static const uint8_t regesters[] = {
    GPS_FLAG_REG_1,
    GPS_FLAG_REG_2,
    GPS_FLAG_REG_3,
    GPS_FLAG_REG_4};

uint64_t gps_get_reading_lat(const gps_moduel *gps)
{
    if (gps == NULL)
    {
        fprintf(stderr, "Error: NULL pointer passed to gps_get_reading_lat\n");
        return 0;
    }
    return gps->lat_reading;
}

uint64_t gps_get_reading_lng(const gps_moduel *gps)
{
    if (gps == NULL)
    {
        fprintf(stderr, "Error: NULL pointer passed to gps_get_reading_lng\n");
        return 0;
    }
    return gps->long_reading;
}

void setStatusFlag(gps_moduel *const gps, int reg, bool active)
{
    if (gps == NULL)
    {
        fprintf(stderr, "null!!!!");
        return;
    }

    if (reg < 0 || reg > (sizeof(regesters) / sizeof(regesters[0])))
    {
        fprintf(stderr, "too big/small");
        return;
    }

    uint8_t mask = regesters[reg - 1];

    if (active)
    {
        gps->status_flags |= mask;
    }
    else
    {
        gps->status_flags &= ~mask;
    }
    return;
}