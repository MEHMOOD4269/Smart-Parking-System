#ifndef ANALYTICS_H
#define ANALYTICS_H

class Analytics {
private:
    int totalRequests;
    int successfulAllocations;
    int crossZoneAllocations;
    int cancellations;
    int rollbacks;
    int totalDuration;
    int zoneUsage[10];  // Track requests per zone (array, no STL)
    int zoneAllocations[10];  // Successful allocations per zone

public:
    Analytics();
    void recordRequest();
    void recordAllocation(int zoneId, bool crossZone = false);
    void recordCancellation();
    void recordRollback();
    void recordDuration(int duration);
    int calculateAverageDuration() const;
    int getPeakZone() const;
    double calculateUtilization(int zoneId) const;
    void display() const;
};

#endif
