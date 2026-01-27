#ifndef PARKINGREQUEST_H
#define PARKINGREQUEST_H

enum RequestState {
    REQUESTED,
    ALLOCATED,
    CANCELLED
};

class ParkingRequest {
private:
    int vehicleId;
    int requestedZone;
    int allocatedZone;
    RequestState state;

public:
    ParkingRequest(int vId, int zId);

    int getRequestedZone() const;
    void setAllocatedZone(int zone);
    int getAllocatedZone() const;
    
    RequestState getState() const;
    void setState(RequestState s);
    bool canCancel() const;
};

#endif