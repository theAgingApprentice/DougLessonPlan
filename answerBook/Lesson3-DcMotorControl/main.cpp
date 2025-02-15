/**
 * @file main.cpp
 * @author The Aging Apprentice (theAgingApprentice@protonmail.com)
 * @brief Lesson 3: Demonstrate spinning the shaft if a DC motor.
 * @version 1.0
 * @date 2025-02-15
 * 
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.

// Global variables and object declarations
#define enA1     A3 // DC Motor controller enable pin.
#define inA1     A4 // DC Motor controller direction pin 1.
#define inA2     A5 // DC Motor controller direction pin 1.

// Forward function declarations (not reqiured for Arduino IDE) but is required 
// for PlatformIO IDE.
void stop();
void goForward();
void goBackward();

/**
 * Standard Arduino intialization function.
 */
void setup() 
{
   Serial.begin(115200);
   Serial.println("<setup> Start of setup.");
   Serial.println("<setup> Set up DC motor control pins.");
   pinMode(enA1, OUTPUT);
   pinMode(inA1, OUTPUT);
   pinMode(inA2, OUTPUT);
   Serial.println("<setup> End of setup.");
} // setup()

/**
 * Standard Arduino main loop function.
 */
void loop() 
{
   Serial.println("<loop> Spin motor forward.");
   goForward();
   delay(1000);
   Serial.println("<loop> Stop motor.");
   stop();
   delay(1000);
   Serial.println("<loop> Spin motor backward.");
   goBackward();
   delay(1000);
   Serial.println("<loop> Stop motor.");
   stop();
   delay(1000);
} // loop()

/**
 * @brief Spins motor clockwise (from motor's perspecive).
 * 
 */
void stop() 
{
  // LM298N Motor Controller.
  Serial.println("<stop> Stop motor.");
  digitalWrite(enA1, LOW);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
} // stop()

/**
 * @brief Spins motor clockwise (from motor's perspecive).
 * 
 */
void goForward() 
{
  // LM298N Motor Controller.
  Serial.println("<goForward> Spin motor forward.");
  digitalWrite(enA1, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
} // goForward()

/**
 * @brief Spins motor counter-clockwise (from motor's perspecive).
 * 
 */
void goBackward() 
{
  // LM298N Motor Controller.
  Serial.println("<goBackward> Spin motor backward.");
  digitalWrite(enA1, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
} // goBackward()