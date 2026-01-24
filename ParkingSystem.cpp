#include "ParkingSystem.h"
#include "ParkingRequest.h"
#include "Vehicle.h"
#include <iostream>
#include <limits>
using namespace std;

ParkingSystem::ParkingSystem(Zone* z, int count) {
    zones = z;
    zoneCount = count;
    currentTime = 0;
    requestCount = 0;
    for (int i = 0; i < 100; i++) {
        requests[i] = nullptr;
    }
}

ParkingSystem::~ParkingSystem() {
    for (int i = 0; i < requestCount; i++) {
        if (requests[i] != nullptr) {
            delete requests[i];
        }
    }
}

void ParkingSystem::run() {
    int choice;
    while (true) {
        showMainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                handleCreateVehicle();
                break;
            case 2:
                handleParkingRequest();
                break;
            case 3:
                handleCancel();
                break;
            case 4:
                handleRollback();
                break;
            case 5:
                showAnalytics();
                break;
            case 0:
                cout << "\nThank you for using Smart Parking System. Goodbye!\n";
                return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void ParkingSystem::showMainMenu() {
    cout << "\n====================================\n";
    cout << " SMART PARKING MANAGEMENT SYSTEM\n";
    cout << " Time: " << currentTime << " min\n";
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
    int vehicleId;

    cout << "\n--- Vehicle Registration ---\n";
    cout << "Enter Vehicle ID: ";
    cin >> vehicleId;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nVehicle registration completed successfully.\n";
    cout << "You may now request a parking slot.\n";

    cout << "\nPress ENTER to return to main menu...";
    cin.get();
}

void ParkingSystem::handleParkingRequest() {
    int vehicleId, zoneId;

    cout << "\n--- Parking Slot Request ---\n";

    cout << "Enter Vehicle ID: ";
    cin >> vehicleId;

    cout << "Enter Preferred Zone (0-" << (zoneCount-1) << "): ";
    cin >> zoneId;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (zoneId < 0 || zoneId >= zoneCount) {
        cout << "\nInvalid zone selection.\n";
        cout << "\nPress ENTER to return to main menu...";
        cin.get();
        return;
    }

    // Create parking request with current time
    ParkingRequest* request = new ParkingRequest(vehicleId, zoneId, currentTime);
    if (requestCount < 100) {
        requests[requestCount++] = request;
    }
    
    analytics.recordRequest();

    ParkingSlot* slot = engine.allocate(zones, zoneCount, *request);

    if (slot != nullptr) {
        bool crossZone = request->getAllocatedZone() != zoneId;
        analytics.recordAllocation(request->getAllocatedZone(), crossZone);

        cout << "\nParking slot allocated successfully.\n";
        cout << "Allocated Zone: " << request->getAllocatedZone() << "\n";
        cout << "Request Time: " << currentTime << " minutes\n";
    } else {
        cout << "\nNo parking slots available at the moment.\n";
    }

    cout << "\nPress ENTER to return to main menu...";
    cin.get();
}

void ParkingSystem::handleCancel() {
    int requestId;
    cout << "\n--- Cancel Parking Request ---\n";
    cout << "Enter Request ID to cancel (0-" << (requestCount-1) << "): ";
    cin >> requestId;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (requestId < 0 || requestId >= requestCount || requests[requestId] == nullptr) {
        cout << "\nInvalid request ID.\n";
    } else if (!requests[requestId]->canCancel()) {
        cout << "\nCannot cancel request in current state.\n";
    } else {
        requests[requestId]->setState(CANCELLED);
        cout << "\nRequest cancellation processed.\n";
        cout << "Slot has been released for other users.\n";
        analytics.recordCancellation();
    }

    cout << "\nPress ENTER to return to main menu...";
    cin.get();
}

void ParkingSystem::handleRollback() {
    cout << "\n--- Rollback Last Allocation ---\n";
    
    if (rollbackManager.isEmpty()) {
        cout << "\nNo allocations to rollback.\n";
    } else {
        rollbackManager.rollback();
        cout << "\nPrevious allocation has been safely reverted.\n";
        cout << "Slot availability has been updated.\n";
        analytics.recordRollback();
    }

    cout << "\nPress ENTER to return to main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ParkingSystem::showAnalytics() {
    cout << "\n";
    analytics.display();

    cout << "\nPress ENTER to return to main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ParkingSystem::advanceTime() {
    currentTime += 5;  // Advance by 5 minutes
}

