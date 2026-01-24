#ifndef ROLLBACKMANAGER_H
#define ROLLBACKMANAGER_H

#include "ParkingSlot.h"
#include "ParkingRequest.h"

class RollbackManager {
private:
    ParkingSlot* history[100];
    int top;

public:
    RollbackManager();
    void record(ParkingSlot* slot);
    void rollback(ParkingRequest& request);
};

#endif

