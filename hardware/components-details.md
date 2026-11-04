
# SMSES – Hardware Components Documentation

## 1. Arduino UNO

Arduino UNO acts as the main controller of the Smart Medicine Sorting & Expiry Alert System.

It processes medicine records, performs data structure operations, and controls the connected hardware components.

## 2. LEDs

The prototype uses nine LEDs.

| LED | Quantity | Purpose |
|---|---:|---|
| Green LED | 4 | Indicates occupied medicine slots |
| Red LED | 4 | Identifies the highest-priority medicine slot |
| White LED | 1 | Indicates power status |

## 3. Buzzer

A buzzer provides audio feedback during supported operations and simulated alert demonstrations.

## 4. Push Buttons

Two push buttons are used.

| Button | Arduino Pin | Function |
|---|---|---|
| DISPENSE | D6 | Removes the highest-priority record from logical inventory |
| NEXT | D8 | Navigates between occupied slots |

## 5. Breadboard and Jumper Wires

The breadboard and jumper wires connect the Arduino UNO to the LEDs, buzzer, and push buttons.

## 6. Medicine Storage Tray

A four-slot medicine tray provides physical compartments for organising medicine packages.

## 7. Component Summary

| Component | Quantity |
|---|---:|
| Arduino UNO | 1 |
| Green LEDs | 4 |
| Red LEDs | 4 |
| White LED | 1 |
| Buzzer | 1 |
| Push Buttons | 2 |
| Breadboard | 1 |
| Jumper Wires | As required |
| Medicine Tray | 1 |

## 8. Conclusion

These hardware components form the physical implementation of SMSES. Together with the Arduino program and data structures, they demonstrate an embedded medicine inventory management prototype.
