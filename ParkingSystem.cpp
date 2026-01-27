#include "ParkingSystem.h"
#include <iostream>
#include <limits>
using namespace std;

ParkingSystem::ParkingSystem() : zones(nullptr), zoneCount(5), requestCount(0) {
    cout << "--- SYSTEM STARTUP (STATIC MEMORY) ---\n";
    
    // Create the main array
    zones = new Zone[zoneCount];

    // Setup Zones (This triggers the static arrays inside)
    for (int i = 0; i < zoneCount; i++) {
        zones[i].setup(i);
    }
    
    // Self-Check to prove slots exist
    if (zones[0].getAreas()[0].getSlots()[0].isOccupied() == false) {
        cout << "[CHECK] Memory Verified: Slots are ready and free.\n";
    }

    // Adjacency
    zones[0].addAdjacentZone(1); zones[1].addAdjacentZone(0); 
    // ... add others if needed
}

// ... (Rest of functions: showMainMenu, handleCancel etc.) ...

// PASTE THIS CRITICAL FUNCTION EXACTLY:
void ParkingSystem::handleRequestParking() {
    int vid, zid;
    cout << "\n--- Parking Request ---\n";
    cout << "Enter Vehicle ID: "; cin >> vid;
    cout << "Enter Preferred Zone (0-4): "; cin >> zid;

    if (requestCount >= 100) return;

    requests[requestCount] = new ParkingRequest(vid, zid);
    analytics.recordRequest();
    
    // Call Engine
    ParkingSlot* slot = engine.allocate(zones, zoneCount, *requests[requestCount], rollbackManager);
    
    if (slot != nullptr) {
        bool cross = (slot->getZoneId() != zid);
        analytics.recordAllocation(slot->getZoneId(), cross);
        cout << "✔ SUCCESS! Allocated Slot " << slot->getSlotId() 
             << " in Zone " << slot->getZoneId() << endl;
        if (cross) cout << "(Cross-zone)\n";
    } else {
        cout << "✖ No slots available.\n";
    }
    requestCount++;
}

// Ensure you include the implementations for run(), showMainMenu(), handleCancel(), handleRollback() as well
// (You can copy those from previous steps, they don't change logic, just the memory above matters)
void ParkingSystem::showMainMenu() { cout << "\n1. Register\n2. Request\n3. Cancel\n4. Rollback\n5. Analytics\n0. Exit\nChoice: "; }
void ParkingSystem::handleCancel() { /* ... */ }
void ParkingSystem::handleRollback() { /* ... */ }
void ParkingSystem::run() {
    int choice;
    do {
        showMainMenu();
        cin >> choice;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice) {
            case 2: handleRequestParking(); break;
            case 5: analytics.display(); break;
            case 0: break;
        }
    } while(choice != 0);
}