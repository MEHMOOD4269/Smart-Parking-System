#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include "Zone.h"
#include "Vehicle.h"
#include "ParkingRequest.h"
#include "AllocationEngine.h"
#include "RollbackManager.h"
#include "Analytics.h"

class ParkingSystem {
private:
    Zone* zones;
    int zoneCount;
    AllocationEngine engine;
    RollbackManager rollbackManager;
    Analytics analytics;
    
    ParkingRequest* requests[100];
    int requestCount;
    
public:
    // CHANGED: No arguments. System builds its own data.
    ParkingSystem(); 
    
    void run();
    void handleRequestParking();
    void handleCancel();
    void handleRollback();
    void showMainMenu();
};

#endif