# PWM Control Experiment for Meccano ER20 Motor

## Overview

This project uses an **Arduino Uno R4 WiFi** development board to control a **Meccano ER20 hybrid AC/DC motor** through an **L298N motor driver**. The program, `main.cpp`, experiments with different PWM (Pulse Width Modulation) settings to determine the optimal frequency and duty cycle range for driving the ER20 motor, aiming to widen its responsive PWM range. A basic DC motor is also tested for comparison.

The Meccano ER20, a vintage hybrid AC/DC motor (likely from the 1950s, e.g., E20R model), is rated for 20V AC/DC. Initial tests at 12VDC showed the ER20 only spins at `analogWrite` values of 250 or higher (≥98% duty cycle, ~10V effective after L298N voltage drop), while a basic DC motor responds from `analogWrite(9, 20)` (~7.8% duty cycle). This program sweeps PWM frequencies (5 kHz, 1 kHz, 500 Hz, 100 Hz) and duty cycles (19.6%–100%) at supply voltages of 12V, 18V, and 20V to find settings that allow the ER20 to spin at lower duty cycles, improving speed control.

## Hardware Setup

- **Arduino Uno R4 WiFi**:
  - Microcontroller: RA4M1, 48 MHz peripheral clock.
  - Pin 9 (D9, P303, likely GPT0_GTIOCA): PWM output to L298N ENA pin for speed control.
  - Pin 7 (D7): L298N IN1 for motor direction.
  - Pin 8 (D8): L298N IN2 for motor direction.
- **L298N Motor Driver**:
  - VCC: Tested at 12V, 18V, and 20VDC.
  - 5V: Supplied from Arduino 5V pin (5V regulator jumper removed for VCC > 12V to prevent regulator overheating).
  - GND: Common with Arduino and power supply.
  - ENA: Connected to pin 9 (PWM).
  - IN1, IN2: Pins 7, 8 (set HIGH/LOW for forward).
  - OUT1, OUT2: Connected to Meccano ER20 motor.
- **Meccano ER20 Motor**:
  - Hybrid AC/DC motor, rated for 20V AC/DC.
  - Tested at 12V, 18V, 20VDC, with varying duty cycle thresholds.
- **Basic DC Motor** (for comparison):
  - Responds to a wider PWM range (e.g., `analogWrite(9, 20)` at all frequencies, ~0.94V effective at 12V).
- **Power Supply**:
  - 12V, 18V, 20VDC, 2–3A recommended.
  - Jumper removal required for VCC > 12V.
- **Tools**:
  - Saleae Logic Analyzer: Verifies PWM signals (frequency, duty cycle).
  - Serial Monitor: For debugging (115200 baud).
  - Excel Spreadsheet (`er20PwmTestResults.xlsx`): Contains test results.

## Software Overview

### File: `src/main.cpp`

#### Purpose
The program tests different PWM frequencies and duty cycles to find settings that allow the Meccano ER20 motor to spin at lower `analogWrite` values, improving its speed control range. It compares the ER20’s behavior to a basic DC motor, which responds more readily to PWM.

#### Functionality
- **PWM Configuration**:
  - Uses the `FspTimer` class (ArduinoCore-renesas framework) to configure PWM on pin 9.
  - Tests frequencies: 5 kHz, 1 kHz, 500 Hz, 100 Hz.
  - Resolution: 8-bit (256 levels, 0–255).
  - Duty cycle sweep: 19.6% (`analogWrite(9, 50)`) to 100% (`analogWrite(9, 255)`).
- **Motor Control**:
  - Sets motor direction to forward (IN1 HIGH, IN2 LOW).
  - Sweeps duty cycles at each frequency to find the lowest value where the ER20 spins.
- **Debugging**:
  - Outputs frequency and duty cycle to Serial Monitor (115200 baud).
  - 2-second delay per duty cycle step to allow motor response.
  - 3-second pause between frequency tests (motor off).

#### Key Functions
- **`setupPWM(uint32_t frequency_hz, uint8_t resolution_bits, uint16_t duty_value)`**:
  - Configures PWM using `FspTimer`:
    - Calculates prescaler and period: `f_PWM = 48,000,000 ÷ (Prescaler × Period)`.
    - Sets duty cycle: `pulse_counts = (duty_value * period_counts) / (max_counts - 1)`.
    - Starts PWM on pin 9.
  - Prints settings to Serial (e.g., “PWM set: 1000 Hz, 8-bit, Duty: 78.43%”).
- **`setup()`**:
  - Initializes Serial, pins, and sets initial PWM (1 kHz, 8-bit, 78.43% duty cycle).
- **`loop()`**:
  - Loops through frequencies, sweeping duty cycles from 50 to 255 at each frequency.

#### Default PWM (Without Code)
- Frequency: 489.4 Hz (measured previously).
- Prescaler: 256, Period: ~383 (`48,000,000 ÷ (256 × 383) ≈ 489.4 Hz`).

### Test Results (`er20PwmTestResults.xlsx`)

The spreadsheet records the lowest duty cycle (%) at which the ER20 spins across three test runs for each combination of voltage (12V, 18V, 20V) and frequency (5 kHz, 1 kHz, 500 Hz, 100 Hz), with 8-bit resolution. Saleae measurements confirm PWM frequencies.

| Voltage (VDC) | Frequency (Hz) | Saleae Reading (Hz) | Lowest Duty Cycle (%) | `analogWrite` Value | Effective Voltage (After ~2V L298N Drop) |
|---------------|----------------|---------------------|-----------------------|---------------------|-------------------------------------------|
| 12            | 5000           | 4996                | 90.20–94.12 (Avg: 91.51) | 230–240 (Avg: 234) | ~9.78V–10.09V                            |
| 12            | 1000           | 1002                | 86.27–90.20 (Avg: 87.58) | 220–230 (Avg: 223) | ~9.35V–9.62V                             |
| 12            | 500            | 499.6               | 82.35–86.27 (Avg: 84.96) | 210–220 (Avg: 217) | ~8.88V–9.15V                             |
| 12            | 100            | 99.91               | 66.67 (All Tests)        | 170                 | ~7.00V                                   |
| 18            | 5000           | 4996                | 66.67–74.51 (Avg: 71.90) | 170–190 (Avg: 183) | ~10.78V–11.50V                           |
| 18            | 1000           | 1002                | 66.67–78.43 (Avg: 71.90) | 170–200 (Avg: 183) | ~10.78V–12.55V                           |
| 18            | 500            | 499.6               | 66.67–74.51 (Avg: 70.59) | 170–190 (Avg: 180) | ~10.59V–11.29V                           |
| 18            | 100            | 99.91               | 31.37–39.22 (Avg: 33.99) | 80–100 (Avg: 87)   | ~4.71V–5.66V                             |
| 20            | 5000           | 4996                | 66.67 (All Tests)        | 170                 | ~12.00V                                  |
| 20            | 1000           | 1002                | 66.67 (All Tests)        | 170                 | ~12.00V                                  |
| 20            | 500            | 499.6               | 66.67 (All Tests)        | 170                 | ~12.00V                                  |
| 20            | 100            | 99.91               | 27.45 (All Tests)        | 70                  | ~4.94V                                   |

#### Key Findings
- **Optimal Settings**:
  - **20V, 100 Hz**: Lowest duty cycle = 27.45% (`analogWrite(9, 70)`), or ~4.94V effective, offering the widest range (70–255, 27.45%–100%).
  - **18V, 100 Hz**: Lowest duty cycle = 33.99% (`analogWrite(9, 87)`), or ~5.10V effective, also effective (87–255, 33.99%–100%).
- **Voltage Impact**:
  - Higher voltage reduces the duty cycle threshold (e.g., 66.67% at 12V, 100 Hz vs. 27.45% at 20V, 100 Hz), as 20V matches the ER20’s rated voltage.
- **Frequency Impact**:
  - 100 Hz consistently yields the lowest duty cycle threshold across all voltages, improving current delivery to the ER20’s windings.
  - 5 kHz performs worst, requiring higher duty cycles (e.g., 91.51% at 12V).
- **Comparison to DC Motor**:
  - A basic DC motor spins at `analogWrite(9, 20)` (7.8%, ~0.94V at 12V) across all frequencies, showing a much wider range than the ER20 (e.g., 20–255 vs. 70–255 at 20V, 100 Hz).

### Why the Meccano ER20 Has a Narrower PWM Response Range

The Meccano ER20, a hybrid AC/DC motor (likely a series-wound universal motor from the 1950s), exhibits a narrower PWM response range compared to a typical DC motor due to several factors, confirmed by the test results:

1. **Design and Voltage Rating**:
   - The ER20 is rated for 20V AC/DC. At 12V, the effective voltage after the L298N’s ~2V drop (e.g., ~10V at 100% duty cycle) is well below its rating, requiring a high duty cycle (e.g., 66.67% at 100 Hz, ~7V) to generate sufficient torque.
   - At 20V, the threshold drops to 27.45% (~4.94V), as the supply matches the motor’s rating, but this is still higher than a DC motor’s ~0.94V threshold.
   - **Comparison**: A basic DC motor (e.g., 3–12V hobby motor) has a lower torque threshold, spinning at ~0.94V (7.8% duty cycle).

2. **Torque and Current Requirements**:
   - Universal motors like the ER20 rely on high current through series-wound coils to produce torque. At lower duty cycles (e.g., 31.37% at 18V, 100 Hz, ~4.71V), the current is insufficient to overcome friction or inertia, especially at 12V.
   - **Comparison**: DC motors have simpler armature designs with lower current/torque thresholds, responding at much lower voltages.

3. **PWM Frequency Sensitivity**:
   - The ER20’s inductance causes inefficient current delivery at high frequencies (e.g., 5 kHz requires 91.51% duty cycle at 12V). Lower frequencies (100 Hz) allow better current buildup, reducing the threshold to 27.45% at 20V.
   - **Comparison**: Modern DC motors are less sensitive to frequency, operating well at 1–20 kHz with no significant threshold change.

4. **Mechanical Factors**:
   - As a vintage motor, the ER20 may have increased friction, worn brushes, or internal resistance, raising the torque needed to start spinning. This contributes to its high duty cycle requirement (e.g., 66.67% at 12V, 100 Hz vs. 7.8% for a DC motor).
   - **Comparison**: A new DC motor has lower friction and better brush contact, starting more easily.

5. **L298N Voltage Drop**:
   - The L298N’s ~2V drop reduces effective voltage. At 12V, 66.67% duty cycle yields ~7V, but at 20V, 27.45% yields ~4.94V, showing how higher supply voltage helps.
   - **Comparison**: A DC motor’s lower threshold makes it less affected by the drop.

### Usage Instructions

1. **Setup Hardware**:
   - Connect the L298N as described above.
   - Use a 20VDC supply for optimal ER20 performance (jumper removed, L298N 5V to Arduino 5V pin).
   - Attach Saleae Logic Analyzer to pin 9 and GND to verify PWM.

2. **Build and Upload**:
   - Navigate to the project directory:
     ```bash
     cd /Users/andrewmitchell/Documents/visualStudioCode/platformio/projects/DougLessonPlan
     ```
   - Clean and build:
     ```bash
     pio run -t clean
     pio run
     ```

3. **Run Tests**:
   - Open Serial Monitor (115200 baud) to view frequency and duty cycle outputs.
   - Observe the ER20 motor’s response at each duty cycle and frequency.
   - Use Saleae to verify PWM (e.g., 100 Hz, 27.45% duty cycle: period = 10 ms, HIGH = 2.745 ms).
   - Record results in `er20PwmTestResults.xlsx`.

4. **Analyze Results**:
   - Optimal setting: 20V, 100 Hz, duty cycle range 27.45%–100% (`analogWrite(9, 70)` to 255).
   - Compare ER20 and DC motor responses (DC motor: 7.8%–100%).

### Recommendations for Improving ER20 PWM Range

1. **Fix Optimal Settings**:
   - Use 20V, 100 Hz for the widest range (27.45%–100%):
     ```cpp
     setupPWM(100, 8, 70); // 100 Hz, 8-bit, 27.45%
     ```
   - Test 10-bit resolution for finer control:
     ```cpp
     setupPWM(100, 10, 281); // 100 Hz, 10-bit, ~27.45% (281/1023)
     ```

2. **Use a MOSFET Driver**:
   - Replace the L298N with a MOSFET (e.g., IRF520) to reduce voltage drop (~0.5V vs. 2V):
     - Gate: Pin 9 (PWM).
     - Drain: ER20 (other terminal to 20V).
     - Source: GND.
     - Flyback diode across ER20.
   - At 20V, 27.45% duty cycle → ~5.44V (vs. 4.94V with L298N).

3. **Motor Maintenance**:
   - Inspect the ER20 for worn brushes, friction, or dirt. Clean and lubricate to reduce torque requirements.

4. **Direct DC Control**:
   - If PWM range remains insufficient, use a variable DC supply (10–20V) for smoother ER20 control, bypassing PWM limitations.

### Limitations

- **ER20 Design**: Its high torque threshold (20V rating, universal motor design) limits PWM responsiveness, even at 20V (27.45% vs. DC motor’s 7.8%).
- **L298N**: Voltage drop restricts effective voltage. A MOSFET driver can help.
- **PWM Frequency**: Very low frequencies (<100 Hz) may cause vibration or noise in the ER20.

### Future Work

- Test with a MOSFET driver for better voltage delivery.
- Experiment with 10-bit resolution for finer speed control.
- Add reverse direction testing by toggling IN1/IN2.
- Assess ER20 mechanical condition to reduce torque threshold.

## License

Copyright © 2025 theAgingApprntice. All rights reserved.