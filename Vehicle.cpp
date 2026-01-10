#include "Vehicle.h"

Vehicle::Vehicle(int id, int zone)
    : vehicleId(id), preferredZone(zone) {}

int Vehicle::getPreferredZone() const {
    return preferredZone;
}

