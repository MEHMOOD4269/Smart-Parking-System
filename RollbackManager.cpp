#include "RollbackManager.h"
#include "ParkingSlot.h"
#include "ParkingRequest.h"
#include <iostream> // NULL ke liye

RollbackManager::RollbackManager() {
    top = -1;
}

void RollbackManager::push(ParkingSlot* s, ParkingRequest* r) {
    if (top < 99) { // 100 ki limit check
        top++;
        stack[top].slot = s;
        stack[top].request = r;
    }
}

void RollbackManager::rollback() {
    if (top >= 0) {
        // 1. Slot ko free karo
        stack[top].slot->release();

        // 2. Request ko reset karo
        // FIX: 'REQUESTED' ki jagah 'PENDING' use kiya
        stack[top].request->setState(PENDING);
        stack[top].request->setAllocatedZone(-1);

        top--; // Stack se hatao
    }
}
