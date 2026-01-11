#include "RollbackManager.h"

RollbackManager::RollbackManager() : top(-1) {}

void RollbackManager::record(ParkingSlot* slot) {
    history[++top] = slot;
}

void RollbackManager::rollback() {
    if (top >= 0) {
        history[top--]->release();
    }
}

