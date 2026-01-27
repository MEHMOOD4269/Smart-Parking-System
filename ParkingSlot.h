#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

class ParkingSlot {
private:
    int slotId;
    int zoneId;
    bool occupied = false; // Forced Initialization

public:
    ParkingSlot();
    void setup(int sId, int zId);
    bool isOccupied() const;
    void occupy();
    void release();
    int getSlotId() const;
    int getZoneId() const;
};

#endif