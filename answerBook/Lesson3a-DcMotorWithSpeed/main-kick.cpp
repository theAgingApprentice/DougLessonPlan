/**
 * @file main.cpp
 * @author theAgingApprntice
 * @brief Motor Control Test for ESP32
 * @version 0.1  
 * @date  2025-05-17
 * 
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.

// Pin definitions
const int ENA = 9;   // PWM pin for Motor A speed
const int IN1 = 8;   // Motor A direction
const int IN2 = 7;   // Motor A direction

/**
 * @brief Initializes serial communication and prompts user for input.
 * @return void
 */
void setupSerial() 
{
  // Initialize Serial communication at 115200 baud rate
  Serial.begin(115200);
  
  // Wait for Serial Monitor to connect
  while (!Serial) 
  {
  } // while()
  
  // Print prompt for user
  Serial.println("Enter a number between 0 and 255 for Motor A speed:");
} // setupSerial()

/**
 * @brief Checks for user input from Serial Monitor and sets motor speed.
 * @return void 
 */
void checkUserInput() 
{
  // Wait until data is available (blocks until user sends input)
  while (Serial.available() == 0) 
  {
    ; // Do nothing, wait for input
  }
  
  // Read the incoming string until newline (Enter key)
  String userInput = Serial.readStringUntil('\n');
  
  // Remove any whitespace or newline characters
  userInput.trim();
  
  // Check if the input is a valid number
  if (userInput.toInt() > 0 || userInput == "0") 
  {
    int number = userInput.toInt();
    
    // Check if the number is within the valid range (0-255)
    if (number >= 0 && number <= 255) 
    {
      // Apply kick-start: full speed (PWM 255) for 100ms if number > 0
      if (number > 0) 
      {
        analogWrite(ENA, 255);
        delay(100); // Brief pulse to start motor
      } // if
      // Set user-specified speed
      analogWrite(ENA, number);
      Serial.print("Valid input received: ");
      Serial.print(number);
      Serial.println(" (Motor A speed set with kick-start)");
    } // if 
    else 
    {
      Serial.println("Error: Number must be between 0 and 255!");
    } // else
  } // if
  else 
  {
    Serial.println("Error: Invalid input! Please enter a number.");
  } // else
} // checkUserInput()

/** 
 * @brief Setup function to initialize the motor control pins and serial communication.
 * @return void
 */
void setup() 
{
  // Set motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Set motor direction (forward: IN1 HIGH, IN2 LOW)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Initialize serial communication
  setupSerial();
} // setup()

/**
 * @brief Main loop function to continuously check for user input.
 * @return void
 */
void loop() 
{
  // Check for user input
  checkUserInput();
} // loop()