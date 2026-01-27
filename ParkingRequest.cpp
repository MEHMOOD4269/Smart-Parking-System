#include "ParkingRequest.h"

// Sirf Constructor yahan hoga.
// Baaki Getters/Setters header file mein hain, isliye yahan se hata diye gaye hain.

ParkingRequest::ParkingRequest(int vId, int zId)
    : vehicleId(vId), requestedZone(zId), allocatedZone(-1), state(PENDING) // FIXED: REQUESTED -> PENDING
{
}
