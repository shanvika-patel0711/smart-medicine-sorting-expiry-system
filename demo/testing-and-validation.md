
# SMSES – Testing and Validation

## 1. Testing Overview

The Smart Medicine Sorting & Expiry Alert System (SMSES) is tested to verify its medicine record management, expiry-based prioritisation, slot navigation, and hardware feedback.

The testing process focuses on the implemented Arduino UNO prototype and its Min-Heap and Circular Doubly Linked List operations.

## 2. Testing Environment

| Parameter | Details |
|---|---|
| Microcontroller | Arduino UNO |
| Programming Language | Embedded C/C++ |
| Development Environment | Arduino IDE |
| Serial Communication | 115200 baud |
| Medicine Storage | Four physical slots |
| Priority Structure | Min-Heap |
| Navigation Structure | Circular Doubly Linked List |
| Output Components | LEDs and Buzzer |
| Input Components | Serial Monitor and Push Buttons |

## 3. Functional Test Cases

The following test cases describe the expected behaviour of the implemented prototype.

| Test ID | Test Scenario | Expected Result |
|---|---|---|
| TC01 | Enter a valid medicine record | Medicine details are accepted and stored |
| TC02 | Insert multiple medicine records | Records are organised according to expiry priority |
| TC03 | Check the Min-Heap root | The earliest-expiry record has the highest priority |
| TC04 | Press the NEXT button | Navigation moves to the next occupied slot |
| TC05 | Press the DISPENSE button | The highest-priority record is removed from logical inventory |
| TC06 | Check occupied slots | Green LEDs indicate occupied slots |
| TC07 | Check priority indication | Red LED identifies the highest-priority slot |
| TC08 | Power on the system | White LED indicates power status |
| TC09 | Enter LIST command | Stored medicine records and their status are displayed |
| TC10 | Enter BEEP command | Buzzer produces audio feedback |
| TC11 | Enter FORCEALERT command | Simulated near-expiry alert is triggered |

**Note:** These are expected results. Actual test outcomes should be recorded after performing each test on the hardware prototype.

## 4. Serial Monitor Testing

The Arduino Serial Monitor is used to enter medicine records and execute system commands.

### Sample Medicine Input

```text
BATCH:201;EXP:2025-01-05;NAME:Paracetamol
```

### Supported Commands

| Command | Function |
|---|---|
| LIST | Displays medicine inventory |
| BEEP | Tests buzzer functionality |
| FORCEALERT | Triggers the simulated near-expiry demonstration |

### Serial Monitor Configuration

- Baud Rate: 115200
- Line Ending: Newline

## 5. Data Structure Validation

### Min-Heap Validation

The Min-Heap is used to maintain medicine records according to expiry priority.

- Insertion maintains the Min-Heap property.
- The root stores the record with the smallest expiry value.
- Removal of the highest-priority record restores the heap property.

### Circular Doubly Linked List Validation

The CDLL is used for circular navigation between occupied medicine slots.

- Each occupied slot is connected through previous and next links.
- The NEXT button advances the navigation position.
- Circular links allow navigation to continue from the last occupied slot to the first.

## 6. Hardware Validation

The hardware validation focuses on the interaction between the Arduino UNO and the connected components.

| Component | Validation Purpose |
|---|---|
| Arduino UNO | Main processing and control |
| Green LEDs | Occupied slot indication |
| Red LEDs | Highest-priority slot indication |
| White LED | Power indication |
| Buzzer | Audio feedback |
| NEXT Button | Circular slot navigation |
| DISPENSE Button | Logical inventory removal |
| Breadboard | Hardware connections |

## 7. Testing Limitations

- The prototype uses four physical medicine slots.
- Medicine information is entered manually through the Serial Monitor.
- The system does not use a physical barcode scanner.
- Calendar-based expiry tracking requires a dedicated real-time clock module, which is not included in the current implementation.
- DISPENSE performs logical inventory removal rather than physical medicine dispensing.
- FORCEALERT is a simulated demonstration feature.

## 8. Conclusion

The testing and validation plan covers the core functionality of SMSES, including medicine record handling, Min-Heap prioritisation, CDLL-based slot navigation, push-button operations, and hardware feedback.

The prototype demonstrates the practical application of fundamental data structures in an Arduino-based embedded system.

SMSES is intended for academic demonstration and learning purposes only. It is not a medical or pharmacy-grade inventory management device.
