/**
 * @file main.cpp
 * @author The Aging Apprentice (theAgingApprentice@protonmail.com)
 * @brief Lesson 4: Demonstrate Arduino LED Matrix library and joystick input.
 * @version 1.0
 * @date 2025-02-17
 * 
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.
#include <Servo.h> // Servo motor library. 

// Global variables and object declarations
#define servoPin D11 // Servo motor control pin.
Servo servo;

int servoForward = 115; // PWM rate for servo motor to go forward.
int servoBackward = 55; // PWM rate for servo motor to go backward.
int servoStop = 90; // PWM rate for servo motor to stop.

/**
 * Standard Arduino intialization function.
 */
void setup() 
{
   Serial.begin(115200);
   Serial.println("<setup> Start of setup.");
   Serial.println("<setup> Set up Servo motor control pin.");
   servo.attach(servoPin);
   servo.write(servoStop);
   Serial.println("<setup> End of setup.");
} // setup()

/**
 * Standard Arduino main loop function.
 */
void loop() 
{
   servo.write(servoStop);
   delay(1000);
   servo.write(servoForward);
   delay(1000);
   servo.write(servoBackward);
   delay(1000);
} // loop()
