#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H
int completedRequests;
int cancelledRequests;

class ParkingSlot {
private:
    int slotId;
    int zoneId;
    bool isAvailable;

public:
    ParkingSlot();                 // default constructor
    ParkingSlot(int id, int zone); // parameterized constructor

    bool getAvailability() const;
    void occupy();
    void release();
    int getZoneId() const;
};

#endif
