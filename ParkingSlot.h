#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

class ParkingSlot {
private:
    int slotId;
    int zoneId;
    int areaId;
    bool occupied;
    int vehicleId; // NEW: Gari ka number yaad rakhne ke liye

public:
    ParkingSlot();
    void setup(int zId, int aId, int sId);

    int getSlotId();
    int getZoneId();
    bool isOccupied();
    int getVehicleId(); // NEW: Getter

    void occupy(int vId); // NEW: Ab ye ID bhi lega
    void release();
};
#endif
