#include "Zone.h"

Zone::Zone() : zoneId(-1) {}

void Zone::setup(int id) {
    zoneId = id;
    for(int i = 0; i < 2; i++) {
        areas[i].setup(i, zoneId);
    }
}

void Zone::addAdjacentZone(int zId) {
    if (adjacentCount < 10) adjacentZones[adjacentCount++] = zId;
}

int Zone::getZoneId() const { return zoneId; }
ParkingArea* Zone::getAreas() { return areas; }
int Zone::getAreaCount() const { return 2; }