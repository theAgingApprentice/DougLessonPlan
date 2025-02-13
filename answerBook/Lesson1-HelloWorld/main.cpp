/**
 * @file main.cpp
 * @author The Aging Apprentice (theAgingApprentice@protonmail.com)
 * @brief Lesson 1: Write Hello World to the console.
 * @version 1.0
 * @date 2025-02-13
 * 
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.

/**
 * Standard Arduino intialization function.
 */
void setup() 
{
   Serial.begin(115200);
   Serial.println("Setup complete.");
} // setup()

/**
 * Standard Arduino main loop function.
 */
void loop() 
{
   Serial.println("Hello, world!");
   delay(1000);
} // loop()