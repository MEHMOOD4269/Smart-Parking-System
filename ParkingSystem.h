#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <QString>
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
    ParkingSystem();
    ~ParkingSystem();

    // --- CHECK & BOOK MANUAL ---
    bool isVehicleAlreadyParked(int vid);
    QString checkAvailableSlots(int zid);
    QString bookManualGUI(int vid, int zid, int slotId);

    // --- DEPART & ANALYTICS ---
    QString leaveVehicleGUI(int vid);
    QString getAnalyticsGUI();

    // --- ROLLBACK (Ye Line Missing Thi) ---
    QString rollbackGUI();

    // Console Functions (Ignored)
    void run();
    void showMainMenu();
    void handleRequestParking();
    void handleCancel();
    void handleRollback();
};

#endif
