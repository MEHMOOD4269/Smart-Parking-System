#include "AllocationEngine.h"
#include "ParkingSlot.h"    
#include "ParkingArea.h"   

ParkingSlot* AllocationEngine::allocate(Zone* zones, int zoneCount, ParkingRequest& request) {
    
    // Try preferred zone first
    for (int i = 0; i < zoneCount; i++) {
        ParkingArea* areas = zones[i].getAreas();
        ParkingSlot* slot = areas[0].getAvailableSlot();

        if (slot != nullptr) {
            slot->occupy();
            request.changeState(ALLOCATED);
            return slot;
        }
    }

    return nullptr; // no slot found
}
