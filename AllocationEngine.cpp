#include "AllocationEngine.h"
#include "ParkingSlot.h"
#include "ParkingArea.h"
#include "Zone.h"
#include <iostream>
using namespace std;

ParkingSlot* AllocationEngine::allocate(Zone* zones, int zoneCount, ParkingRequest& request) {
    
    // Validate state before allocation
    if (!request.canAllocate()) {
        cout << "Invalid state: cannot allocate\n";
        return nullptr;
    }
    
    int preferredZone = request.getRequestedZone();
    ParkingSlot* slot = nullptr;
    int allocatedZoneId = -1;
    bool crossZone = false;
    
    // STRATEGY 1: Try SAME-ZONE first (preferred zone)
    if (preferredZone >= 0 && preferredZone < zoneCount) {
        ParkingArea* areas = zones[preferredZone].getAreas();
        if (areas != nullptr) {
            slot = areas[0].getAvailableSlot();
            if (slot != nullptr) {
                allocatedZoneId = zones[preferredZone].getZoneId();
            }
        }
    }
    
    // STRATEGY 2: Try ADJACENT zones if same-zone not available
    if (slot == nullptr) {
        int* adjacentZones = zones[preferredZone].getAdjacentZones();
        int adjacentCount = zones[preferredZone].getAdjacentCount();
        
        for (int i = 0; i < adjacentCount; i++) {
            int adjZoneId = adjacentZones[i];
            for (int j = 0; j < zoneCount; j++) {
                if (zones[j].getZoneId() == adjZoneId) {
                    ParkingArea* areas = zones[j].getAreas();
                    if (areas != nullptr) {
                        slot = areas[0].getAvailableSlot();
                        if (slot != nullptr) {
                            allocatedZoneId = zones[j].getZoneId();
                            crossZone = true;
                            break;
                        }
                    }
                }
            }
            if (slot != nullptr) break;
        }
    }
    
    // STRATEGY 3: Try REMAINING zones if adjacent not available
    if (slot == nullptr) {
        for (int i = 0; i < zoneCount; i++) {
            if (zones[i].getZoneId() != preferredZone) {
                ParkingArea* areas = zones[i].getAreas();
                if (areas != nullptr) {
                    slot = areas[0].getAvailableSlot();
                    if (slot != nullptr) {
                        allocatedZoneId = zones[i].getZoneId();
                        crossZone = true;
                        break;
                    }
                }
            }
        }
    }
    
    // If slot found, update request state and return
    if (slot != nullptr) {
        slot->occupy();
        request.setState(ALLOCATED);
        request.setAllocatedZone(allocatedZoneId);
        return slot;
    }
    
    return nullptr; // No slot available in any zone
}
