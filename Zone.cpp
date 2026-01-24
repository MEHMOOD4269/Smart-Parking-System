#include "Zone.h"
#include "ParkingArea.h"

Zone::Zone(int id) : zoneId(id), areaCount(0) {
    areas = nullptr;
}

Zone::Zone(int id, int count) : zoneId(id), areaCount(count) {
    areas = new ParkingArea[areaCount];
}

Zone::~Zone() {
    delete[] areas;
}

ParkingArea* Zone::getAreas() {
    return areas;
}

int Zone::getZoneId() const {
    return zoneId;
}
