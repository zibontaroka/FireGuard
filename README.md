# FireGuard: Autonomous Fire Detection and Extinguishing System

## Overview

FireGuard is an advanced autonomous fire detection and extinguishing system designed to detect fires in multiple rooms, alert authorities, and deploy a robot to extinguish the fire. The system is divided into two main sections:

* **Section A (Control Unit)**: Responsible for fire detection, user interface, communication, and audio announcements. It uses an ESP32 to monitor fire sensors, display system status on a TFT screen, make phone calls via a SIM800L module, and play audio announcements using a DFPlayer Mini.
* **Section B (Firefighting Robot)**: A mobile robot that navigates to the fire location using RFID tags and IR sensors, communicates with Section A via ESP-NOW, and extinguishes fires using a water pump.

The system operates in a multi-room environment (Room 11, 12, 30, 31, and a refill station), providing a smart solution for fire safety.

## Features

* **Fire Detection**: Detects fires in four rooms (Room 11, 12, 30, 31) using flame sensors.
* **User Interface**: Displays system status (battery, water level, fire status) on an Adafruit ST7735 TFT display.
* **Phone Number Editing**: Allows users to edit owner and emergency numbers using a keypad with the secret code `*153#`.
* **Audio Announcements**: Plays pre-recorded messages for the owner and fire service using a DFPlayer Mini module.
* **Automated Alerts**: Automatically calls the owner and fire service via a SIM800L module when a fire is detected.
* **Robot Navigation**: Navigates to the fire location using RFID tags for room identification and IR sensors for line following.
* **ESP-NOW Communication**: Sections A and B communicate wirelessly using ESP-NOW to coordinate fire detection and response.
* **Fire Extinguishing**: The robot uses a water pump to extinguish fires and returns to the refill station (Room 0) after the task.

## System Architecture

The system consists of two main components:

1. **Section A (Control Unit)**:

   * Monitors fire sensors in four rooms.
   * Displays system status on a TFT screen.
   * Allows phone number editing via a 4x4 keypad.
   * Makes calls to the owner and fire service using a SIM800L module.
   * Plays audio announcements using a DFPlayer Mini.
   * Communicates with Section B via ESP-NOW.

2. **Section B (Firefighting Robot)**:

   * Receives fire detection commands from Section A via ESP-NOW.
   * Navigates to the target room using RFID tags and IR sensors.
   * Extinguishes the fire using a water pump.
   * Sends status updates (water level, fire status, robot state) back to Section A.

## Hardware Requirements

### Section A

* ESP32 Development Board
* Adafruit ST7735 TFT Display (1.8" SPI)
* 4x4 Keypad
* SIM800L GSM Module
* DFPlayer Mini MP3 Module
* Fire Sensors (e.g., Flame Sensors) for 4 rooms
* Buzzer
* Relay Module (for controlling external devices)
* 18650 Battery Pack (with holder)
* Jumper Wires and Breadboard/PCB

### Section B

* ESP32 Development Board
* RFID Reader Module (UART-based, e.g., RDM6300)
* IR Sensor Array (5 sensors for line following)
* TB6612FNG Motor Driver
* 2 DC Motors (with wheels for the robot chassis)
* Water Pump (for fire extinguishing)
* Servo Motor (for controlling the water pump nozzle, optional)
* LED (for feedback)
* Robot Chassis
* 18650 Battery Pack (with holder)
* Jumper Wires and Breadboard/PCB

## Pin Configuration

### Section A

| Component         | Pin(s)         |
| ----------------- | -------------- |
| **TFT Display**   |                |
| CS                | 18             |
| RST               | 21             |
| DC                | 19             |
| MOSI              | 22             |
| SCLK              | 23             |
| **Keypad**        |                |
| Row Pins          | 32, 33, 14, 13 |
| Col Pins          | 12, 5, 4, 15   |
| **Buzzer**        | 2              |
| **Fire Sensors**  |                |
| Room 11           | 34             |
| Room 12           | 35             |
| Room 30           | 36             |
| Room 31           | 39             |
| **DFPlayer Mini** |                |
| RX                | 27             |
| TX                | 26             |
| **Relay**         | 25             |
| **SIM800L**       |                |
| TX                | 16             |
| RX                | 17             |

### Section B

| Component                    | Pin(s) |
| ---------------------------- | ------ |
| **LED**                      | 2      |
| **Motor Driver (TB6612FNG)** |        |
| ENA (PWM A)                  | 14     |
| IN1 (A1)                     | 13     |
| IN2 (A2)                     | 12     |
| STBY                         | 5      |
| IN3 (B1)                     | 18     |
| IN4 (B2)                     | 19     |
| ENB (PWM B)                  | 4      |
| **IR Sensors**               |        |
| Left                         | 32     |
| Center Left                  | 33     |
| Center                       | 25     |
| Center Right                 | 26     |
| Right                        | 27     |
| **RFID Reader**              |        |
| RX                           | 23     |

## Software Requirements

* **Arduino IDE** with ESP32 board support
* **Libraries**:

  * `Keypad` (for keypad input in Section A)
  * `Adafruit_GFX` (for TFT display)
  * `Adafruit_ST7735` (for TFT display)
  * `DFRobotDFPlayerMini` (for audio playback)
  * `esp_now` (for ESP-NOW communication)
  * `WiFi` (required for ESP-NOW)
  * `Arduino` (core library for ESP32)
  * `FreeRTOS` (included with ESP32 Arduino core for task management in Section B)

## Project Structure

```text
FireGuard/
├── SectionA/
│   ├── FireGuard_SectionA.ino    # Main sketch for Section A
│   ├── DFPlayerHandler.cpp       # DFPlayer audio handling
│   ├── DFPlayerHandler.h         # DFPlayer header
│   ├── ESPNowCommA.cpp           # ESP-NOW communication for Section A
│   ├── ESPNowCommA.h             # ESP-NOW header for Section A
│   ├── FireStatusManager.cpp     # Fire sensor management
│   ├── FireStatusManager.h       # Fire sensor header
│   ├── PhoneEditor.cpp           # Phone number editing and TFT display
│   ├── PhoneEditor.h             # Phone editor header
│   ├── SIM800LManager.cpp        # SIM800L call handling
│   └── SIM800LManager.h          # SIM800L header
├── SectionB/
│   ├── FireGuard_SectionB.ino    # Main sketch for Section B
│   ├── ESPNowCommB.cpp           # ESP-NOW communication for Section B
│   ├── ESPNowCommB.h             # ESP-NOW header for Section B
│   ├── NavigationFunctions.cpp   # Robot navigation and motor control
│   ├── NavigationFunctions.h     # Navigation header
│   ├── RFID_reader.cpp           # RFID reader handling
│   ├── RFID_reader.h             # RFID reader header
│   ├── RoomNavigation.cpp        # Room navigation logic using RFID
│   └── RoomNavigation.h          # Room navigation header
├── docs/
│   └── schematic_diagram.jpg     # Circuit schematic diagram
├── README.md                     # Project documentation
├── LICENSE                       # MIT License file
└── .gitignore                    # Git ignore file
```

## Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/zibontaroka/FireGuard.git
   ```

2. **Install Arduino IDE and Libraries**:

   * Install the Arduino IDE and add ESP32 board support.
   * Install the required libraries via the Arduino Library Manager.

3. **Set Up Hardware**:

   * Connect the components for Section A and Section B as per the pin configuration tables.
   * Ensure the 18650 battery packs are charged and connected.

4. **Configure ESP-NOW**:

   * Update the MAC addresses in ESPNowCommA.h and ESPNowCommB.h to match your ESP32 devices.

     * Section A MAC Address (in ESPNowCommB.h): `{0x94, 0x54, 0xC5, 0xA8, 0x3D, 0x04}`
     * Section B MAC Address (in ESPNowCommA.h): `{0x94, 0x54, 0xC5, 0xA8, 0x3D, 0x04}`
   * Replace these with the actual MAC addresses of your ESP32 boards. To find the MAC address, upload a simple sketch to print it to the Serial Monitor.

5. **Upload the Code**:

   * Open `FireGuard_SectionA.ino` in the Arduino IDE and upload it to the Section A ESP32.
   * Open `FireGuard_SectionB.ino` in the Arduino IDE and upload it to the Section B ESP32.

## Usage

1. **Power On the System**:

   * Power on both Section A (Control Unit) and Section B (Robot) using the 18650 battery packs.

2. **Monitor System Status**:

   * Section A will display the system status on the TFT screen, including:

     * Battery percentage
     * Water level percentage
     * Fire status (ON/OFF)
     * Current mode, room, last event, GSM, ESP, and DFP status
     * Owner and emergency phone numbers

3. **Edit Phone Numbers**:

   * Enter the secret code `*153#` on the keypad to access the phone number editor.
   * Press `A` to edit the owner number or `B` to edit the emergency number.
   * Use the keypad to input the new number: `*` to save, `#` to cancel, `D` to delete digits.

4. **Respond to Fire**:

   * When fire is detected:

     * Section A calls the owner and fire service, plays audio via DFPlayer.
     * Section B navigates to the detected room and extinguishes the fire.
     * After extinguishing, Section B returns to Room 0 (refill station).

---

If you encounter issues, please refer to the schematic diagram in `docs/schematic_diagram.jpg` and check your wiring and connections carefully.

For further contributions or bug reports, feel free to open an issue or pull request on the GitHub repository.


---

## 🧠 Author

**Md Shaifulla Zibon**  
Electrical and Electronics Engineering  
European University of Bangladesh  
GitHub: [@zibontaroka](https://github.com/zibontaroka)