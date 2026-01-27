#include "RollbackManager.h"
#include <iostream>
using namespace std;

RollbackManager::RollbackManager() {
    top = -1;
}

void RollbackManager::push(ParkingSlot* slot, ParkingRequest* request) {
    if (top < 99) {
        stack[++top] = {slot, request};
    }
}

void RollbackManager::rollback() {
    if (top < 0) {
        cout << "No operations to rollback.\n";
        return;
    }

    // Release the slot
    stack[top].slot->release();
    
    // Reset request state
    stack[top].request->setState(REQUESTED);
    
    cout << "Rollback successful. Slot freed.\n";
    top--;
}

bool RollbackManager::isEmpty() const {
    return top == -1;
}