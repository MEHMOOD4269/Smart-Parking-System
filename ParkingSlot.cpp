#include "ParkingSlot.h"

ParkingSlot::ParkingSlot() {
    occupied = false;
    slotId = -1; zoneId = -1; areaId = -1;
    vehicleId = -1; // Default -1 matlab khali
}

void ParkingSlot::setup(int zId, int aId, int sId) {
    zoneId = zId; areaId = aId; slotId = sId;
}

int ParkingSlot::getSlotId() { return slotId; }
int ParkingSlot::getZoneId() { return zoneId; }
int ParkingSlot::getVehicleId() { return vehicleId; } // NEW
bool ParkingSlot::isOccupied() { return occupied; }

// UPDATED: Jab park karein, to ID save karein
void ParkingSlot::occupy(int vId) {
    occupied = true;
    vehicleId = vId;
}

// UPDATED: Jab release karein, to ID hata dein
void ParkingSlot::release() {
    occupied = false;
    vehicleId = -1;
}
