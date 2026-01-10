#include "ParkingSlot.h"

ParkingSlot::ParkingSlot()
    : slotId(-1), zoneId(-1), isAvailable(true) {}

ParkingSlot::ParkingSlot(int id, int zone)
    : slotId(id), zoneId(zone), isAvailable(true) {}

bool ParkingSlot::getAvailability() const {
    return isAvailable;
}

void ParkingSlot::occupy() {
    isAvailable = false;
}

void ParkingSlot::release() {
    isAvailable = true;
}

int ParkingSlot::getZoneId() const {
    return zoneId;
}

