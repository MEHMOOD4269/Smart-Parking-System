#ifndef ZONE_H
#define ZONE_H

#include "ParkingArea.h"

class Zone {
private:
    int zoneId;
    ParkingArea areas[2]; // Static Array: Always exists
    int areaCount = 2;
    int adjacentZones[10];
    int adjacentCount = 0;

public:
    Zone();
    void setup(int id);
    void addAdjacentZone(int zId);
    int getZoneId() const;
    ParkingArea* getAreas();
    int getAreaCount() const;
};

#endif