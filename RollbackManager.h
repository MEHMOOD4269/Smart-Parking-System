#ifndef ROLLBACKMANAGER_H
#define ROLLBACKMANAGER_H

#include "ParkingSlot.h"
#include "ParkingRequest.h"

// Structured rollback action for STACK
struct RollbackEntry {
    ParkingSlot* slot;
    ParkingRequest* request;
};

class RollbackManager {
private:
    RollbackEntry stack[100];
    int top;

public:
    RollbackManager();
    void push(ParkingSlot* slot, ParkingRequest* request);
    void rollback();
    bool isEmpty() const;
};

#endif

