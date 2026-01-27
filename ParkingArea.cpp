#include "ParkingArea.h"

ParkingArea::ParkingArea() {
    areaId = -1;
}

void ParkingArea::setup(int zoneID, int aID) {
    areaId = aID;
    // CHANGED: Loop 10 ki bajaye 4 tak chalega
    for (int i = 0; i < 4; i++) {
        mySlots[i].setup(zoneID, areaId, i);
    }
}

ParkingSlot* ParkingArea::getSlots() {
    return mySlots;
}

int ParkingArea::getSlotCount() const {
    return 4; // CHANGED: Return 4
}
