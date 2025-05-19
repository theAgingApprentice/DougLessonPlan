/**
 * @file main.cpp
 * @author theAgingApprntice
 * @brief Motor Control Test for Arduino UNO R4 WiFi
 * @version 0.2
 * @date 2025-05-17
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h>

// Pin definitions
const int ENA = 9;   // PWM pin for Motor A speed
const int IN1 = 8;   // Motor A direction
const int IN2 = 7;   // Motor A direction

// Toggle GPT PWM (1 = use GPT for 4 kHz, 0 = use analogWrite for 490 Hz)
#define USE_GPT_PWM 0

#if USE_GPT_PWM
// Renesas RA4M1 GPT registers for pin 9 (P108, assumed GPT0 GTIOC0A)
#define GPT0_BASE 0x40078000 // GPT0 base address
#define GPT0_GTWP  (*(volatile uint32_t *)(GPT0_BASE + 0x00)) // Write protection
#define GPT0_GTCR  (*(volatile uint32_t *)(GPT0_BASE + 0x04)) // Timer control
#define GPT0_GTCNT (*(volatile uint32_t *)(GPT0_BASE + 0x08)) // Counter
#define GPT0_GTPR  (*(volatile uint32_t *)(GPT0_BASE + 0x2C)) // Period
#define GPT0_GTDT  (*(volatile uint32_t *)(GPT0_BASE + 0x34)) // Duty cycle
#define GPT0_GTIOR (*(volatile uint32_t *)(GPT0_BASE + 0x14)) // Output control
#define R_PFS_BASE 0x40080000 // Port function select base
#define PFS_P108PFS (*(volatile uint32_t *)(R_PFS_BASE + 0x0208)) // Pin 9 (P108)

/**
 * @brief Initializes GPT0 for 4 kHz PWM on pin 9.
 */
void setupPwm() {
  // Unlock GPT0 registers
  GPT0_GTWP = 0x1F0000; // Disable write protection
  
  // Stop timer
  GPT0_GTCR = 0;
  
  // Configure pin 9 (P108) for GPT0 GTIOC0A
  PFS_P108PFS = (1 << 16) | (0x0D << 8); // PME=1, PSEL=0x0D (GPT)
  
  // Set PWM mode
  GPT0_GTIOR = (1 << 16) | (2 << 6); // GTIOC0A: high at start, low at compare
  GPT0_GTCR = (1 << 16) | (0 << 0); // Saw-wave PWM, PCLK/1 (48 MHz)
  
  // Set frequency: ~4 kHz (48 MHz / (11999 + 1))
  GPT0_GTPR = 11999;
  
  // Initial duty cycle (0%)
  GPT0_GTDT = 0;
  
  // Start timer
  GPT0_GTCR |= (1 << 24);
  Serial.println("GPT PWM initialized: ~4 kHz on pin 9");
}

/**
 * @brief Sets PWM duty cycle (0-255).
 */
void setPwmDuty(uint8_t duty) {
  uint32_t compare = (uint32_t)duty * 11999 / 255;
  GPT0_GTDT = compare;
}
#else
/**
 * @brief Initializes default PWM (490 Hz) on pin 9.
 */
void setupPwm() {
  pinMode(ENA, OUTPUT);
  analogWriteResolution(8); // 8-bit (0-255)
  Serial.println("Default PWM initialized: ~490 Hz on pin 9");
}

/**
 * @brief Sets PWM duty cycle using analogWrite.
 */
void setPwmDuty(uint8_t duty) {
  analogWrite(ENA, duty);
}
#endif

/**
 * @brief Initializes serial communication.
 */
void setupSerial() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for Serial Monitor
  }
  Serial.println("Enter a number between 0 and 255 for Motor A speed:");
}

/**
 * @brief Checks user input and sets motor speed.
 */
void checkUserInput() {
  while (Serial.available() == 0) {
    ; // Wait for input
  }
  String userInput = Serial.readStringUntil('\n');
  userInput.trim();
  if (userInput.toInt() > 0 || userInput == "0") {
    int number = userInput.toInt();
    if (number >= 0 && number <= 255) {
      if (number > 0) {
        // Enhanced kick-start: 200ms pulse, 3 attempts
        for (int attempt = 1; attempt <= 3; attempt++) {
          setPwmDuty(255); // Full speed
          delay(200);
          setPwmDuty(number); // User speed
          delay(100);
          Serial.print("Kick-start attempt ");
          Serial.print(attempt);
          Serial.print(" at PWM ");
          Serial.println(number);
          if (attempt < 3) {
            delay(100);
          }
        }
      } else {
        setPwmDuty(0); // Stop motor
      }
      Serial.print("Valid input received: ");
      Serial.print(number);
      Serial.println(" (Motor A speed set with enhanced kick-start)");
    } else {
      Serial.println("Error: Number must be between 0 and 255!");
    }
  } else {
    Serial.println("Error: Invalid input! Please enter a number.");
  }
  Serial.println("Enter a number between 0 and 255 for Motor A speed:");
}

/**
 * @brief Setup function.
 */
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  setupPwm();
  setupSerial();
}

/**
 * @brief Main loop.
 */
void loop() {
  checkUserInput();
}