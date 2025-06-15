// I2C Scanner for ESP32 (Adafruit HUZZAH32 Feather)
// This program scans the I2C bus for connected devices and prints their addresses to the Serial Monitor.
// It is designed for teaching and demonstration purposes.
//
// Wiring for HUZZAH32 Feather:
//   SDA: GPIO23 (physical pin 17, labeled "SDA" on the board)
//   SCL: GPIO22 (physical pin 18, labeled "SCL" on the board)
//
// Connect your I2C device's SDA and SCL lines to these pins.
//
// Open the Serial Monitor at 115200 baud to view the results.

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object for 16x2 display at I2C address 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);

/**
 * @brief STandrad Arduino setup funciotn that runs at the start of the program.
 */
void setup() 
{
  // Initialize I2C bus on the correct pins for HUZZAH32 Feather
  // Wire.begin(SDA, SCL):
  //   SDA = GPIO23
  //   SCL = GPIO22
  Wire.begin(23, 22); 

  // Start serial communication at 115200 baud
  Serial.begin(115200);
 
  // Wait for Serial Monitor to open (not always needed, but good for USB serial)
  while (!Serial) 
  {
    delay(10); // Wait for Serial to be ready
  } //while()

} // setup()

/**
 * @brief Main loop that scans the I2C bus for devices.
 * 
 * This function attempts to communicate with each possible I2C address
 * and reports any devices found.
 */
void loop() 
{
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning I2C bus...");

  // I2C addresses range from 1 to 126 (0 and 127 are reserved)
  for (address = 1; address < 127; address++) 
  {
    // Try to start communication with each address
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) 
    {
      // Device responded at this address
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0"); // Print leading zero for single-digit hex
      } // if
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    } // if
    else if (error == 4) 
    {
      // Unknown error occurred
      Serial.print("Unknown error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      } // if
      Serial.println(address, HEX);
    } // else if
  } // for

  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  } // if
  else
  {
    Serial.println("done\n");
  } // else

  // Wait 5 seconds before scanning again
  delay(5000); 
} // loop()
