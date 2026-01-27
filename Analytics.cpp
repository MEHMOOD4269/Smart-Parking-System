#include "Analytics.h"
#include <iostream>
using namespace std;

Analytics::Analytics() {
    totalRequests = 0;
    successfulAllocations = 0;
    crossZoneAllocations = 0;
    cancellations = 0;
    rollbacks = 0;
    for(int i=0; i<10; i++) zoneAllocations[i] = 0;
}

void Analytics::recordRequest() {
    totalRequests++;
}

void Analytics::recordAllocation(int zoneId, bool crossZone) {
    successfulAllocations++;
    if (zoneId >= 0 && zoneId < 10) {
        zoneAllocations[zoneId]++;
    }
    if (crossZone) {
        crossZoneAllocations++;
    }
}

void Analytics::recordCancellation() {
    cancellations++;
}

void Analytics::recordRollback() {
    rollbacks++;
}

void Analytics::display() const {
    cout << "\n========== ANALYTICS REPORT ==========\n";
    cout << "Total Requests: " << totalRequests << endl;
    cout << "Successful Allocations: " << successfulAllocations << endl;
    cout << "Cross-Zone Allocations: " << crossZoneAllocations << endl;
    cout << "Cancellations: " << cancellations << endl;
    cout << "Rollbacks: " << rollbacks << endl;
    cout << "======================================\n";
}