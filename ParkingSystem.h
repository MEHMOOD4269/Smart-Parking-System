#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H

#include "Zone.h"
#include "AllocationEngine.h"
#include "RollbackManager.h"
#include "Analytics.h"
#include "ParkingRequest.h"

class ParkingSystem {
private:
    Zone* zones;
    int zoneCount;
    AllocationEngine engine;
    RollbackManager rollbackManager;
    Analytics analytics;
    int currentTime;
    ParkingRequest* requests[100];  // Array of pointers to track requests
    int requestCount;

public:
    ParkingSystem(Zone* z, int count);
    ~ParkingSystem();
    
    void run();
    void showMainMenu();
    void handleCreateVehicle();
    void handleParkingRequest();
    void handleCancel();
    void handleRollback();
    void showAnalytics();
    void advanceTime();
    
    int getCurrentTime() const { return currentTime; }
    void setCurrentTime(int time) { currentTime = time; }
};

#endif

