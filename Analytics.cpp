#include "Analytics.h"
#include <iostream>
using namespace std;

Analytics::Analytics() {
    totalRequests = successfulAllocations = crossZoneAllocations = 0;
    cancellations = rollbacks = totalDuration = 0;
    for (int i = 0; i < 10; i++) {
        zoneUsage[i] = 0;
        zoneAllocations[i] = 0;
    }
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

void Analytics::recordDuration(int duration) {
    totalDuration += duration;
}

int Analytics::calculateAverageDuration() const {
    if (successfulAllocations == 0) return 0;
    return totalDuration / successfulAllocations;
}

int Analytics::getPeakZone() const {
    int peak = 0;
    int maxAllocations = zoneAllocations[0];
    for (int i = 1; i < 10; i++) {
        if (zoneAllocations[i] > maxAllocations) {
            maxAllocations = zoneAllocations[i];
            peak = i;
        }
    }
    return peak;
}

double Analytics::calculateUtilization(int zoneId) const {
    if (totalRequests == 0) return 0.0;
    if (zoneId < 0 || zoneId >= 10) return 0.0;
    return (double)zoneAllocations[zoneId] / totalRequests * 100.0;
}

void Analytics::display() const {
    cout << "\n========== ANALYTICS REPORT ==========\n";
    cout << "Total Requests: " << totalRequests << endl;
    cout << "Successful Allocations: " << successfulAllocations << endl;
    cout << "Cross-Zone Allocations: " << crossZoneAllocations << endl;
    cout << "Cancellations: " << cancellations << endl;
    cout << "Rollbacks: " << rollbacks << endl;
    
    if (successfulAllocations > 0) {
        cout << "Average Parking Duration: " << calculateAverageDuration() << " minutes\n";
        cout << "Peak Zone (by allocations): " << getPeakZone() << endl;
        cout << "\nZone-wise Allocations:\n";
        for (int i = 0; i < 10; i++) {
            if (zoneAllocations[i] > 0) {
                cout << "  Zone " << i << ": " << zoneAllocations[i] 
                     << " allocations (" << calculateUtilization(i) << "%)\n";
            }
        }
    }
    
    cout << "======================================\n";
}
