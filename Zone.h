#ifndef ZONE_H
#define ZONE_H

#include "ParkingArea.h"

class Zone {
private:
    int zoneId;
    ParkingArea* areas;
    int areaCount;

public:
    Zone(int id, int count);
    ParkingArea* getAreas();
    int getZoneId() const;
};

#endif

