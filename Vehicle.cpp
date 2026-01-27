#include "Vehicle.h"

Vehicle::Vehicle(int id, int zone) 
    : vehicleId(id), preferredZone(zone) {}

int Vehicle::getVehicleId() const {
    return vehicleId;
}

int Vehicle::getPreferredZone() const {
    return preferredZone;
}