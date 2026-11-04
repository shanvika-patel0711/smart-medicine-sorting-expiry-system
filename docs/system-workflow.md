
# SMSES – System Workflow

## 1. Introduction

The Smart Medicine Sorting & Expiry Alert System (SMSES) follows a structured workflow to manage medicine records according to their expiry priority.

The system combines Arduino UNO, a Min-Heap, a Circular Doubly Linked List (CDLL), push buttons, LEDs, and a buzzer.

## 2. Overall Workflow

The system follows these major steps:

1. User enters medicine details through the Arduino Serial Monitor.
2. Arduino UNO receives and processes the input.
3. Medicine records are stored in fixed-size data structures.
4. The Min-Heap arranges records according to expiry priority.
5. The CDLL maintains circular navigation between occupied slots.
6. LEDs indicate slot occupancy and expiry priority.
7. The buzzer provides audio feedback.
8. The DISPENSE button removes the highest-priority record from logical inventory.

## 3. Step-by-Step Working

### Step 1: Medicine Data Input

The user enters medicine details through the Arduino IDE Serial Monitor.

Each record contains:

- Batch number
- Expiry date
- Medicine name

Example:

```text
BATCH:201;EXP:2025-01-05;NAME:Paracetamol
```

### Step 2: Data Processing

The Arduino UNO receives the input and processes the medicine record.

The system maintains medicine information using a fixed-size Item structure array.

### Step 3: Min-Heap Insertion

The medicine record is inserted into the Min-Heap according to its expiry value.

- The earliest-expiry record receives the highest priority.
- The root node represents the minimum expiry value.
- Heap operations maintain the priority order.

### Step 4: Slot Management

The system manages four physical medicine slots.

The slot-to-record mapping maintains the relationship between medicine records and their assigned positions.

### Step 5: Circular Slot Navigation

A Circular Doubly Linked List connects occupied slot positions.

When the user presses the NEXT button:

- The current navigation position advances.
- The next occupied slot is selected.
- Circular navigation allows movement back to the first occupied slot.

### Step 6: LED Indication

The LEDs provide visual information about the medicine slots.

| LED | Function |
|---|---|
| Green LED | Indicates an occupied slot |
| Red LED | Identifies the highest-priority slot |
| White LED | Indicates system power |

### Step 7: Audio Feedback

The buzzer provides audio feedback during supported system operations and simulated alert demonstrations.

### Step 8: Logical Dispensing

When the DISPENSE button is pressed:

- The system identifies the highest-priority medicine record.
- The record is removed from the logical inventory.
- The relevant data structures are updated.
- The remaining inventory is maintained.

This operation does not physically dispense medicine.

## 4. Data Structure Interaction

### Min-Heap

The Min-Heap manages expiry-based prioritisation.

| Operation | Time Complexity |
|---|---|
| Access minimum | O(1) |
| Insertion | O(log n) |
| Remove minimum | O(log n) |

### Circular Doubly Linked List

The CDLL supports circular navigation between occupied medicine slots.

Each node maintains links to its previous and next positions.

### Fixed-Size Arrays

Arrays and Item records maintain medicine information, heap positions, slot mappings, and linked-list connections.

## 5. Serial Monitor Commands

| Command | Description |
|---|---|
| LIST | Displays stored medicine records |
| BEEP | Tests the buzzer |
| FORCEALERT | Triggers a simulated near-expiry demonstration |

Serial communication configuration:

- Baud Rate: 115200
- Line Ending: Newline

## 6. System Workflow Summary

The complete process can be represented as:

```text
User
  |
  v
Manual Medicine Input
  |
  v
Arduino UNO
  |
  v
Medicine Record Storage
  |
  v
Expiry-Based Min-Heap
  |
  v
Priority Identification
  |
  v
Four-Slot Management
  |
  v
CDLL-Based Slot Navigation
  |
  v
LED Indicators and Buzzer
  |
  v
Logical Inventory Removal
  |
  v
Updated Medicine Inventory
```

## 7. Conclusion

The SMSES workflow demonstrates how fundamental data structures can be integrated with embedded programming to manage a small medicine inventory.

The Min-Heap handles expiry-based prioritisation, while the Circular Doubly Linked List supports circular slot navigation.

Arduino UNO coordinates the input, data processing, and hardware feedback operations.

The system is an educational prototype and is not intended for real-world medical or pharmacy use.
```
