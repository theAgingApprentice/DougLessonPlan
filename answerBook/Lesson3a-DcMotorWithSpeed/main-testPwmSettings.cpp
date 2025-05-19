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

  Serial.print("PWM set: ");
  Serial.print(frequency_hz);
  Serial.print(" Hz, ");
  Serial.print(resolution_bits);
  Serial.print("-bit, Duty: ");
  Serial.print((duty_value * 100.0) / (max_counts - 1));
  Serial.println("%");
}

void setup() {
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
}

void loop() {
  // Test frequencies
  uint32_t frequencies[] = {5000, 1000, 500, 100};
  const int freq_count = 4;

  for (int f = 0; f < freq_count; f++) {
    Serial.print("Testing frequency: ");
    Serial.print(frequencies[f]);
    Serial.println(" Hz");

    // Sweep duty cycle from 50 to 255 (19.6% to 100%)
    for (int duty = 50; duty <= 255; duty += 10) {
      setupPWM(frequencies[f], 8, duty);
      analogWrite(PWM_PIN, duty);
      Serial.print("Duty cycle: ");
      Serial.print((duty * 100.0) / 255);
      Serial.println("%");
      delay(2000); // Allow motor to respond
    }

    // Pause between frequencies
    analogWrite(PWM_PIN, 0);
    Serial.println("Motor off");
    delay(3000);
  }
}