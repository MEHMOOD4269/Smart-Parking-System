#ifndef PARKINGREQUEST_H
#define PARKINGREQUEST_H

enum RequestState {
    REQUESTED,
    ALLOCATED,
    OCCUPIED,
    RELEASED,
    CANCELLED,
    ROLLED_BACK
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
    bool canAllocate() const;
    bool canCancel() const;
    bool canRollback() const;
};

#endif

