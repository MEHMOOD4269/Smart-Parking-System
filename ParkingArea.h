#ifndef PARKINGAREA_H
#define PARKINGAREA_H

#include "ParkingSlot.h"

class ParkingArea {
private:
    int areaId;
    ParkingSlot slots[10]; // Static Array: Always exists
    int slotCount = 10;

public:
    ParkingArea();
    void setup(int id, int zId);
    ParkingSlot* getSlots();
    int getSlotCount() const;
};

#endif