#ifndef PARKINGAREA_H
#define PARKINGAREA_H

#include "ParkingSlot.h"

class ParkingArea {
private:
    ParkingSlot* slots;
    int slotCount;

public:
    ParkingArea();
    ParkingArea(int count, int zoneId);
    ~ParkingArea();
    ParkingSlot* getAvailableSlot();
};

#endif
