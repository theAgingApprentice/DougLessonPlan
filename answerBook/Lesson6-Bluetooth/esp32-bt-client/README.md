# ESP32 BLE Client

This project implements a BLE client on an ESP32 (Adafruit ESP32 Feather) that connects to a BLE server (e.g., Arduino UNO R4 WiFi) and sends ON/OFF commands to control an LED.

## Overview

The ESP32 client:
- Scans for a BLE server advertising a specific service UUID (`19b10000-e8f2-537e-4f6c-d104768a1214`).
- Connects to the server (named `UNO_R4_Server`) when found.
- Discovers the server's service and characteristic (`19b10001-e8f2-537e-4f6c-d104768a1214`).
- Sends alternating `1` (ON) and `0` (OFF) messages every 2 seconds to the characteristic, controlling the server's LED.
- Re-scans if the connection is lost or fails, with a 10-second connection timeout.

## Hardware Requirements

- **ESP32 Board**: Adafruit ESP32 Feather (or compatible ESP32 board).
- **Power Supply**: USB cable or stable 5V/3.3V power source.
- **BLE Server**: Arduino UNO R4 WiFi running the corresponding server code.

## Software Requirements

- **PlatformIO**: IDE for building and uploading the code (VSCode extension recommended).
- **Arduino Framework**: ESP32 Arduino core (`espressif32@6.8.1`).
- **Library**: `ESP32 BLE Arduino` (included via PlatformIO).

## Setup Instructions

1. **Install PlatformIO**:
   - Install VSCode and the PlatformIO extension.
   - Clone or download this project to your computer.

2. **Configure `platformio.ini`**:
   - Ensure the `platformio.ini` file is configured as follows:
     ```ini
     [env:featheresp32]
     platform = espressif32@6.8.1
     board = featheresp32
     framework = arduino
     monitor_speed = 115200
     upload_speed = 115200
     upload_port = /dev/cu.usbserial-0264F2AE
     monitor_port = /dev/cu.usbserial-0264F2AE
     build_flags =
       -DCONFIG_ARDUINO_LOOP_STACK_SIZE=32768
       -DCONFIG_BTDM_CTRL_HCI_UART_BAUDRATE=115200
     ```
   - Adjust `upload_port` and `monitor_port` to match your ESP32’s serial port (e.g., `/dev/ttyUSB0` on Linux or `COM3` on Windows).

3. **Connect the ESP32**:
   - Connect the ESP32 to your computer via USB.
   - Verify the serial port in PlatformIO’s device monitor.

4. **Build and Upload**:
   - Open the project in PlatformIO.
   - Run `pio run --target upload` to build and upload the code.
   - Open the serial monitor (`pio device monitor`) to view output.

5. **Ensure Server is Running**:
   - The UNO R4 WiFi server must be running with the corresponding server code, advertising the service UUID `19b10000-e8f2-537e-4f6c-d104768a1214`.

## How It Works

1. **Initialization**:
   - The ESP32 initializes as a BLE client named `ESP32_Client`.
   - It sets the BLE radio power to a low level (`ESP_PWR_LVL_N0`) to minimize interference.

2. **Scanning**:
   - The client scans for BLE devices every 30 seconds.
   - It looks for a device advertising the service UUID `19b10000-e8f2-537e-4f6c-d104768a1214` (named `UNO_R4_Server`).

3. **Connection**:
   - Upon finding the server, the client stops scanning and attempts to connect to the server’s address.
   - A 10-second timeout ensures the client doesn’t hang indefinitely.
   - If the connection fails, it restarts scanning.

4. **Service and Characteristic Discovery**:
   - After connecting, the client discovers the server’s service and characteristic (`19b10001-e8f2-537e-4f6c-d104768a1214`).
   - If discovery fails, it disconnects and resumes scanning.

5. **LED Control**:
   - Every 2 seconds, the client sends a `1` (ON) or `0` (OFF) to the characteristic, toggling the server’s LED.
   - The client checks if the characteristic is writable before sending.

6. **Error Handling**:
   - If the connection is lost, the client automatically restarts scanning.
   - Memory is managed to prevent leaks (e.g., freeing the server address).

## Serial Output

The serial monitor shows:
- Heap usage (`Free heap: ...`).
- Discovered devices (`Found device: ...`).
- Connection status (`Found UNO R4 Server!`, `Connected to server!`).
- LED commands (`Attempting to send: ON/OFF`, `Write completed`).
- Errors or timeouts (`Connection timed out!`, `Connection failed.`).

## Troubleshooting

- **No Connection**:
  - Ensure the UNO R4 server is powered and advertising.
  - Test the server with a BLE app (e.g., nRF Connect) to verify the service UUID.
  - Check for interference from other BLE devices (e.g., “Desk 0321”).
- **Serial Port Issues**:
  - Update `upload_port` and `monitor_port` in `platformio.ini` to match your ESP32’s port.
- **Slow Scanning**:
  - Adjust `setInterval` and `setWindow` in the code (e.g., `200` and `160`) for faster scanning, but ensure compatibility with the server.

## License

This project is licensed under the MIT License.