#include "ParkingSlot.h"

ParkingSlot::ParkingSlot() : slotId(-1), zoneId(-1), occupied(false) {}

void ParkingSlot::setup(int sId, int zId) {
    slotId = sId;
    zoneId = zId;
    occupied = false; // Reset to free
}

bool ParkingSlot::isOccupied() const { return occupied; }
void ParkingSlot::occupy() { occupied = true; }
void ParkingSlot::release() { occupied = false; }
int ParkingSlot::getSlotId() const { return slotId; }
int ParkingSlot::getZoneId() const { return zoneId; }