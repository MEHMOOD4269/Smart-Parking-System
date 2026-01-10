# Design Overview

# Data Structures
- Arrays for zones and slots
- Stack for rollback

# Allocation Strategy
- Same-zone first
- Cross-zone if full

# State Machine
Strict transitions enforced in ParkingRequest class

# Rollback
Stack-based undo of last allocation

# Complexity
Allocation: O(n)
Rollback: O(1)

