#include <iostream>
#include <vector>
#include <limits>

#include "Vehicle.h"
#include "ParkingRequest.h"
#include "AllocationEngine.h"
#include "RollbackManager.h"
#include "Analytics.h"
#include "Zone.h"

using namespace std;

// Global (simple & acceptable for course)
vector<Vehicle> vehicles;
vector<ParkingRequest> requests;
Analytics analytics;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void showHeader() {
    cout << "=========================================\n";
    cout << "        SMART PARKING SYSTEM\n";
    cout << "=========================================\n\n";
}

void createVehicle() {
    int id;
    cout << "Enter Vehicle ID: ";
    cin >> id;

    vehicles.emplace_back(id);
    cout << "✔ Vehicle created successfully\n";
}

void requestParking(Zone* zones, int zoneCount, AllocationEngine& engine) {
    int vehicleId, zoneId;

    cout << "Enter Vehicle ID: ";
    cin >> vehicleId;

    cout << "Enter Preferred Zone: ";
    cin >> zoneId;

    ParkingRequest req(vehicleId, zoneId);
    analytics.recordRequest();

    ParkingSlot* slot = engine.allocate(zones, zoneCount, req);

    if (slot) {
        bool crossZone = req.getAllocatedZone() != zoneId;
        analytics.recordAllocation(crossZone);

        cout << "✔ Parking allocated in Zone "
             << req.getAllocatedZone() << "\n";
        requests.push_back(req);
    } else {
        cout << "✖ No parking slot available\n";
    }
}

void cancelParking() {
    int id;
    cout << "Enter Request Index: ";
    cin >> id;

    if (id < 0 || id >= requests.size()) {
        cout << "✖ Invalid request ID\n";
        return;
    }

    if (!requests[id].canCancel()) {
        cout << "✖ Cannot cancel this request\n";
        return;
    }

    requests[id].changeState(CANCELLED);
    analytics.recordCancellation();
    cout << "✔ Parking cancelled\n";
}

void rollbackParking() {
    int id;
    cout << "Enter Request Index: ";
    cin >> id;

    if (id < 0 || id >= requests.size()) {
        cout << "✖ Invalid request ID\n";
        return;
    }

    if (!requests[id].canRollback()) {
        cout << "✖ Cannot rollback this request\n";
        return;
    }

    requests[id].changeState(ROLLED_BACK);
    analytics.recordRollback();
    cout << "✔ Rollback successful\n";
}

int main() {
    // Dummy setup (example)
    Zone zones[2] = { Zone(1), Zone(2) };
    AllocationEngine engine;

    int choice;

    do {
        clearScreen();
        showHeader();

        cout << "1. Create Vehicle\n";
        cout << "2. Request Parking\n";
        cout << "3. Cancel Parking\n";
        cout << "4. Rollback Parking\n";
        cout << "5. View Analytics\n";
        cout << "0. Exit\n\n";
        cout << "Enter choice: ";

        cin >> choice;

        clearScreen();
        showHeader();

        switch (choice) {
        case 1:
            createVehicle();
            break;
        case 2:
            requestParking(zones, 2, engine);
            break;
        case 3:
            cancelParking();
            break;
        case 4:
            rollbackParking();
            break;
        case 5:
            analytics.display();
            break;
        case 0:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "✖ Invalid choice\n";
        }

        pause();

    } while (choice != 0);

    return 0;
}
