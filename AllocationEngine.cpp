#include "AllocationEngine.h"
#include "ParkingSlot.h"    
#include "ParkingArea.h"
#include <iostream>
using namespace std;   

ParkingSlot* AllocationEngine::allocate(Zone* zones, int zoneCount, ParkingRequest& request) {
    
    // Validate state before allocation
    if (!request.canAllocate()) {
        cout << "Invalid state: cannot allocate\n";
        return nullptr;
    }
    
    // Try preferred zone first
    for (int i = 0; i < zoneCount; i++) {
        ParkingArea* areas = zones[i].getAreas();
        ParkingSlot* slot = areas[0].getAvailableSlot();

        if (slot != nullptr) {
            slot->occupy();
            request.changeState(ALLOCATED);
            request.setAllocatedZone(zones[i].getZoneId());
            return slot;
        }
    }

    return nullptr; // no slot found
}
