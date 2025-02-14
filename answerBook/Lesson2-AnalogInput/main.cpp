/**
 * @file main.cpp
 * @author The Aging Apprentice (theAgingApprentice@protonmail.com)
 * @brief Lesson 2: Demonstrate Arduino LED Matrix library and joystick input.
 * @version 0.1
 * @date 2025-02-14
 * 
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.

// Global variables and object declarations
#define SW_PIN   A2 // Arduino pin connected to Joystick SW pin
#define VRX_PIN  A1 // Arduino pin connected to Joystick VRX pin
#define VRY_PIN  A0 // Arduino pin connected to Joystick VRY pin

int bValue = 0; // To store value of the button (push down on joystick).
int xValue = 0; // To store value of the X axis.
int yValue = 0; // To store value of the Y axis.

// Forward function declarations (not reqiured for Arduino IDE) but is required 
// for PlatformIO IDE.
void checkJoystick();

/**
 * Standard Arduino intialization function.
 */
void setup() 
{
   Serial.begin(115200);
   Serial.println("<setup> Start of setup.");
   Serial.println("<setup> End of setup.");
} // setup()

/**
 * Standard Arduino main loop function.
 */
void loop() 
{
   checkJoystick();
   delay(200);
} // loop()

/**
 * @brief Read input values of the joystick and act accordingly.
 * @details The Joystick returns 3 analog values: X, Y and button. 
 * X equals ~509 in the neutral position.
 * X equals 1023 in the left position.
 * X equals 0 in the right position.
 * Y equals ~511 in the neutral position.
 * Y equals 0 in the up position.
 * Y equals 1023 in the down position.
 * B equals ~500 in the neutral position.
 * B equals 0 in the pressed position.
 * The values in the neutral position can vary quite a bit.
 * We ignore the Y values in this example.
 * @return * void 
 */
void checkJoystick()
{
   // Read joystick X, Y and button analog values.
   bValue = analogRead(SW_PIN);
   xValue = analogRead(VRX_PIN);
   yValue = analogRead(VRY_PIN);

   if(bValue < 50)
   {
      Serial.println("<checkJoystick> Button pressed.");
      return;
   } // if 

   if(xValue > 950)
   {
      Serial.println("<checkJoystick> Backward.");
      return;
   } // else if

   if(xValue < 50)
   {
      Serial.println("<checkJoystick> Forward.");
      return;
   } // else if

   Serial.println("<checkJoystick> Stop.");
   return;
} // checkJoyStick()