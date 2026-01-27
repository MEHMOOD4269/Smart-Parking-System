#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <iostream>
using namespace std;

class Analytics {
private:
    int totalRequests;
    int successfulAllocations;
    int crossZoneAllocations;
    int cancellations;
    int rollbacks;

    // --- FIX: Ye array missing tha ---
    int zoneAllocations[10];

public:
    Analytics();

    void recordRequest();
    void recordAllocation(int zoneId, bool isCrossZone);
    void recordCancellation();
    void recordRollback();

    void display(); // Note: Yahan 'const' nahi hai

    // Getters for GUI
    int getTotalRequests() { return totalRequests; }
    int getSuccessfulAllocations() { return successfulAllocations; }
    int getCrossZoneAllocations() { return crossZoneAllocations; }
    int getCancellations() { return cancellations; }
    int getRollbacks() { return rollbacks; }
};

#endif
