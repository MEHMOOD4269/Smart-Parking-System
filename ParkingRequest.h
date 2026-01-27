#ifndef PARKINGREQUEST_H
#define PARKINGREQUEST_H

enum RequestState { PENDING, ALLOCATED, REJECTED, CANCELLED };

class ParkingRequest {
private:
    int vehicleId;
    int requestedZone;
    int allocatedZone;
    RequestState state;

public:
    ParkingRequest(int vId, int zoneId);

    // --- NEW: Getter for Vehicle ID ---
    int getVehicleID() const { return vehicleId; }

    int getRequestedZone() const { return requestedZone; }
    int getAllocatedZone() const { return allocatedZone; }

    void setAllocatedZone(int zId) { allocatedZone = zId; }
    void setState(RequestState s) { state = s; }
};

#endif
