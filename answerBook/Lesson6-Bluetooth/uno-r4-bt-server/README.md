# Arduino UNO R4 WiFi BLE Server

This project implements a BLE server on an Arduino UNO R4 WiFi that advertises a service and controls an onboard LED based on ON/OFF commands received from a BLE client (e.g., ESP32).

## Overview

The UNO R4 WiFi server:
- Advertises a BLE service with UUID `19b10000-e8f2-537e-4f6c-d104768a1214` under the name `UNO_R4_Server`.
- Exposes a characteristic (`19b10001-e8f2-537e-4f6c-d104768a1214`) that accepts `1` (ON) or `0` (OFF) to control the onboard LED.
- Polls for a central device (BLE client) and handles connections.
- Sets optimized connection and advertising intervals for reliable communication.

## Hardware Requirements

- **Arduino UNO R4 WiFi**: Board with NINA-W102 BLE module.
- **Power Supply**: USB cable or stable 5V power source.
- **LED**: Uses the onboard LED (typically pin `LED_BUILTIN`).

## Software Requirements

- **Arduino IDE**: For programming the UNO R4 WiFi (or PlatformIO).
- **ArduinoBLE Library**: Required for BLE functionality (included via Arduino Library Manager).
- **Board Support**: Arduino UNO R4 WiFi board package.

## Setup Instructions

1. **Install Arduino IDE**:
   - Download and install the Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software).
   - Add the UNO R4 WiFi board package via Boards Manager (search for “Arduino UNO R4 Boards”).

2. **Install ArduinoBLE Library**:
   - In the Arduino IDE, go to `Sketch > Include Library > Manage Libraries`.
   - Search for `ArduinoBLE` and install the latest version.

3. **Load the Server Code**:
   - Open the server code (`server.ino`) in the Arduino IDE.
   - Ensure the UUIDs match:
     - Service UUID: `19b10000-e8f2-537e-4f6c-d104768a1214`
     - Characteristic UUID: `19b10001-e8f2-537e-4f6c-d104768a1214`
   - Verify the LED pin is set to `LED_BUILTIN` (or your custom pin).

4. **Connect the UNO R4 WiFi**:
   - Connect the UNO R4 WiFi to your computer via USB.
   - Select the board (`Arduino UNO R4 WiFi`) and port in the Arduino IDE.

5. **Upload and Monitor**:
   - Upload the code to the UNO R4 WiFi (`Sketch > Upload`).
   - Open the Serial Monitor (`Tools > Serial Monitor`) at 115200 baud to view output.

6. **Ensure Client is Running**:
   - The ESP32 client must be running with the corresponding client code, scanning for the service UUID `19b10000-e8f2-537e-4f6c-d104768a1214`.

## How It Works

1. **Initialization**:
   - The UNO R4 WiFi initializes the BLE module with the name `UNO_R4_Server`.
   - It sets connection intervals (7.5ms–15ms) and advertising intervals (62.5ms–125ms) for efficient communication.

2. **Service and Characteristic Setup**:
   - Creates a BLE service with UUID `19b10000-e8f2-537e-4f6c-d104768a1214`.
   - Adds a writable characteristic (`19b10001-e8f2-537e-4f6c-d104768a1214`) to receive ON/OFF commands.

3. **Advertising**:
   - The server advertises the service, making it discoverable by BLE clients.
   - It polls for a central device (client) to connect.

4. **Connection Handling**:
   - When a client (e.g., ESP32) connects, the server logs the connection.
   - It monitors the characteristic for write events.

5. **LED Control**:
   - If the characteristic receives `1`, the LED turns ON (`digitalWrite(LED_BUILTIN, HIGH)`).
   - If it receives `0`, the LED turns OFF (`digitalWrite(LED_BUILTIN, LOW)`).

6. **Error Handling**:
   - If the client disconnects, the server resumes advertising and polling for a new connection.

## Serial Output

The Serial Monitor shows:
- Initialization status (`Starting BLE Server...`).
- Advertising status (`Polling for central...`).
- Connection events (`Connected to client: [address]`).
- LED commands (`Received: ON`, `Received: OFF`).

## Troubleshooting

- **Client Doesn’t Connect**:
  - Ensure the ESP32 client is scanning for the correct service UUID.
  - Test with a BLE app (e.g., nRF Connect) to verify the server’s service and characteristic.
  - Check for interference from other BLE devices.
- **LED Doesn’t Respond**:
  - Verify the LED pin is correctly set (`LED_BUILTIN`).
  - Ensure the client is sending `1` or `0` to the characteristic.
- **Serial Port Issues**:
  - Select the correct port in the Arduino IDE.
  - Restart the IDE or reconnect the board if the port is unavailable.

## License

This project is licensed under the MIT License.