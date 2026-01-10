#ifndef PARKINGREQUEST_H
#define PARKINGREQUEST_H

enum RequestState {
    REQUESTED,
    ALLOCATED,
    OCCUPIED,
    RELEASED,
    CANCELLED
};

class ParkingRequest {
private:
    int vehicleId;
    int zoneId;
    RequestState state;

public:
    ParkingRequest(int vId, int zId);
    bool changeState(RequestState newState);
    RequestState getState() const;
};

#endif

