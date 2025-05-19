/**
 * @file main.cpp
 * @author theAgingApprntice
 * @brief PWM Motor Control Test for Meccano ER20 on Arduino Uno R4 WiFi
 * @version 0.5
 * @date 2025-05-18
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h>
#include <FspTimer.h>

#define PWM_PIN 9   // D9, P303, likely GPT0_GTIOCA (ENA for L298N)
#define IN1_PIN 7   // D7, motor direction
#define IN2_PIN 8   // D8, motor direction

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
 *   critical for finding the ER20's spin threshold, avoiding approximations in simpler methods.
 * - **Hardware-Specific Needs**: The RA4M1's GPT timers require direct configuration for non-standard PWM.
 *   FspTimer interfaces with the Renesas FSP, providing access to low-level timer controls unavailable
 *   through analogWrite().
 * - **Motor-Specific Needs**: The ER20's inductance and high torque threshold (20V-rated universal motor)
 *   make it sensitive to frequency. FspTimer allows optimization (e.g., 100 Hz vs. 5 kHz).
 * 
 * This approach ensures the PWM signal meets the ER20's needs, as confirmed by test results showing
 * improved performance at lower frequencies and higher voltages (e.g., 20V, 100 Hz: 27.45% duty cycle).
 */
void setupPWM(uint32_t frequency_hz, uint8_t resolution_bits, uint16_t duty_value) 
{
  pwm_timer.stop();
  pwm_timer.close();

  uint8_t timer_type = GPT_TIMER;
  uint8_t channel = GET_CHANNEL(getPinCfgs(PWM_PIN, PIN_CFG_REQ_PWM)[0]);

  uint32_t max_counts = (1UL << resolution_bits);
  uint32_t clock_freq = 48000000UL;
  uint32_t target_counts = clock_freq / frequency_hz;
  timer_source_div_t source_div = TIMER_SOURCE_DIV_1;
  uint32_t period_counts = max_counts;

  if (target_counts <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_1;
    period_counts = target_counts;
  } 
  else if (target_counts / 4 <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_4;
    period_counts = target_counts / 4;
  } 
  else if (target_counts / 16 <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_16;
    period_counts = target_counts / 16;
  } 
  else if (target_counts / 64 <= max_counts) 
  {
    source_div = TIMER_SOURCE_DIV_64;
    period_counts = target_counts / 64;
  } 
  else 
  {
    source_div = TIMER_SOURCE_DIV_256;
    period_counts = target_counts / 256;
  }

  uint32_t pulse_counts = (duty_value * period_counts) / (max_counts - 1);

  if (!pwm_timer.begin(TIMER_MODE_PWM, timer_type, channel, period_counts, pulse_counts, source_div, nullptr, nullptr)) 
  {
    Serial.println("PWM initialization failed!");
    while (1);
  }

  pwm_timer.open();
  pwm_timer.start();
  analogWriteResolution(resolution_bits);

  Serial.print("PWM set: ");
  Serial.print(frequency_hz);
  Serial.print(" Hz, ");
  Serial.print(resolution_bits);
  Serial.print("-bit, Duty: ");
  Serial.print((duty_value * 100.0) / (max_counts - 1));
  Serial.println("%");
}

/**
 * @brief Setup function for the Arduino Uno R4 WiFi.
 * 
 * Initializes the serial communication, sets up the PWM pin and motor direction,
 * and starts the PWM signal with an initial duty cycle.
 */
void setup() 
{
  Serial.begin(115200);
  while (!Serial) delay(10);

  pinMode(PWM_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  // Set motor direction: forward
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);

  // Initial PWM: 1 kHz, 8-bit, 78.431% duty cycle
  setupPWM(1000, 8, 200);
  analogWrite(PWM_PIN, 200);

  Serial.println("Setup complete. Testing Meccano ER20 motor.");
} // setup()

/**
 * @brief Main loop function for the Arduino Uno R4 WiFi.
 */
void loop() 
{
  // Test frequencies
  uint32_t frequencies[] = {5000, 1000, 500, 100};
  const int freq_count = 4;

  for (int f = 0; f < freq_count; f++) 
  {
    Serial.print("Testing frequency: ");
    Serial.print(frequencies[f]);
    Serial.println(" Hz");

    // Sweep duty cycle from 50 to 255 (19.6% to 100%)
    for (int duty = 50; duty <= 255; duty += 10) 
    {
      setupPWM(frequencies[f], 8, duty);
      analogWrite(PWM_PIN, duty);
      Serial.print("Duty cycle: ");
      Serial.print((duty * 100.0) / 255);
      Serial.println("%");
      delay(2000); // Allow motor to respond
    } // for

    // Pause between frequencies
    analogWrite(PWM_PIN, 0);
    Serial.println("Motor off");
    delay(3000);
  } // for
} // loop()