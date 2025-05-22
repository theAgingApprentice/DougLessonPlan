#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// Define the service and characteristic UUIDs (lowercase for consistency)
#define SERVICE_UUID "19b10000-e8f2-537e-4f6c-d104768a1214"
#define CHARACTERISTIC_UUID "19b10001-e8f2-537e-4f6c-d104768a1214"

// Global variables
BLEClient* pClient = nullptr;
BLERemoteCharacteristic* pRemoteCharacteristic = nullptr;
bool deviceConnected = false;
bool doScan = false;
bool ledState = false;
bool connecting = false;
unsigned long connectStartTime = 0;
BLEAddress* serverAddress = nullptr;
const unsigned long CONNECT_TIMEOUT = 10000; // 10 seconds

// Static callback instance
class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    deviceConnected = true;
    connecting = false;
    Serial.println("Connected to server!");
  }

  void onDisconnect(BLEClient* pclient) {
    deviceConnected = false;
    doScan = true;
    connecting = false;
    Serial.println("Disconnected from server. Restarting scan...");
  }
} clientCallback;

// Advertised device callbacks
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("Found device: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      Serial.println("Found UNO R4 Server!");
      BLEDevice::getScan()->stop();
      Serial.println("Scan stopped");

      // Store the device address
      serverAddress = new BLEAddress(advertisedDevice.getAddress());
      Serial.print("Server address: ");
      Serial.println(serverAddress->toString().c_str());

      // Start connection process
      connecting = true;
      connectStartTime = millis();
      Serial.println("Attempting to connect...");
    }
  }
};

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Starting BLE Client...");
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());

  // Initialize BLE with minimal connections
  BLEDevice::init("ESP32_Client");
  BLEDevice::setPower(ESP_PWR_LVL_N0); // Reduce power to minimize interference

  // Enable BLE debug logging
  esp_log_level_set("BLE", ESP_LOG_VERBOSE);

  // Start scanning
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(100); // Match server advertising interval
  pBLEScan->setWindow(80);    // Scanning window
  pBLEScan->setActiveScan(true); // Active scan for faster discovery
  pBLEScan->start(30, false);
  doScan = true;
  Serial.println("Scanning started");
}

void loop() {
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());

  if (deviceConnected && pRemoteCharacteristic != nullptr) {
    if (pRemoteCharacteristic->canWrite()) {
      uint8_t message = ledState ? 1 : 0;
      Serial.print("Attempting to send: ");
      Serial.println(ledState ? "ON" : "OFF");
      pRemoteCharacteristic->writeValue(message, true);
      Serial.println("Write completed");
      ledState = !ledState;
    } else {
      Serial.println("Characteristic cannot be written!");
    }
    delay(2000);
  }

  if (connecting && serverAddress != nullptr) {
    unsigned long currentTime = millis();
    if (currentTime - connectStartTime >= CONNECT_TIMEOUT) {
      Serial.println("Connection timed out!");
      connecting = false;
      doScan = true;
      if (pClient != nullptr) {
        pClient->disconnect();
      }
      delete serverAddress;
      serverAddress = nullptr;
      return;
    }

    if (pClient == nullptr) {
      Serial.println("Creating new BLE client...");
      pClient = BLEDevice::createClient();
      if (pClient == nullptr) {
        Serial.println("Failed to create BLE client!");
        connecting = false;
        doScan = true;
        delete serverAddress;
        serverAddress = nullptr;
        return;
      }
      pClient->setClientCallbacks(&clientCallback);
    }

    // Attempt connection
    bool connectResult = false;
    try {
      Serial.println("Calling connect...");
      connectResult = pClient->connect(*serverAddress);
    } catch (...) {
      Serial.println("Exception caught during connect!");
    }
    Serial.print("Connection attempt result: ");
    Serial.println(connectResult ? "Success" : "Failed");
    Serial.print("Connection time: ");
    Serial.println(millis() - connectStartTime);

    connecting = false;
    if (!connectResult) {
      Serial.println("Connection failed. Restarting scan...");
      doScan = true;
      pClient->disconnect();
      delete serverAddress;
      serverAddress = nullptr;
      return;
    }

    // Discover service
    Serial.println("Discovering service...");
    BLERemoteService* pRemoteService = pClient->getService(BLEUUID(SERVICE_UUID));
    if (pRemoteService == nullptr) {
      Serial.println("Failed to find service UUID!");
      pClient->disconnect();
      doScan = true;
      delete serverAddress;
      serverAddress = nullptr;
      return;
    }
    Serial.println("Service found");

    // Discover characteristic
    Serial.println("Discovering characteristic...");
    pRemoteCharacteristic = pRemoteService->getCharacteristic(BLEUUID(CHARACTERISTIC_UUID));
    if (pRemoteCharacteristic == nullptr) {
      Serial.println("Failed to find characteristic UUID!");
      pClient->disconnect();
      doScan = true;
      delete serverAddress;
      serverAddress = nullptr;
      return;
    }
    Serial.println("Characteristic found");
    delete serverAddress;
    serverAddress = nullptr;
  }

  if (!deviceConnected && doScan) {
    Serial.println("Scanning for server...");
    BLEDevice::getScan()->start(30, false);
  }
  delay(500);
}