#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

class ParkingSlot {
private:
    int slotId;
    int zoneId;
    bool isAvailable;

public:
    ParkingSlot(int id, int zone);
    bool getAvailability() const;
    void occupy();
    void release();
    int getZoneId() const;
};

#endif

