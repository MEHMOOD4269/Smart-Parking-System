#ifndef PARKINGAREA_H
#define PARKINGAREA_H

#include "ParkingSlot.h"

class ParkingArea {
private:
    ParkingSlot mySlots[4]; // CHANGED: 10 -> 4
    int areaId;

public:
    ParkingArea();

    void setup(int zoneID, int aID);

    ParkingSlot* getSlots();

    int getSlotCount() const; // Ye ab 4 return karega
};

#endif
