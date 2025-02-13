/**
 * @file main.cpp
 * @author The Aging Apprentice (theAgingApprentice@protonmail.com)
 * @brief Demonstrate Arduino LED Matrix library and joystick input.
 * @version 0.1
 * @date 2025-02-11
 * 
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.
#include <Arduino_LED_Matrix.h> // Part of the Renesas core. Library manager 
                                // not required.
#include <Servo.h> // 

// Global variables and object declarations
ArduinoLEDMatrix matrix; // Create LED matrix object.
#define SW_PIN   A2 // Arduino pin connected to Joystick SW pin
#define VRX_PIN  A1 // Arduino pin connected to Joystick VRX pin
#define VRY_PIN  A0 // Arduino pin connected to Joystick VRY pin
#define enA1     A3 // DC Motor controller enable pin.
#define inA1     A4 // DC Motor controller direction pin 1.
#define inA2     A5 // DC Motor controller direction pin 1.
#define servoPin D11 // Servo motor control pin.
Servo servo;

int bValue = 0; // To store value of the button (push down on joystick).
int xValue = 0; // To store value of the X axis.
int yValue = 0; // To store value of the Y axis.

int servoForward = 115; // PWM rate for servo motor to go forward.
int servoBackward = 55; // PWM rate for servo motor to go backward.
int servoStop = 90; // PWM rate for servo motor to stop.

// Forward function declarations (not reqiured for Arduino IDE) but is required 
// for PlatformIO IDE.
void checkJoystick();
void stop();
void goForward();
void goBackward();

// Pre-defined 2D array of an arrow pointing Forward.
byte forward[8][12] = 
{
   { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }
};

// Pre-defined 2D array of an arrow pointing Backward.
byte backward[8][12] = 
{
   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }
};

// Pre-defined 2D array of a hollow box.
byte Neutral[8][12] = 
{
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
   { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
   { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
   { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Pre-defined 2D array of a solid box.
byte Pressed[8][12] = 
{
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

/**
 * Standard Arduino intialization function.
 */
void setup() 
{
   Serial.begin(115200);
   Serial.println("<setup> Start of setup.");
   Serial.println("<setup> Initialize LED diplay.");
   matrix.begin(); // Initialize LED matrix.
   matrix.clear(); // Clear LED matrix.
   Serial.println("<setup> Set up DC motor control pins.");
   pinMode(enA1, OUTPUT);
   pinMode(inA1, OUTPUT);
   pinMode(inA2, OUTPUT);
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

  // Print joystick input reading to Serial Monitor.
//   Serial.print("<checkJoystick> x = ");
//   Serial.print(xValue);
//   Serial.print(", y = ");
//   Serial.print(yValue);
//   Serial.print(", b = ");
//   Serial.println(bValue);

  // Display pattern on the LED matrix based on joystick input.
  if(bValue < 50)
  {
    matrix.renderBitmap(Pressed, 8, 12);
    Serial.println("<checkJoystick> Button pressed.");
  return;
  } // if 
  
  if(xValue < 50)
  {
    matrix.renderBitmap(forward, 8, 12);
//    Serial.println("<checkJoystick> Forward.");
    goForward();
    return;
  } // if 

  if(xValue > 950)
  {
    matrix.renderBitmap(backward, 8, 12);
//    Serial.println("<checkJoystick> Backward.");
    goBackward();
    return;
  } // else if

  matrix.renderBitmap(Neutral, 8, 12);
  stop();
  return;
} // checkJoyStick()

/**
 * @brief Spins motor clockwise (from motor's perspecive).
 * 
 */
void stop() 
{
  // LM298N Motor Controller.
  digitalWrite(enA1, LOW);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  servo.write(servoStop);
} // stop()

/**
 * @brief Spins motor clockwise (from motor's perspecive).
 * 
 */
void goForward() 
{
  // LM298N Motor Controller.
  digitalWrite(enA1, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  servo.write(servoForward);
  Serial.println("<goForward> Forward.");
} // goForward()

/**
 * @brief Spins motor counter-clockwise (from motor's perspecive).
 * 
 */
void goBackward() 
{
  digitalWrite(enA1, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  servo.write(servoBackward);
  Serial.println("<checkJoystick> Backward.");
} // goBackward()