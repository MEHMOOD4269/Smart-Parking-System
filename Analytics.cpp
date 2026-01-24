#include "Analytics.h"
#include <iostream>
using namespace std;

Analytics::Analytics() {
    totalRequests = successfulAllocations = crossZoneAllocations = 0;
    cancellations = rollbacks = 0;
}

void Analytics::recordRequest() {
    totalRequests++;
}

void Analytics::recordAllocation(bool crossZone) {
    successfulAllocations++;
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
