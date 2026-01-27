#ifndef ANALYTICS_H
#define ANALYTICS_H

class Analytics {
private:
    int totalRequests;
    int successfulAllocations;
    int crossZoneAllocations;
    int cancellations;
    int rollbacks;
    int zoneAllocations[10]; 

public:
    Analytics();
    void recordRequest();
    void recordAllocation(int zoneId, bool crossZone);
    void recordCancellation();
    void recordRollback();
    void display() const;
};

#endif