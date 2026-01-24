#include "ParkingRequest.h"

ParkingRequest::ParkingRequest(int vid, int zone, int time)
    : vehicleId(vid),
      requestedZone(zone),
      allocatedZone(-1),
      requestTime(time),
      releaseTime(-1),
      state(REQUESTED) {}

bool ParkingRequest::canAllocate() const {
    return state == REQUESTED;
}

bool ParkingRequest::canOccupy() const {
    return state == ALLOCATED;
}

bool ParkingRequest::canRelease() const {
    return state == OCCUPIED;
}

bool ParkingRequest::canCancel() const {
    return state == REQUESTED || state == ALLOCATED;
}

bool ParkingRequest::canTransition(RequestState next) const {
    if (state == REQUESTED && next == ALLOCATED) return true;
    if (state == ALLOCATED && next == OCCUPIED) return true;
    if (state == OCCUPIED && next == RELEASED) return true;
    if ((state == REQUESTED || state == ALLOCATED) && next == CANCELLED) return true;
    return false;
}

void ParkingRequest::setAllocatedZone(int zone) {
    allocatedZone = zone;
}

int ParkingRequest::getAllocatedZone() const {
    return allocatedZone;
}

int ParkingRequest::getRequestedZone() const {
    return requestedZone;
}

int ParkingRequest::getRequestTime() const {
    return requestTime;
}

void ParkingRequest::setReleaseTime(int time) {
    releaseTime = time;
}

int ParkingRequest::getReleaseTime() const {
    return releaseTime;
}

int ParkingRequest::getDuration() const {
    if (requestTime == -1 || releaseTime == -1) return -1;
    return releaseTime - requestTime;
}

RequestState ParkingRequest::getState() const {
    return state;
}

void ParkingRequest::setState(RequestState s) {
    state = s;
}

