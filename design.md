# Smart Parking System - Design Document
## Allocation & Zone Management Architecture

**Date:** January 2026  
**Specification:** Smart Parking Allocation & Zone Management System  
**Language:** C++ (MinGW)  
**Key Paradigm:** Data Structure-centric design with strict adherence to classical algorithms

---

## 1. Zone and Slot Representation

### 1.1 Hierarchical Structure

The parking system employs a three-tier spatial hierarchy:

```
ParkingSystem (root controller)
    ↓
Zone[0..4] (5 geographic zones)
    ↓
ParkingArea[0..k] (areas within zones)
    ↓
ParkingSlot[0..m] (individual slots in areas)
```

**Zone:** Represents a distinct geographic or administrative parking region identified by a unique integer ID (0-4). Each zone maintains:
- **zoneId:** Unique identifier
- **areas:** Dynamic array of ParkingArea pointers
- **adjacentZones:** Fixed array of adjacent zone IDs
- **adjacentCount:** Current count of adjacent zones

**ParkingArea:** Encapsulates a collection of contiguous parking slots within a zone. Responsible for:
- Storing array of ParkingSlot objects
- Providing first-available-slot lookup functionality
- Managing area-level capacity and utilization

**ParkingSlot:** Atomic unit of parking allocation. Each slot maintains:
- **slotId:** Unique identifier within its area
- **isAvailable:** Boolean occupancy state
- **occupiedBy:** Vehicle ID currently occupying slot (or -1 if empty)

### 1.2 Adjacency System (Array-Based, No STL)

Zone adjacency is represented using a **fixed-size array** rather than graph structures or STL containers:

```
Zone 0: adjacentZones[5] = {1, -1, -1, -1, -1}, adjacentCount = 1
Zone 1: adjacentZones[5] = {0, 2, -1, -1, -1}, adjacentCount = 2
Zone 2: adjacentZones[5] = {1, 3, -1, -1, -1}, adjacentCount = 2
Zone 3: adjacentZones[5] = {2, 4, -1, -1, -1}, adjacentCount = 2
Zone 4: adjacentZones[5] = {3, -1, -1, -1, -1}, adjacentCount = 1
```

**Design Rationale:** 
- Fixed array size (5 elements) sufficient for typical zone configurations
- No dynamic allocation overhead; constant-time access to adjacency information
- Explicit index management prevents hidden O(log n) tree traversals
- Linear iteration through adjacencyCount maintains O(k) adjacency exploration where k << n

### 1.3 Memory Management

- **Dynamic Allocation:** Zone::areas allocated via `new[]` during zone construction
- **Deallocation:** Destructor (~Zone) explicitly calls `delete[]` to prevent memory leaks
- **Scope:** All parking slot objects allocated within parent ParkingArea; lifetime extends to system shutdown

---

## 2. Allocation Strategy

## 2. Allocation Strategy

### 2.1 Three-Tier Preference Algorithm

The allocation engine implements a three-tier preference strategy to optimize slot utilization while minimizing cross-zone movements:

#### **Tier 1: Same-Zone Allocation (O(n) search)**
**Priority:** HIGHEST  
**Process:** Iterate through zones array, locate the zone matching the customer's preferred zone ID. Perform linear search through the first available area to find an unoccupied slot.

**Pseudocode:**
```
FOR i FROM 0 TO zoneCount-1:
    IF zones[i].getZoneId() == requestedZoneId:
        slot = zones[i].getAreas()[0].getAvailableSlot()
        IF slot != NULL:
            RETURN slot (SAME-ZONE SUCCESS)
```

**Benefit:** Minimizes customer travel distance; reduces operational cost.

#### **Tier 2: Adjacent-Zone Allocation (O(k·n) search)**
**Priority:** MEDIUM  
**Process:** If same-zone allocation fails, retrieve the adjacent zones array from the preferred zone. Iterate through adjacent zone IDs and perform linear slot search in each adjacent zone.

**Pseudocode:**
```
adjacentZones[] = zones[preferredZoneIndex].getAdjacentZones()
adjacentCount = zones[preferredZoneIndex].getAdjacentCount()

FOR i FROM 0 TO adjacentCount-1:
    adjZoneId = adjacentZones[i]
    FOR j FROM 0 TO zoneCount-1:
        IF zones[j].getZoneId() == adjZoneId:
            slot = zones[j].getAreas()[0].getAvailableSlot()
            IF slot != NULL:
                RETURN slot (CROSS-ZONE: ADJACENT)
```

**Complexity:** O(k·n) where k = number of adjacent zones (~2), n = zones to check  
**Cross-Zone Flag:** Set to TRUE; analytics records as cross-zone allocation

#### **Tier 3: Global Remaining-Zone Allocation (O(n) search)**
**Priority:** LOWEST  
**Process:** If adjacent zones exhausted, iterate through all remaining zones (excluding preferred zone). Return first available slot regardless of distance.

**Pseudocode:**
```
FOR i FROM 0 TO zoneCount-1:
    IF zones[i].getZoneId() != preferredZoneId:
        slot = zones[i].getAreas()[0].getAvailableSlot()
        IF slot != NULL:
            RETURN slot (CROSS-ZONE: REMOTE)
```

**Cross-Zone Flag:** Set to TRUE

### 2.2 First-Available-Slot Logic

Within each zone, the search follows a **first-available strategy**:

1. Iterate through ParkingArea array sequentially
2. For each area, invoke getAvailableSlot() which linearly searches the slots array
3. Return immediately upon finding first slot with isAvailable == TRUE
4. No sorting or optimization applied (ensures O(n) linear time complexity)

**Trade-off:** Simple and predictable; may not optimize for spatial clustering, but acceptable for mid-sized parking facilities.

### 2.3 Rollback Integration

Upon successful allocation, the AllocationEngine registers the allocation with RollbackManager:
- **Entry Stored:** {ParkingSlot* pointer, ParkingRequest* pointer}
- **LIFO Stack:** Maintains chronological order for undo operations
- **Recovery:** Enables restoration of both slot availability and request state

---

## 3. Parking Request Lifecycle

## 3. Parking Request Lifecycle

### 3.1 State Machine Definition

The RequestState enum defines five canonical states:

| State | Value | Meaning |
|-------|-------|---------|
| REQUESTED | 0 | Initial state; request created but not yet allocated |
| ALLOCATED | 1 | Slot assigned; payment/confirmation pending |
| OCCUPIED | 2 | Vehicle physically present; active parking |
| RELEASED | 3 | Vehicle departed; session concluded |
| CANCELLED | 4 | Request terminated before completion |

### 3.2 Valid State Transitions

The state machine enforces strict, directional transitions via validation methods:

```
REQUESTED ──→ ALLOCATED (via canAllocate())
       ↓           ↓
       └───→ CANCELLED (via canCancel() from REQUESTED)
             (via canCancel() from ALLOCATED)

ALLOCATED ──→ OCCUPIED (via canOccupy())
OCCUPIED  ──→ RELEASED (via canRelease())
```

### 3.3 Transition Validation Methods

**canAllocate():** Returns TRUE if state == REQUESTED  
**canOccupy():** Returns TRUE if state == ALLOCATED  
**canRelease():** Returns TRUE if state == OCCUPIED  
**canCancel():** Returns TRUE if state ∈ {REQUESTED, ALLOCATED}

### 3.4 Invalid Transition Prevention

Attempts at invalid transitions are explicitly rejected:
- **Cancel Before Allocate:** Fails; state == REQUESTED but operation invalid in sequence
- **Cancel After Release:** Fails; state == RELEASED, not in {REQUESTED, ALLOCATED}
- **Double Allocation:** Fails; state != REQUESTED on second allocate() call
- **Occupy Without Allocation:** Fails; state != ALLOCATED

**Implementation:** Every state-modifying operation checks precondition before execution:
```
IF NOT request.canAllocate():
    PRINT "Invalid state: cannot allocate"
    RETURN NULL
```

### 3.5 Time Tracking

Each ParkingRequest maintains temporal information:
- **requestTime:** Unix-style timestamp when request created
- **releaseTime:** Timestamp when vehicle departs (set at RELEASED state)
- **getDuration():** Returns (releaseTime - requestTime) in minutes

**Purpose:** Enable analytics calculations for average parking duration and zone utilization over time.

---

## 4. Rollback Design

### 4.1 Stack-Based Undo Architecture

The RollbackManager implements a **Last-In-First-Out (LIFO) stack** data structure specifically designed for undoing parking allocations:

```
Stack Structure:
┌──────────────────────────────────────┐
│ Top → RollbackEntry[99] {slot, req}  │  ← Most Recent
│       RollbackEntry[98] {slot, req}  │
│       RollbackEntry[97] {slot, req}  │
│       ...                            │
│       RollbackEntry[0]  {slot, req}  │  ← Oldest
│ Bottom (unused)                      │
└──────────────────────────────────────┘
```

### 4.2 RollbackEntry Structure

Each stack entry contains:
```
struct RollbackEntry {
    ParkingSlot* slot;         // Pointer to affected parking slot
    ParkingRequest* request;   // Pointer to affected request
}
```

**Motivation:** Undo operation requires both:
1. Restoration of slot to available state
2. Reversion of request to REQUESTED state

Storing both pointers enables atomic rollback without searching.

### 4.3 Core Operations

**push(slot, request) → O(1)**
- Insert RollbackEntry at top of stack
- Increment stack pointer (top++)
- Check boundary: top < 99 (array capacity)

**pop() → O(1)**
- Decrement stack pointer (top--)
- Return entry at position top

**isEmpty() → O(1)**
- Check if top < 0
- Returns boolean

**rollback() → O(1)**
- Retrieve top entry via pop()
- Call slot→release() to set isAvailable = TRUE
- Call request→setState(REQUESTED) to reset state
- Decrement top

### 4.4 Support for Last-K Operations

**Sequential Rollback:** Stack naturally supports multiple consecutive rollbacks:
1. First rollback(): Undoes most recent allocation (LIFO)
2. Second rollback(): Undoes second-most recent allocation (LIFO)
3. Continues until stack empty

**Complexity:** Each rollback operation O(1); k sequential rollbacks = O(k)

**Constraint:** Maximum k limited by stack capacity (100 entries). Sufficient for typical parking session duration.

### 4.5 Integrity Guarantees

- **Atomicity:** Each rollback reverses both slot state and request state simultaneously
- **Consistency:** Stack pointer always points to valid entry or -1 (empty)
- **No Orphans:** Rolled-back requests and slots immediately available for reuse
- **Chronological Correctness:** LIFO ordering ensures reverse chronological undo (most recent first)

---

## 5. Analytics Design

### 5.1 Metric Categories

#### **Request Metrics**
- **totalRequests:** Count of all parking requests initiated
- **successfulAllocations:** Count of requests resulting in slot assignment
- **cancellations:** Count of requests cancelled before completion

#### **Zone Metrics**
- **zoneAllocations[10]:** Array tracking successful allocations per zone
- **zoneUsage[10]:** Array tracking request volume per zone
- **crossZoneAllocations:** Count of allocations outside preferred zone

#### **Temporal Metrics**
- **totalDuration:** Cumulative parking time across all sessions (in minutes)
- **rollbacks:** Count of undo operations performed

### 5.2 Calculation Methods

**Average Parking Duration → O(1) amortized**
```
calculateAverageDuration() = totalDuration / successfulAllocations
```
Requires continuous accumulation of duration at each release event.

**Zone Utilization Rate → O(1)**
```
calculateUtilization(zoneId) = (zoneAllocations[zoneId] / totalRequests) × 100%
```
Direct array lookup; constant computation.

**Peak Zone Identification → O(n) where n = 10**
```
getPeakZone():
    max = zoneAllocations[0]
    peakZone = 0
    FOR i FROM 1 TO 9:
        IF zoneAllocations[i] > max:
            max = zoneAllocations[i]
            peakZone = i
    RETURN peakZone
```

**Cancellation vs Completion Ratio → O(1)**
```
completionRate = successfulAllocations / totalRequests
cancellationRate = cancellations / totalRequests
```

### 5.3 Data Aggregation

Analytics receives events from:
1. **ParkingSystem.handleParkingRequest()** → recordRequest()
2. **AllocationEngine.allocate()** → recordAllocation(zoneId, isCrossZone)
3. **ParkingSystem.handleCancel()** → recordCancellation()
4. **RollbackManager.rollback()** → recordRollback()
5. **Release Events** → recordDuration(minutes)

### 5.4 Display Format

The display() method outputs comprehensive metrics including zone-wise breakdown, peak zone, average duration, and utilization percentages.

---

## 6. Time and Space Complexity Analysis

### 6.1 Allocation Operation

**Operation:** ParkingSlot* allocate(Zone* zones, int zoneCount, ParkingRequest& request)

| Phase | Complexity | Explanation |
|-------|-----------|-------------|
| Same-Zone Search | O(n) | Iterate through all zones; linear slot search within zone |
| Adjacent-Zone Search | O(k·n) | k adjacent zones; n zones to check each; k ≈ 2-3 |
| Remaining-Zone Search | O(n) | Iterate through all zones excluding preferred |
| **Total Worst-Case** | **O(n)** | Dominated by zone iteration; k is constant |

**Best-Case:** O(1) if preferred zone has immediate available slot  
**Average-Case:** O(n) across three tiers  
**Space:** O(1) additional space; no heap allocation during search

### 6.2 Rollback Operations

| Operation | Complexity | Space |
|-----------|-----------|-------|
| push(slot, request) | O(1) | O(1) per entry |
| pop() | O(1) | O(1) |
| rollback() | O(1) | O(1) |
| rollback() × k operations | O(k) | O(1) per operation |

**Implementation:** Direct array indexing; no traversal or search required.  
**Stack Capacity:** 100 entries → supports 100 consecutive undo operations.

### 6.3 Analytics Operations

| Operation | Complexity | Data Structure |
|-----------|-----------|-----------------|
| recordRequest() | O(1) | Simple counter increment |
| recordAllocation(zoneId, crossZone) | O(1) | Array update: zoneAllocations[zoneId]++ |
| calculateAverageDuration() | O(1) | Direct division |
| calculateUtilization(zoneId) | O(1) | Array lookup + arithmetic |
| getPeakZone() | O(n) | Linear scan of 10-element array |
| display() | O(n) | Print n zones + metrics |

**Total Analytics Overhead:** Negligible; all operations sub-linear except peak zone detection.

### 6.4 Space Complexity (System-Wide)

| Component | Space | Notes |
|-----------|-------|-------|
| Zones | O(m) | m zones × adjacency array (fixed 5) |
| ParkingAreas | O(m·a) | m zones × a areas per zone |
| ParkingSlots | O(m·a·s) | m zones × a areas × s slots per area |
| RollbackManager Stack | O(100) | Fixed-size 100-entry array |
| Analytics Arrays | O(10) | zoneAllocations[10] + zoneUsage[10] |
| Requests Array | O(100) | Pointer array to track requests |
| **Total** | **O(m·a·s)** | Dominated by slot storage |

Where:
- m = number of zones (5)
- a = areas per zone (~2-3)
- s = slots per area (~50-100)

**Realistic Total:** 5 × 2.5 × 75 ≈ 937.5 ParkingSlot objects ≈ 15KB (assuming 16 bytes per object)

---

## 7. Design Justifications

### 7.1 Why Array-Based Adjacency?

- **No STL Containers:** Fulfills DSA requirement for custom data structures
- **Cache Locality:** Fixed array enables CPU cache optimization
- **Predictable Performance:** No hidden hash collisions or tree rebalancing
- **Simplicity:** Linear iteration matches human intuition for zone proximity

### 7.2 Why LIFO Stack for Rollback?

- **Natural Fit:** Parking allocations naturally form a sequence; undoing in reverse order is intuitive
- **O(1) Operations:** Constant-time push/pop independent of allocation volume
- **No Search Required:** Unlike queue or priority queue, no need to find specific entry
- **Proven Pattern:** UNDO functionality in software universally implemented as stacks

### 7.3 Why Three-Tier Allocation?

- **Optimizes Customer Experience:** Same-zone first minimizes travel
- **Fair Load Distribution:** Cascades to adjacent, then remaining zones
- **Operational Efficiency:** Reduces cross-zone movements; lowers congestion
- **Tractable Complexity:** O(n) worst case remains linear even with fallbacks

### 7.4 Why Strict State Machine?

- **Prevents Invalid Operations:** Explicit validation prevents logical errors at runtime
- **Aids Debugging:** Clear state transitions simplify tracing and testing
- **Enables Analytics:** Request lifecycle easily tracked through state history
- **Matches Real-World Semantics:** Physical parking transitions follow the state progression

---

## 8. System Architecture Diagram

```
┌─────────────────────────────────────────────────────────┐
│                   ParkingSystem                         │
│              (MVC Controller Pattern)                   │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  Zone[5] ─────→ ParkingArea ────→ ParkingSlot[]        │
│   ├─ zoneId                                            │
│   ├─ adjacentZones[5]                                  │
│   └─ getAvailableSlot()                                │
│                                                         │
│  AllocationEngine                                       │
│   ├─ Tier 1: Same-Zone (O(n))                          │
│   ├─ Tier 2: Adjacent-Zone (O(k·n))                    │
│   └─ Tier 3: Remaining-Zone (O(n))                     │
│                                                         │
│  RollbackManager (STACK)                                │
│   ├─ RollbackEntry[100]                                │
│   ├─ push() [O(1)]                                     │
│   ├─ pop() [O(1)]                                      │
│   └─ rollback() [O(1)]                                 │
│                                                         │
│  ParkingRequest (State Machine)                         │
│   ├─ REQUESTED → ALLOCATED → OCCUPIED → RELEASED       │
│   ├─ Validation: canAllocate, canOccupy, canRelease   │
│   └─ Time tracking: requestTime, releaseTime          │
│                                                         │
│  Analytics                                              │
│   ├─ totalRequests, successfulAllocations              │
│   ├─ zoneAllocations[10]                               │
│   ├─ calculateAverageDuration() [O(1)]                 │
│   └─ getPeakZone() [O(n)]                              │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

## 9. Key Performance Characteristics

| Operation | Typical Time | Best Case | Worst Case |
|-----------|-------------|-----------|-----------|
| Allocate Slot | O(n) | O(1) | O(n) |
| Cancel Request | O(1) | O(1) | O(1) |
| Rollback Allocation | O(1) | O(1) | O(1) |
| Record Metric | O(1) | O(1) | O(1) |
| Calculate Average Duration | O(1) | O(1) | O(1) |
| Identify Peak Zone | O(n) | O(n) | O(n) |

**System Capacity:** Supports 1000+ allocations, 100 undo operations, real-time analytics on typical hardware.

---

## 10. Conclusion

The Smart Parking System's design prioritizes:

1. **Algorithmic Clarity:** Three-tier allocation with explicit fallback hierarchy
2. **DSA Fundamentals:** Stack-based rollback, array-based adjacency, state machine validation
3. **Performance Guarantees:** Worst-case O(n) allocation; O(1) rollback and cancellation
4. **Scalability:** Supports 10+ zones, 1000+ concurrent requests, 100-depth undo stack
5. **Maintainability:** Strict separation of concerns between controller (ParkingSystem), engine (AllocationEngine), and data structures (Zone, Request, Stack)

This architecture enables efficient urban parking management while remaining intellectually tractable for academic evaluation and professional deployment.

---

**Document Version:** 3.0  
**Last Updated:** January 2026  
**Compliance:** Smart Parking Allocation & Zone Management System DSA Specification

