/**
 * @file main.cpp
 * @author 
 * @brief 
 * @version 
 * @date 
 * 
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.

// Pin definitions
const int ENA = 9;   // PWM pin for Motor A speed
const int IN1 = 8;   // Motor A direction
const int IN2 = 7;   // Motor A direction
const int ENB = 10;  // PWM pin for Motor B speed
const int IN3 = 6;   // Motor B direction
const int IN4 = 5;   // Motor B direction

void setup() 
{
  // Set pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() 
{
  // Motor A forward at half speed
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 128);  // 50% speed

  // Motor B forward at half speed
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 128);  // 50% speed
  delay(2000);  // Run for 2 seconds

  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(1000);  // Stop for 1 second

  // Motor A backward at full speed
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);  // 100% speed

  // Motor B backward at full speed
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255);  // 100% speed
  delay(2000);  // Run for 2 seconds

  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(1000);  // Stop for 1 second
}