#include "AllocationEngine.h"
#include "Zone.h"
#include "ParkingArea.h"
#include "ParkingSlot.h"
#include "ParkingRequest.h"
#include "RollbackManager.h"
#include <iostream>

using namespace std;

ParkingSlot* AllocationEngine::allocate(Zone* zones, int zoneCount, ParkingRequest& request, RollbackManager& rollback) {
    int preferred = request.getRequestedZone();

    // 1. Try Preferred Zone
    for (int i = 0; i < zoneCount; i++) {
        if (zones[i].getZoneId() == preferred) {

            ParkingArea* areas = zones[i].getAreas();
            int areaCount = zones[i].getAreaCount();

            for (int a = 0; a < areaCount; a++) {
                ParkingSlot* slots = areas[a].getSlots();
                int slotCount = areas[a].getSlotCount();

                for (int s = 0; s < slotCount; s++) {
                    if (!slots[s].isOccupied()) {
                        // FIX: Pass Vehicle ID here
                        slots[s].occupy(request.getVehicleID());

                        request.setAllocatedZone(preferred);
                        request.setState(ALLOCATED);
                        rollback.push(&slots[s], &request);
                        return &slots[s];
                    }
                }
            }
        }
    }

    // 2. Cross Zone Fallback
    for (int i = 0; i < zoneCount; i++) {
        if (zones[i].getZoneId() != preferred) {
            ParkingArea* areas = zones[i].getAreas();
            int areaCount = zones[i].getAreaCount();

            for (int a = 0; a < areaCount; a++) {
                ParkingSlot* slots = areas[a].getSlots();
                int slotCount = areas[a].getSlotCount();

                for (int s = 0; s < slotCount; s++) {
                    if (!slots[s].isOccupied()) {
                        // FIX: Pass Vehicle ID here too
                        slots[s].occupy(request.getVehicleID());

                        request.setAllocatedZone(zones[i].getZoneId());
                        request.setState(ALLOCATED);
                        rollback.push(&slots[s], &request);
                        return &slots[s];
                    }
                }
            }
        }
    }
    return nullptr;
}
