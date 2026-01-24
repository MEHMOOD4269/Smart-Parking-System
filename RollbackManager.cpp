#include "RollbackManager.h"
#include <iostream>
using namespace std;

RollbackManager::RollbackManager() : top(-1) {}

void RollbackManager::record(ParkingSlot* slot) {
    history[++top] = slot;
}

void RollbackManager::rollback(ParkingRequest& request) {
    // Validate state before rollback
    if (!request.canRollback()) {
        cout << "Invalid state: cannot rollback\n";
        return;
    }
    
    if (top >= 0) {
        history[top--]->release();
        request.changeState(ROLLED_BACK);
    }
}

