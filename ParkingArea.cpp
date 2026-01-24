#include "ParkingArea.h"

ParkingArea::ParkingArea() {
    slots = nullptr;
    slotCount = 0;
}

ParkingArea::ParkingArea(int count, int zoneId) {
    slotCount = count;
    slots = new ParkingSlot[slotCount];

    for (int i = 0; i < slotCount; i++) {
        slots[i] = ParkingSlot(i, zoneId);  // ✅ correct assignment
    }
}

ParkingArea::~ParkingArea() {
    delete[] slots;
}

ParkingSlot* ParkingArea::getAvailableSlot() {
    for (int i = 0; i < slotCount; i++) {
        if (slots[i].getAvailability()) {
            return &slots[i];
        }
    }
    return nullptr;
}
