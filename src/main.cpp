/**
 * @file main.cpp
 * @author theAgingApprntice
 * @brief Motor Control Test for Arduino UNO R4 WiFi
 * @version 0.2
 * @date 2025-05-17
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h>

/**
 * @brief Initializes serial communication.
 */
void setupSerial() 
{
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for Serial Monitor
  }
} // setupSerial()


/**
 * @brief Setup function.
 */
void setup() 
{
  setupSerial();
  Serial.println("<setup> End of setup.");
} // setup()

/**
 * @brief Main loop.
 */
void loop() 
{

} // loop()