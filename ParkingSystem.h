#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H

#include "Zone.h"
#include "AllocationEngine.h"
#include "Analytics.h"

class ParkingSystem {
private:
    Zone* zones;
    int zoneCount;
    AllocationEngine engine;
    Analytics analytics;

public:
    ParkingSystem(Zone* z, int count);
    void showMainMenu();
    void handleCreateVehicle();
    void handleParkingRequest();
    void handleCancel();
    void handleRollback();
    void showAnalytics();
};

#endif

