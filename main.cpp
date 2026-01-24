#include <iostream>
#include <limits>
#include "ParkingSystem.h"
#include "Zone.h"
using namespace std;

int main() {
    // Initialize 5 zones with adjacency information
    Zone zones[5] = {
        Zone(0),
        Zone(1),
        Zone(2),
        Zone(3),
        Zone(4)
    };
    
    // Set up adjacency (zone 0 adjacent to 1, zone 1 adjacent to 0 and 2, etc.)
    zones[0].addAdjacentZone(1);
    zones[1].addAdjacentZone(0);
    zones[1].addAdjacentZone(2);
    zones[2].addAdjacentZone(1);
    zones[2].addAdjacentZone(3);
    zones[3].addAdjacentZone(2);
    zones[3].addAdjacentZone(4);
    zones[4].addAdjacentZone(3);
    
    // Create and run parking system
    ParkingSystem system(zones, 5);
    system.run();
    
    return 0;
}
