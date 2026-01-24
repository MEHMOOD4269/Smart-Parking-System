#include "ParkingRequest.h"

ParkingRequest::ParkingRequest(int vId, int zId)
    : vehicleId(vId), zoneId(zId), state(REQUESTED) {}

bool ParkingRequest::changeState(RequestState newState) {
    if (
        (state == REQUESTED && (newState == ALLOCATED || newState == CANCELLED)) ||
        (state == ALLOCATED && (newState == OCCUPIED || newState == CANCELLED)) ||
        (state == OCCUPIED && newState == RELEASED)
    ) {
        state = newState;
        return true;
    }
    return false;
}

RequestState ParkingRequest::getState() const {
    return state;
}

bool ParkingRequest::canAllocate() const {
    return state == REQUESTED;
}

bool ParkingRequest::canCancel() const {
    return state == ALLOCATED || state == REQUESTED;
}

bool ParkingRequest::canRollback() const {
    return state == CANCELLED || state == ALLOCATED;
}

