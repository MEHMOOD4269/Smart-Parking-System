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
    int requestedZone;
    int allocatedZone;
    int requestTime;
    int releaseTime;
    RequestState state;

public:
    ParkingRequest(int vid, int zone, int time);

    bool canAllocate() const;
    bool canOccupy() const;
    bool canRelease() const;
    bool canCancel() const;

    void setAllocatedZone(int zone);
    int getAllocatedZone() const;
    int getRequestedZone() const;
    bool canTransition(RequestState next) const;

    int getRequestTime() const;
    void setReleaseTime(int time);
    int getReleaseTime() const;
    int getDuration() const;

    RequestState getState() const;
    void setState(RequestState s);
};

#endif

