#ifndef ALLOCATIONENGINE_H
#define ALLOCATIONENGINE_H

class Zone;
class ParkingRequest;
class RollbackManager;
class ParkingSlot;

class AllocationEngine {
public:
    ParkingSlot* allocate(Zone* zones, int zoneCount, ParkingRequest& request, RollbackManager& rollback);
};

#endif