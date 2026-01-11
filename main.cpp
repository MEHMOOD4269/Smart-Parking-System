#include <iostream>
#include "Vehicle.h"
#include "ParkingRequest.h"
#include "AllocationEngine.h"
#include "RollbackManager.h"
#include "Zone.h"

using namespace std;

int main() {

    // --- SYSTEM SETUP ---
    const int ZONE_COUNT = 2;
    Zone zones[ZONE_COUNT] = {
        Zone(1, 1),
        Zone(2, 1)
    };

    AllocationEngine allocator;
    RollbackManager rollbackManager;

    Vehicle* vehicles[10];
    ParkingRequest* requests[10];
    int vehicleCount = 0;
    int requestCount = 0;

    int completedRequests = 0;
    int cancelledRequests = 0;

    int choice;

    // --- MENU LOOP ---
    do {
        cout << "\n===== SMART PARKING SYSTEM =====\n";
        cout << "1. Create Vehicle\n";
        cout << "2. Request Parking\n";
        cout << "3. Cancel Parking Request\n";
        cout << "4. Rollback Last Allocation\n";
        cout << "5. View Analytics\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            int vId, zone;
            cout << "Enter Vehicle ID: ";
            cin >> vId;
            cout << "Enter Preferred Zone: ";
            cin >> zone;

            vehicles[vehicleCount++] = new Vehicle(vId, zone);
            cout << "Vehicle created successfully.\n";
            break;
        }

        case 2: {
            if (vehicleCount == 0) {
                cout << "No vehicles available.\n";
                break;
            }

            int vIndex;
            cout << "Enter Vehicle Index (0 to " << vehicleCount - 1 << "): ";
            cin >> vIndex;

            ParkingRequest* req =
                new ParkingRequest(vIndex, vehicles[vIndex]->getPreferredZone());

            ParkingSlot* slot = allocator.allocate(zones, ZONE_COUNT, *req);

            if (slot != nullptr) {
                rollbackManager.record(slot);
                req->changeState(OCCUPIED);
                completedRequests++;
                cout << "Parking allocated successfully.\n";
            } else {
                cout << "No parking slot available.\n";
            }

            requests[requestCount++] = req;
            break;
        }

        case 3: {
            if (requestCount == 0) {
                cout << "No requests to cancel.\n";
                break;
            }

            int rIndex;
            cout << "Enter Request Index (0 to " << requestCount - 1 << "): ";
            cin >> rIndex;

            if (requests[rIndex]->changeState(CANCELLED)) {
                cancelledRequests++;
                cout << "Request cancelled successfully.\n";
            } else {
                cout << "Invalid cancellation.\n";
            }
            break;
        }

        case 4: {
            rollbackManager.rollback();
            cout << "Last allocation rolled back.\n";
            break;
        }

        case 5: {
            cout << "\n--- ANALYTICS ---\n";
            cout << "Completed Requests: " << completedRequests << endl;
            cout << "Cancelled Requests: " << cancelledRequests << endl;
            break;
        }

        case 6:
            cout << "Exiting system...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
