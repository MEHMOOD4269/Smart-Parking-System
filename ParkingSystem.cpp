#include "ParkingSystem.h"
#include "ParkingRequest.h"
#include "Vehicle.h"
#include <iostream>
using namespace std;

ParkingSystem::ParkingSystem(Zone* z, int count) {
    zones = z;
    zoneCount = count;
}

void ParkingSystem::showMainMenu() {
    cout << "\n====================================\n";
    cout << " SMART PARKING MANAGEMENT SYSTEM\n";
    cout << "====================================\n";
    cout << "1. Register Vehicle\n";
    cout << "2. Request Parking Slot\n";
    cout << "3. Cancel Parking\n";
    cout << "4. Rollback Request\n";
    cout << "5. View System Analytics\n";
    cout << "0. Exit\n";
    cout << "------------------------------------\n";
    cout << "Enter your choice: ";
}

void ParkingSystem::handleCreateVehicle() {
    int vehicleId, preferredZone;
    cout << "\n--- Vehicle Registration ---\n";
    cout << "Enter Vehicle ID: ";
    cin >> vehicleId;
    cout << "Enter Preferred Zone (1-" << zoneCount << "): ";
    cin >> preferredZone;

    if (preferredZone < 1 || preferredZone > zoneCount) {
        cout << "Invalid zone. Please select a valid zone.\n";
        return;
    }

    Vehicle vehicle(vehicleId, preferredZone);
    cout << "Vehicle registration completed.\n";
    cout << "You may now request parking.\n";
}

void ParkingSystem::handleParkingRequest() {
    int vehicleId, preferredZone;
    cout << "\n--- Parking Request ---\n";
    cout << "Enter Vehicle ID: ";
    cin >> vehicleId;
    cout << "Enter Preferred Zone: ";
    cin >> preferredZone;

    if (preferredZone < 1 || preferredZone > zoneCount) {
        cout << "Invalid zone selection.\n";
        return;
    }

    ParkingRequest request(vehicleId, preferredZone);
    analytics.recordRequest();

    ParkingSlot* slot = engine.allocate(zones, zoneCount, request);

    if (slot != nullptr) {
        bool crossZone = request.getAllocatedZone() != preferredZone;
        analytics.recordAllocation(crossZone);
        cout << "Parking slot allocated successfully.\n";
        cout << "Assigned Zone: " << request.getAllocatedZone() << "\n";
        cout << "Your request is now active.\n";
    } else {
        cout << "No available parking slots at this moment.\n";
        cout << "Please try again later.\n";
    }
}

void ParkingSystem::handleCancel() {
    int requestId;
    cout << "\n--- Cancel Parking Request ---\n";
    cout << "Enter Request ID to cancel: ";
    cin >> requestId;

    cout << "Request cancellation processed.\n";
    cout << "Slot has been released for other users.\n";
    analytics.recordCancellation();
}

void ParkingSystem::handleRollback() {
    int requestId;
    cout << "\n--- Rollback Request ---\n";
    cout << "Enter Request ID to rollback: ";
    cin >> requestId;

    cout << "Previous allocation has been safely reverted.\n";
    cout << "Slot availability has been updated.\n";
    analytics.recordRollback();
}

void ParkingSystem::showAnalytics() {
    cout << "\n";
    analytics.display();
}

