#include "ParkingArea.h"

ParkingArea::ParkingArea() {
    areaId = -1;
}

void ParkingArea::setup(int id, int zId) {
    areaId = id;
    for(int i = 0; i < 10; i++) {
        slots[i].setup(i, zId);
    }
}

ParkingSlot* ParkingArea::getSlots() { return slots; }
int ParkingArea::getSlotCount() const { return 10; }