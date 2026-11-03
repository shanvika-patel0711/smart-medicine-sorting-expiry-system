
# SMSES – System Architecture

## Overall System Architecture

```mermaid
flowchart TD
    A["User"] --> B["Manual Medicine Input<br/>Arduino Serial Monitor"]
    B --> C["Arduino UNO<br/>Input Parsing"]
    C --> D["Medicine Record Storage<br/>Item Structure Array"]

    D --> E["Min-Heap<br/>Expiry-Based Prioritisation"]
    D --> F["Circular Doubly Linked List<br/>Medicine Slot Navigation"]

    E --> G["System Control Logic"]
    F --> G

    H["DISPENSE Button"] --> G
    I["NEXT Button"] --> G

    G --> J["LED Indicators"]
    G --> K["Buzzer Alerts"]

    J --> L["Four Medicine Slots"]
    K --> M["Audio Notification"]

    style C fill:#dbeafe,stroke:#2563eb,color:#111827
    style E fill:#dcfce7,stroke:#16a34a,color:#111827
    style F fill:#fef3c7,stroke:#d97706,color:#111827
```

## Architecture Explanation

1. **Manual Input:** The user enters medicine details through the Arduino Serial Monitor.
2. **Input Processing:** Arduino parses the received medicine information.
3. **Record Storage:** Medicine details are maintained in a fixed-size structure array.
4. **Min-Heap:** Maintains medicine priority based on expiry values.
5. **CDLL:** Maintains circular navigation between occupied medicine slots.
6. **Control Logic:** Processes medicine operations and button interactions.
7. **Output:** LEDs and buzzer provide visual and audio feedback.

## Design Principle

The system combines software-based data structures with hardware components to demonstrate FEFO-based medicine inventory prioritisation.
