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
    if (top < 0) return;

    stack[top].slot->release();
    stack[top].request->setState(REQUESTED);
    top--;
}

bool RollbackManager::isEmpty() const {
    return top == -1;
}

