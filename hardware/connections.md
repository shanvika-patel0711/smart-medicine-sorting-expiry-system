# Hardware connections

| Component | Arduino UNO pin |
|---|---:|
| DISPENSE push button | D6 |
| NEXT push button | D8 |
| Buzzer | D7 |
| Green LED — slot 0 | D10 |
| Red LED — slot 0 | D11 |
| Green LED — slot 1 | D12 |
| Red LED — slot 1 | D13 |
| Green LED — slot 2 | D4 |
| Red LED — slot 2 | D5 |
| Green LED — slot 3 | D2 |
| Red LED — slot 3 | D3 |
| White power LED | A4 |

## Wiring notes

- The push buttons use the Arduino `INPUT_PULLUP` configuration and connect the input pin to GND when pressed.
- Connect each LED through a 220-ohm current-limiting resistor as documented in the academic report.
- Connect the buzzer signal to D7 and its other terminal to GND, observing the polarity of the component if marked.
- Ensure the Arduino and circuit share a common GND.

Use the submitted project report's hardware pin configuration and circuit photograph as the reference for the assembled prototype.
