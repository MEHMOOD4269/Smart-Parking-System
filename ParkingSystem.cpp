#include "ParkingSystem.h"
#include <iostream>
using namespace std;

ParkingSystem::ParkingSystem() : zones(nullptr), zoneCount(5), requestCount(0) {
    zones = new Zone[zoneCount];
    for (int i = 0; i < zoneCount; i++) zones[i].setup(i);
}

ParkingSystem::~ParkingSystem() {
    if (zones) delete[] zones;
    for(int i=0; i<requestCount; i++) delete requests[i];
}

// 1. DUPLICATE CHECK (Sirf 1 Area Check Karega -> No Repeats)
bool ParkingSystem::isVehicleAlreadyParked(int vid) {
    for(int z=0; z<zoneCount; z++) {
        // FIX: a < 1 (Sirf Pehla Area taake repeat na ho)
        for(int a=0; a<1; a++) {
            ParkingSlot* s = zones[z].getAreas()[a].getSlots();
            // FIX: k < 4 (Sirf 4 slots)
            for(int k=0; k<4; k++) {
                if(s[k].isOccupied() && s[k].getVehicleId() == vid) return true;
            }
        }
    }
    return false;
}

// 2. SHOW AVAILABLE SLOTS (Fix: No Repeats, Limit 4)
QString ParkingSystem::checkAvailableSlots(int zid) {
    if (zid < 0 || zid >= zoneCount) return "Invalid Zone!";

    QString list = "Available Slots in Zone " + QString::number(zid) + ":\n";
    bool found = false;

    // FIX: Sirf Area 0 check karein
    for(int a=0; a<1; a++) {
        ParkingSlot* s = zones[zid].getAreas()[a].getSlots();
        // FIX: Limit 4
        for(int k=0; k<4; k++) {
            if(!s[k].isOccupied()) {
                list += "[Slot " + QString::number(k) + "] ";
                found = true;
            }
        }
    }

    if(!found) return "No Slots Available in Zone " + QString::number(zid);
    return list;
}

// 3. MANUAL BOOKING
QString ParkingSystem::bookManualGUI(int vid, int zid, int slotId) {
    if (isVehicleAlreadyParked(vid)) return "⚠ REJECTED: Vehicle " + QString::number(vid) + " is already parked!";

    if (slotId < 0 || slotId > 3) return "Invalid Slot ID (0-3 only)!";

    // FIX: Sirf Area 0 mein book karein
    for(int a=0; a<1; a++) {
        ParkingSlot* s = zones[zid].getAreas()[a].getSlots();

        if (s[slotId].getSlotId() == slotId) {
            if (!s[slotId].isOccupied()) {
                requests[requestCount] = new ParkingRequest(vid, zid);
                analytics.recordRequest();

                s[slotId].occupy(vid);

                analytics.recordAllocation(zid, false);
                requestCount++;
                return "✔ SUCCESS! Booked Slot " + QString::number(slotId) + " for Vehicle " + QString::number(vid);
            } else {
                return "⚠ Slot " + QString::number(slotId) + " is already OCCUPIED!";
            }
        }
    }
    return "Error locating slot.";
}

// 4. DEPART (Departure Logic)
QString ParkingSystem::leaveVehicleGUI(int vid) {
    for(int z=0; z<zoneCount; z++) {
        // FIX: Sirf Area 0 check
        for(int a=0; a<1; a++) {
            ParkingSlot* s = zones[z].getAreas()[a].getSlots();
            // FIX: Limit 4
            for(int k=0; k<4; k++) {
                if(s[k].isOccupied() && s[k].getVehicleId() == vid) {
                    s[k].release();
                    return "Vehicle " + QString::number(vid) + " Left Zone " + QString::number(z);
                }
            }
        }
    }
    return "Vehicle NOT FOUND!";
}

// 5. ROLLBACK (Ye Function Missing Tha - Ab Added Hai)
QString ParkingSystem::rollbackGUI() {
    rollbackManager.rollback();
    analytics.recordRollback();
    return "↺ Last Action Undone (Rollback Successful)";
}

// 6. ANALYTICS
QString ParkingSystem::getAnalyticsGUI() {
    return "Total Requests: " + QString::number(analytics.getTotalRequests()) +
           "\nActive Cars: " + QString::number(analytics.getSuccessfulAllocations() - analytics.getCancellations());
}

// Console Functions (Empty implementations)
void ParkingSystem::run() {}
void ParkingSystem::showMainMenu() {}
void ParkingSystem::handleRequestParking() {}
void ParkingSystem::handleCancel() {}
void ParkingSystem::handleRollback() {}
