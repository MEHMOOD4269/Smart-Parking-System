#include "Zone.h"
#include "ParkingArea.h"

Zone::Zone(int id) : zoneId(id), areaCount(0), adjacentCount(0) {
    areas = nullptr;
}

Zone::Zone(int id, int count) : zoneId(id), areaCount(count), adjacentCount(0) {
    areas = new ParkingArea[areaCount];
}

Zone::~Zone() {
    delete[] areas;
}

int Zone::getZoneId() const {
    return zoneId;
}

ParkingArea* Zone::getAreas() {
    return areas;
}

int Zone::getAreaCount() const {
    return areaCount;
}

void Zone::addAdjacentZone(int id) {
    if (adjacentCount < 5) {
        adjacentZones[adjacentCount++] = id;
    }
}

int* Zone::getAdjacentZones() {
    return adjacentZones;
}

int Zone::getAdjacentCount() const {
    return adjacentCount;
}
