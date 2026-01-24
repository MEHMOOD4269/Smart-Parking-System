#ifndef ZONE_H
#define ZONE_H

class ParkingArea;

class Zone {
private:
    int zoneId;
    ParkingArea* areas;
    int areaCount;

    int adjacentZones[5];
    int adjacentCount;

public:
    Zone(int id);
    Zone(int id, int count);
    ~Zone();
    
    int getZoneId() const;
    ParkingArea* getAreas();
    int getAreaCount() const;
    
    void addAdjacentZone(int id);
    int* getAdjacentZones();
    int getAdjacentCount() const;
};

#endif

