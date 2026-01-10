#include "Zone.h"
#include "ParkingArea.h"

Zone::Zone(int id, int count) : zoneId(id), areaCount(count) {
    areas = new ParkingArea[areaCount];
}

ParkingArea* Zone::getAreas() {
    return areas;
}

int Zone::getZoneId() const {
    return zoneId;
}
