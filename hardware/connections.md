
# SMSES – Circuit Connections

## 1. Introduction

This document describes the hardware connections used in the Smart Medicine Sorting & Expiry Alert System (SMSES).

The Arduino UNO acts as the main controller and interfaces with LEDs, a buzzer, and two push buttons.

## 2. Pin Configuration

| Component | Arduino Pin |
|---|---|
| DISPENSE Button | D6 |
| NEXT Button | D8 |
| Buzzer | D7 |
| Green LED – Slot 0 | D10 |
| Red LED – Slot 0 | D11 |
| Green LED – Slot 1 | D12 |
| Red LED – Slot 1 | D13 |
| Green LED – Slot 2 | D4 |
| Red LED – Slot 2 | D5 |
| Green LED – Slot 3 | D2 |
| Red LED – Slot 3 | D3 |
| White Power LED | A4 |

## 3. LED Connections

The prototype uses four green LEDs, four red LEDs, and one white LED.

- Each green LED is connected to its assigned digital output pin.
- Each red LED is connected to its assigned digital output pin.
- The white LED is connected to analog pin A4, configured as a digital output.
- Each LED requires a suitable current-limiting resistor.
- LED ground connections are connected to Arduino GND.

## 4. Push Button Connections

Two push buttons are used for system interaction.

### DISPENSE Button

- Signal connection: Arduino D6.
- Other terminal: GND.
- Configured using INPUT_PULLUP.

### NEXT Button

- Signal connection: Arduino D8.
- Other terminal: GND.
- Configured using INPUT_PULLUP.

## 5. Buzzer Connection

The buzzer provides audio feedback.

- Signal connection: Arduino D7.
- Ground connection: Arduino GND.

Check the buzzer's electrical specifications before connecting it directly to the Arduino.

## 6. Power and Ground Connections

- Arduino UNO receives power through its USB connection.
- The breadboard provides convenient component connections.
- All circuit components share a common ground.
- Suitable resistors are used for LED current limiting.

## 7. Hardware Connection Summary

| Hardware Component | Quantity | Connection |
|---|---:|---|
| Arduino UNO | 1 | Main controller |
| Green LEDs | 4 | D10, D12, D4, D2 |
| Red LEDs | 4 | D11, D13, D5, D3 |
| White LED | 1 | A4 |
| Buzzer | 1 | D7 |
| DISPENSE Button | 1 | D6 and GND |
| NEXT Button | 1 | D8 and GND |
| Breadboard | 1 | Circuit assembly |
| Jumper Wires | As required | Component connections |

## 8. Conclusion

The circuit connections integrate the Arduino UNO with the visual indicators, audio feedback, and user input buttons.

These connections support the hardware operations of the SMSES prototype, including slot indication, circular navigation, and logical inventory removal.

Refer to the main README.md for the complete project overview and implementation details.
