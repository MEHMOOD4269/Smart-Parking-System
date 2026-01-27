#include "ParkingRequest.h"

ParkingRequest::ParkingRequest(int vId, int zId) 
    : vehicleId(vId), requestedZone(zId), allocatedZone(-1), state(REQUESTED) {}

int ParkingRequest::getRequestedZone() const {
    return requestedZone;
}

void ParkingRequest::setAllocatedZone(int zone) {
    allocatedZone = zone;
}

int ParkingRequest::getAllocatedZone() const {
    return allocatedZone;
}

RequestState ParkingRequest::getState() const {
    return state;
}

void ParkingRequest::setState(RequestState s) {
    state = s;
}

bool ParkingRequest::canCancel() const {
    return state == REQUESTED || state == ALLOCATED;
}