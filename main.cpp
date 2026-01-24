#include <iostream>
#include "ParkingSystem.h"
using namespace std;

int main() {
    Zone zones[2] = { Zone(1), Zone(2) };
    ParkingSystem system(zones, 2);

    int choice;
    do {
        system.showMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: system.handleCreateVehicle(); break;
            case 2: system.handleParkingRequest(); break;
            case 3: system.handleCancel(); break;
            case 4: system.handleRollback(); break;
            case 5: system.showAnalytics(); break;
            case 0: cout << "Thank you for using the system.\n"; break;
            default: cout << "Invalid selection. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
