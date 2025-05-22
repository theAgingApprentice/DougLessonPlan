#include <Arduino.h>
#include <ArduinoBLE.h>

// Define the BLE service and characteristic UUIDs (lowercase for consistency)
#define SERVICE_UUID "19b10000-e8f2-537e-4f6c-d104768a1214"
#define CHARACTERISTIC_UUID "19b10001-e8f2-537e-4f6c-d104768a1214"

// Pin for the LED
#define LED_PIN 13

BLEService customService(SERVICE_UUID); // Create a BLE service
BLEByteCharacteristic customCharacteristic(CHARACTERISTIC_UUID, BLERead | BLEWrite); // Byte characteristic

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Starting BLE Server...");

  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED pin initialized");

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }
  Serial.println("BLE initialized successfully");

  // Set local name and advertised service
  BLE.setLocalName("UNO_R4_Server");
  BLE.setAdvertisedService(customService);

  // Add characteristic to service
  customService.addCharacteristic(customCharacteristic);
  BLE.addService(customService);

  // Set initial value
  customCharacteristic.writeValue(0);
  Serial.println("Characteristic initialized with value: 0");

  // Set advertising parameters
  BLE.setAdvertisingInterval(100); // 100ms interval
  BLE.setConnectionInterval(6, 12); // Min 7.5ms, Max 15ms
  BLE.setConnectable(true);
  BLE.advertise();
  Serial.println("BLE Server started. Advertising with UUID: " + String(SERVICE_UUID));
}

void loop() {
  // Poll for central device
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to client: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (customCharacteristic.written()) {
        uint8_t value = customCharacteristic.value();
        Serial.print("Received byte: ");
        Serial.println(value);
        if (value == 1) { // 1 for ON
          digitalWrite(LED_PIN, HIGH);
          Serial.println("LED turned ON");
        } else if (value == 0) { // 0 for OFF
          digitalWrite(LED_PIN, LOW);
          Serial.println("LED turned OFF");
        } else {
          Serial.println("Unknown command received");
        }
      }
      delay(100);
    }

    Serial.print("Disconnected from client: ");
    Serial.println(central.address());
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("Polling for central...");
  }
  delay(500);
}