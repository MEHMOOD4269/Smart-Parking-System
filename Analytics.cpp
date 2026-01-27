#include "Analytics.h"

Analytics::Analytics() {
    totalRequests = 0;
    successfulAllocations = 0;
    crossZoneAllocations = 0;
    cancellations = 0;
    rollbacks = 0;

    // Array initialization
    for(int i=0; i<10; i++) zoneAllocations[i] = 0;
}

void Analytics::recordRequest() {
    totalRequests++;
}

void Analytics::recordAllocation(int zoneId, bool isCrossZone) {
    successfulAllocations++;
    if (isCrossZone) crossZoneAllocations++;

    // Zone tracking
    if(zoneId >= 0 && zoneId < 10) {
        zoneAllocations[zoneId]++;
    }
}

void Analytics::recordCancellation() {
    cancellations++;
}

void Analytics::recordRollback() {
    rollbacks++;
}

// FIX: Removed 'const' to match header
void Analytics::display() {
    cout << "\n=== ANALYTICS ===\n";
    cout << "Total Requests: " << totalRequests << endl;
    cout << "Allocations: " << successfulAllocations << endl;
    cout << "Cross-Zone: " << crossZoneAllocations << endl;
    cout << "Cancellations: " << cancellations << endl;
}
