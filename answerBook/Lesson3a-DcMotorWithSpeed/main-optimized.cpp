/**
 * @file main.cpp
 * @author theAgingApprntice
 * @brief Optimized PWM Control for Meccano ER20 Motor on Arduino Uno R4 WiFi
 * @version 1.0
 * @date 2025-05-19
 * @copyright Copyright (c) 2025
 * 
 * @details
 * This program drives the Meccano ER20 hybrid AC/DC motor using optimal PWM settings
 * determined from prior tests (er20PwmTestResults.xlsx). The ER20, a 20V-rated universal
 * motor, is controlled via an L298N motor driver connected to an Arduino Uno R4 WiFi.
 * 
 * ### Optimal Settings:
 * - **Supply Voltage**: 20VDC (matches ER20's rated voltage, L298N 5V jumper removed).
 * - **PWM Frequency**: 100 Hz (best for ER20, lowers duty cycle threshold to 27.45%).
 * - **Resolution**: 8-bit (256 levels, sufficient for control).
 * - **Duty Cycle Range**: 27.45% to 100% (analogWrite(9, 70) to 255), or ~4.94V to 18V
 *   effective (after ~2V L298N drop), offering the widest speed control range.
 * 
 * ### Program Functionality:
 * 1. Configures PWM on pin 9 (D9, P303, likely GPT0_GTIOCA) using FspTimer for precise
 *    control over frequency, resolution, and duty cycle.
 * 2. Sets motor direction (forward/reverse) using L298N IN1 and IN2 pins.
 * 3. Sweeps duty cycle from 27.45% to 100% and back, allowing speed adjustment.
 * 4. Outputs status to Serial Monitor for debugging (115200 baud).
 * 
 * ### Hardware Setup:
 * - **Arduino Uno R4 WiFi**:
 *   - Pin 9: PWM output to L298N ENA (speed control).
 *   - Pin 7: L298N IN1 (direction).
 *   - Pin 8: L298N IN2 (direction).
 * - **L298N Motor Driver**:
 *   - VCC: 20VDC, 2–3A (5V jumper removed to prevent regulator overheating).
 *   - 5V: Supplied from Arduino 5V pin (logic supply).
 *   - GND: Common with Arduino and power supply.
 *   - ENA: Pin 9 (PWM).
 *   - IN1, IN2: Pins 7, 8 (forward: HIGH/LOW, reverse: LOW/HIGH).
 *   - OUT1, OUT2: ER20 motor terminals.
 * - **Meccano ER20 Motor**:
 *   - Hybrid AC/DC, rated for 20V.
 *   - Spins at 27.45% duty cycle (analogWrite(9, 70)) at 20V, 100 Hz.
 * - **Power Supply**:
 *   - 20VDC, 2–3A (adjustable supply or battery).
 * - **Tools**:
 *   - Serial Monitor (115200 baud) for debugging.
 *   - Saleae Logic Analyzer (optional) to verify PWM (100 Hz, 27.45% duty cycle:
 *     period = 10 ms, HIGH = 2.745 ms).
 * 
 * ### Why These Settings:
 * Tests showed 100 Hz at 20V allows the ER20 to spin at a lower duty cycle (27.45%) compared
 * to 66.67% at 5 kHz, due to better current delivery through its inductive windings. The 20V
 * supply matches the motor's rating, reducing the torque threshold. 8-bit resolution provides
 * sufficient control, though 10-bit could be tested for finer steps (0.098% vs. 0.392%).
 */

#include <Arduino.h>
#include <FspTimer.h>

// Pin definitions for L298N motor driver
#define PWM_PIN 9   // D9, P303, likely GPT0_GTIOCA (ENA for L298N speed control)
#define IN1_PIN 7   // D7, controls motor direction (HIGH/LOW for forward)
#define IN2_PIN 8   // D8, controls motor direction (LOW/HIGH for reverse)

// Global FspTimer object for PWM control
FspTimer pwm_timer;

/**
 * @brief Configures PWM on a specified pin using the FspTimer library for precise control.
 * 
 * @param frequency_hz Desired PWM frequency in Hz (e.g., 100 Hz for optimal ER20 performance).
 * @param resolution_bits Resolution of PWM in bits (e.g., 8 for 256 levels, 10 for 1024 levels).
 * @param duty_value Duty cycle value (0 to 2^resolution_bits - 1, e.g., 0–255 for 8-bit).
 * 
 * @details
 * This function configures PWM on pin 9 (D9, P303, likely GPT0_GTIOCA) for the Meccano ER20 motor,
 * allowing precise control over frequency, resolution, and duty cycle. It uses the FspTimer library
 * to interface with the RA4M1's General PWM Timer (GPT), offering greater flexibility than standard
 * Arduino library commands like analogWrite().
 * 
 * ### What the Code Does:
 * 1. **Stops and Closes Timer**: Ensures the timer is reset before reconfiguration.
 * 2. **Determines GPT Channel**: Retrieves the GPT channel for pin 9 (e.g., GPT0) using pin configuration data.
 * 3. **Calculates Timer Parameters**:
 *    - Computes maximum counts based on resolution (e.g., 256 for 8-bit, 1024 for 10-bit).
 *    - Uses the RA4M1's 48 MHz peripheral clock to calculate total counts per PWM cycle:
 *      target_counts = 48,000,000 / frequency_hz.
 *    - Selects the smallest prescaler (1, 4, 16, 64, 256) to fit the period within max_counts:
 *      period_counts = target_counts / prescaler.
 *      Example: For 100 Hz, 8-bit:
 *      - target_counts = 48,000,000 / 100 = 480,000.
 *      - max_counts = 256 (8-bit).
 *      - Prescaler = 256, period_counts = 480,000 / 256 ≈ 1875.
 *      - Adjusted frequency: 48,000,000 / (256 × 1875) ≈ 100 Hz.
 * 4. **Sets Duty Cycle**:
 *    - Calculates pulse counts for the duty cycle: pulse_counts = (duty_value * period_counts) / (max_counts - 1).
 *    - Example: duty_value = 70 (27.45%), period_counts = 1875, max_counts = 256:
 *      pulse_counts = (70 * 1875) / 255 ≈ 515.
 * 5. **Initializes and Starts Timer**:
 *    - Configures the GPT timer in PWM mode with the calculated period and pulse counts.
 *    - Opens and starts the timer to generate the PWM signal.
 * 6. **Sets Resolution**:
 *    - Updates analogWriteResolution to match the specified resolution for consistent duty cycle scaling.
 * 7. **Debug Output**:
 *    - Prints the configured frequency, resolution, and duty cycle percentage to the Serial Monitor.
 * 
 * ### Why Use FspTimer Instead of Simple Arduino Commands:
 * - **Custom Frequency Control**: The default Arduino PWM frequency on the Uno R4 WiFi is ~489.4 Hz,
 *   which is suboptimal for the ER20 (test results show 100 Hz lowers the duty cycle threshold to 27.45%
 *   at 20V, vs. 66.67% at 5 kHz). analogWrite() doesn't allow frequency adjustment, but FspTimer does.
 * - **Resolution Flexibility**: Supports 8-bit, 10-bit, or higher resolution for finer duty cycle steps
 *   (e.g., 0.098% steps in 10-bit vs. 0.392% in 8-bit), which may improve ER20 speed control.
 * - **Precise Duty Cycle**: Ensures accurate duty cycle settings (e.g., 27.45% at analogWrite(9, 70)),
 *   critical for operating at the ER20's spin threshold, avoiding approximations in simpler methods.
 * - **Hardware-Specific Needs**: The RA4M1's GPT timers require direct configuration for non-standard PWM.
 *   FspTimer interfaces with the Renesas FSP, providing access to low-level timer controls unavailable
 *   through analogWrite().
 * - **Motor-Specific Needs**: The ER20's inductance and high torque threshold (20V-rated universal motor)
 *   make it sensitive to frequency. FspTimer allows optimization (e.g., 100 Hz vs. 5 kHz).
 */
void setupPWM(uint32_t frequency_hz, uint8_t resolution_bits, uint16_t duty_value) 
{
  // Stop and close any existing timer to reset configuration
  pwm_timer.stop();
  pwm_timer.close();

  // Define timer type as GPT (General PWM Timer) and get the channel for PWM_PIN
  uint8_t timer_type = GPT_TIMER;
  uint8_t channel = GET_CHANNEL(getPinCfgs(PWM_PIN, PIN_CFG_REQ_PWM)[0]);

  // Calculate maximum counts based on resolution (e.g., 256 for 8-bit)
  uint32_t max_counts = (1UL << resolution_bits);
  // RA4M1 peripheral clock frequency (48 MHz)
  uint32_t clock_freq = 48000000UL;
  // Calculate total counts needed for the desired frequency
  uint32_t target_counts = clock_freq / frequency_hz;
  // Initialize prescaler and period counts
  timer_source_div_t source_div = TIMER_SOURCE_DIV_1;
  uint32_t period_counts = max_counts;

  // Select the smallest prescaler to fit the period within max_counts
  if (target_counts <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_1;
    period_counts = target_counts;
  } // if
  else if (target_counts / 4 <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_4;
    period_counts = target_counts / 4;
  } //else if
  else if (target_counts / 16 <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_16;
    period_counts = target_counts / 16;
  } // else if
  else if (target_counts / 64 <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_64;
    period_counts = target_counts / 64;
  } // else if
  else 
  {
    source_div = TIMER_SOURCE_DIV_256;
    period_counts = target_counts / 256;
  } // else

  // Calculate pulse counts for the duty cycle (HIGH time)
  uint32_t pulse_counts = (duty_value * period_counts) / (max_counts - 1);

  // Initialize the GPT timer in PWM mode with the calculated settings
  if (!pwm_timer.begin(TIMER_MODE_PWM, timer_type, channel, period_counts, pulse_counts, source_div, nullptr, nullptr)) 
  {
    Serial.println("PWM initialization failed!");
    while (1); // Halt if initialization fails
  } // if

  // Open and start the timer to generate PWM
  pwm_timer.open();
  pwm_timer.start();
  // Set the resolution for analogWrite to match the specified resolution
  analogWriteResolution(resolution_bits);

  // Debug output to Serial Monitor
  Serial.print("PWM set: ");
  Serial.print(frequency_hz);
  Serial.print(" Hz, ");
  Serial.print(resolution_bits);
  Serial.print("-bit, Duty: ");
  Serial.print((duty_value * 100.0) / (max_counts - 1));
  Serial.println("%");
} // setupPWM()

/**
 * @brief Initializes the Arduino, pins, and PWM for the ER20 motor.
 * 
 * @details
 * - Initializes Serial communication at 115200 baud for debugging.
 * - Configures PWM_PIN (9), IN1_PIN (7), and IN2_PIN (8) as outputs.
 * - Sets initial motor direction to forward (IN1 HIGH, IN2 LOW).
 * - Configures PWM with optimal settings: 100 Hz, 8-bit resolution, 27.45% duty cycle
 *   (analogWrite(9, 70)), the minimum threshold for the ER20 to spin at 20V.
 */
void setup() 
{
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for Serial to connect

  // Configure pins as outputs
  pinMode(PWM_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  // Set initial motor direction: forward (IN1 HIGH, IN2 LOW)
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);

  // Set optimal PWM settings: 100 Hz, 8-bit, 27.45% duty cycle (minimum for ER20 spin)
  setupPWM(100, 8, 70);
  analogWrite(PWM_PIN, 70);

  // Debug output to confirm setup
  Serial.println("Setup complete. ER20 motor running at 100 Hz, 8-bit, starting at 27.45% duty cycle (forward).");
} // setup()

/**
 * @brief Main loop to control the ER20 motor speed and direction.
 * 
 * @details
 * - **Forward Direction**: Sweeps duty cycle from 27.45% (analogWrite(9, 70)) to 100%
 *   (analogWrite(9, 255)) and back, with 2-second steps to observe speed changes.
 * - **Pause**: Stops the motor for 3 seconds between direction changes.
 * - **Reverse Direction**: Switches direction (IN1 LOW, IN2 HIGH) and repeats the sweep.
 * - **Debugging**: Outputs duty cycle and direction to Serial Monitor.
 * - **Cycle**: Repeats forward and reverse sweeps indefinitely.
 */
void loop() 
{
  // Forward direction: Sweep duty cycle up from 27.45% to 100%
  Serial.println("Forward direction: Increasing speed...");
  for (int duty = 70; duty <= 255; duty += 10) 
  {
    analogWrite(PWM_PIN, duty);
    Serial.print("Duty cycle: ");
    Serial.print((duty * 100.0) / 255);
    Serial.println("%");
    delay(2000); // 2-second delay to observe speed
  } // for

  // Sweep duty cycle down from 100% to 27.45%
  Serial.println("Forward direction: Decreasing speed...");
  for (int duty = 255; duty >= 70; duty -= 10) 
  {
    analogWrite(PWM_PIN, duty);
    Serial.print("Duty cycle: ");
    Serial.print((duty * 100.0) / 255);
    Serial.println("%");
    delay(2000);
  } // for

  // Stop the motor before changing direction
  analogWrite(PWM_PIN, 0);
  Serial.println("Motor off");
  delay(3000); // 3-second pause

  // Reverse direction: Set IN1 LOW, IN2 HIGH
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  Serial.println("Reverse direction: Increasing speed...");
  // Sweep duty cycle up
  for (int duty = 70; duty <= 255; duty += 10) 
  {
    analogWrite(PWM_PIN, duty);
    Serial.print("Duty cycle: ");
    Serial.print((duty * 100.0) / 255);
    Serial.println("%");
    delay(2000);
  } // for

  // Sweep duty cycle down
  Serial.println("Reverse direction: Decreasing speed...");
  for (int duty = 255; duty >= 70; duty -= 10) 
  {
    analogWrite(PWM_PIN, duty);
    Serial.print("Duty cycle: ");
    Serial.print((duty * 100.0) / 255);
    Serial.println("%");
    delay(2000);
  } // for

  // Stop the motor before changing direction again
  analogWrite(PWM_PIN, 0);
  Serial.println("Motor off");
  delay(3000);

  // Reset to forward direction for the next cycle
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
} // loop()