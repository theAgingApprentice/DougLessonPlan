/**
 * @file main.cpp
 * @author theAgingApprntice
 * @brief PWM Motor Control Test for Arduino Uno R4 WiFi Pin 9
 * @version 0.4
 * @date 2025-05-18
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h>
#include <FspTimer.h>

#define PWM_PIN 9   // D9, P303, likely GPT0_GTIOCA (ENA for L298N)
#define IN1_PIN 7   // D7, controls motor direction
#define IN2_PIN 8   // D8, controls motor direction

FspTimer pwm_timer;

void setupPWM(uint32_t frequency_hz, uint8_t resolution_bits, uint16_t duty_value) {
  pwm_timer.stop();
  pwm_timer.close();

  uint8_t timer_type = GPT_TIMER;
  uint8_t channel = GET_CHANNEL(getPinCfgs(PWM_PIN, PIN_CFG_REQ_PWM)[0]);

  uint32_t max_counts = (1UL << resolution_bits);
  uint32_t clock_freq = 48000000UL;
  uint32_t target_counts = clock_freq / frequency_hz;
  timer_source_div_t source_div = TIMER_SOURCE_DIV_1;
  uint32_t period_counts = max_counts;

  if (target_counts <= max_counts) {
    source_div = TIMER_SOURCE_DIV_1;
    period_counts = target_counts;
  } else if (target_counts / 4 <= max_counts) {
    source_div = TIMER_SOURCE_DIV_4;
    period_counts = target_counts / 4;
  } else if (target_counts / 16 <= max_counts) {
    source_div = TIMER_SOURCE_DIV_16;
    period_counts = target_counts / 16;
  } else if (target_counts / 64 <= max_counts) {
    source_div = TIMER_SOURCE_DIV_64;
    period_counts = target_counts / 64;
  } else {
    source_div = TIMER_SOURCE_DIV_256;
    period_counts = target_counts / 256;
  }

  uint32_t pulse_counts = (duty_value * period_counts) / (max_counts - 1);

  if (!pwm_timer.begin(TIMER_MODE_PWM, timer_type, channel, period_counts, pulse_counts, source_div, nullptr, nullptr)) {
    Serial.println("PWM initialization failed!");
    while (1);
  }

  pwm_timer.open();
  pwm_timer.start();
  analogWriteResolution(resolution_bits);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for Serial

  // Initialize pins
  pinMode(PWM_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  // Set motor direction (forward)
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);

  // Setup PWM: 5 kHz, 8-bit, 78.431% duty cycle (200/255)
  setupPWM(5000, 8, 200);
  analogWrite(PWM_PIN, 200); // 78.431% duty cycle

  // Test 20 kHz, 10-bit later (uncomment to try)
  // setupPWM(20000, 10, 800);
  // analogWrite(PWM_PIN, 800);

  Serial.println("PWM initialized: 5 kHz, 8-bit, 78.431% duty cycle");
}

void loop() {
  // Test different duty cycles
  Serial.println("Duty cycle: 50%");
  analogWrite(PWM_PIN, 128); // 50%
  delay(2000);

  Serial.println("Duty cycle: 78.431%");
  analogWrite(PWM_PIN, 200); // 78.431%
  delay(2000);

  // Test direction change (reverse)
  Serial.println("Reversing motor");
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  delay(2000);

  // Back to forward
  Serial.println("Forward motor");
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  delay(2000);
}