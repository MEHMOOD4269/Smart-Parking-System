#ifndef ALLOCATIONENGINE_H
#define ALLOCATIONENGINE_H

#include "Zone.h"
#include "ParkingRequest.h"

class ParkingSlot;   

class AllocationEngine {
public:
    ParkingSlot* allocate(Zone* zones, int zoneCount, ParkingRequest& request);
};

#endif
