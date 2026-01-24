#ifndef ZONE_H
#define ZONE_H

class ParkingArea;   
class Zone {
private:
    int zoneId;
    ParkingArea* areas;
    int areaCount;

public:
    Zone(int id);
    Zone(int id, int count);
    ~Zone();
    ParkingArea* getAreas();
    int getZoneId() const;
};

#endif

