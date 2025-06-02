/**
 * @file main.cpp
 * @author theAgingApprntice
 * @brief Motor Control Test for ESP32
 * @version 0.2
 * @date 2025-05-17
 * @copyright Copyright (c) 2025
 */
#include <Arduino.h> // Standard Arduino library
#include <Wire.h> // Two wire protocol used by I2C
#include <LiquidCrystal_I2C.h> // Library for I2C controlled LCDs
#include <ESP32RotaryEncoder.h> // Library for rotary encoder support

// Pinout planning for ESP32 Feather Huzzah32
// See https://www.espboards.dev/esp32/featheresp32/
// See also https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts
// Our map
// Phy Pin  GPIO  Pin Name  Use
// =======  ===== ========  =================== 
//  1       N/A   Reset     Not GPIO accessible 
//  2       N/A   3.3V      Not GPIO accessible
//  3       N/A   N/C       Not GPIO accessible
//  4       N/A   GND       Not GPIO accessible
//  5       26    A0        Right joystick X-axis (VRX)
//  6       25    A1        Right joystick Y-axis (VRY)
//  7       34    A2        Left joystick switch (SW)
//  8       39    A3        Left joystick X-axis (VRX)
//  9       36    A4        Left joystick Y-axis (VRY)
// 10       4     A5        RGB red LED
// 11       5     SCK       RGB blue LED
// 12       18    MOSI      Not used
// 13       19    MISO      Not used
// 14       16    D16       Not used
// 15       17    D17       Not used
// 16       21    D21       Right joystick switch (SW)
// 17       23    SDA       I2C bus SDA
// 18       22    SCL       I2C bus SCL
// 19       14    D14       Rotary encoder B
// 20       32    D32       RGB green LED
// 21       15    D15       Not used
// 22       33    D33       Rotary encoder switch (SW)
// 23       27    D27       Rotary encoder A
// 24       12    D12       Not used
// 25       13    D13       Not used (onboard LED)
// 26       N/A   VBUS      Not GPIO accessible
// 27       N/A   EN        Not GPIO accessible
// 28       N/A   VBAY=T    Not GPIO accessible

// LCD and I2C pin definitions
#define LCD_ADDRESS 0x38 // I2C address for LCD
#define SDA_PIN 23 // SDA pin for I2C (Physical pin 17, GPIO 23)
#define SCL_PIN 22 // SCL pin for I2C (Physical pin 18, GPIO 22)
#define LCD_COLS 16 // Number of columns on the LCD
#define LCD_ROWS 2 // Number of rows on the LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS); // Set the LCD address for a 16 chars and 2 line display

// Rotary Encoder pin definitions
const uint8_t DI_ENCODER_A = 27; // Digital Input pin for Encoder A (CLK) (Physical pin 23, GPIO 27)
const uint8_t DI_ENCODER_B = 14; // Digital Input pin for Encoder B (DT) (Physical pin 19, GPIO 14)
const int8_t DI_ENCODER_SW = 33; // Digital Input pin for Encoder Switch (SW) (Physical pin 22, GPIO 33)

RotaryEncoder rotaryEncoder(DI_ENCODER_A, DI_ENCODER_B, DI_ENCODER_SW); // Create RotaryEncoder object

// Left Joystick pin definitions
int L_VRX_PIN = 39; // ESP32 pin GPIO39 (ADC3) (physical pin 8) connected to VRX pin on joystick
int L_VRY_PIN = 36; // ESP32 pin GPIO36 (ADC0) (physical pin 9) connected to VRY pin on joystick
int L_SW_PIN = 34; // ESP32 pin GPIO17 (D17) (physical pin 7) connected to SW on joystick

// Right Joystick pin definitions
int R_VRX_PIN = 26; // ESP32 pin GPIO26 (A0) (physical pin 5) connected to VRX pin on joystick
int R_VRY_PIN = 25; // ESP32 pin GPIO25 (A1) (physical pin 6) connected to VRY pin on joystick
int R_SW_PIN = 21; // ESP32 pin GPIO21 (D21) (physical pin 16) connected to SW on joystick

// RGB pin definitions for power switch LED
#define RGB_GREEN_PIN 32 // ESP32 pin GPIO32 (A2) (physical pin 20) connected to green LED
#define RGB_RED_PIN 4 // ESP32 pin GPIO4 (A5) (physical pin 10) connected to red LED
#define RGB_BLUE_PIN 5 // ESP32 pin GPIO5 (SCK) (physical pin 11) connected to blue LED

// Global variables for left joystick state and debouncing
int valueX_L = 0; // To store the X-axis value
int valueY_L = 0; // To store the Y-axis value
int bValue_L = 0; // To store value of the button (0 = pressed, 1 = released for INPUT_PULLUP)
int prevValueX_L = 0; // Previous X-axis value
int prevValueY_L = 0; // Previous Y-axis value
int prevBValue_L = 0; // Previous button value
unsigned long lastDebounceTime_L = 0; // Last time the button state changed
const unsigned long debounceDelay_L = 50; // Debounce delay in milliseconds
int lastButtonState_L = HIGH; // Last read state of the button

// Global variables for right joystick state and debouncing
int valueX_R = 0; // To store the X-axis value
int valueY_R = 0; // To store the Y-axis value
int bValue_R = 0; // To store value of the button (0 = pressed, 1 = released for INPUT_PULLUP)
int prevValueX_R = 0; // Previous X-axis value
int prevValueY_R = 0; // Previous Y-axis value
int prevBValue_R = 0; // Previous button value
unsigned long lastDebounceTime_R = 0; // Last time the button state changed
const unsigned long debounceDelay_R = 50; // Debounce delay in milliseconds
int lastButtonState_R = HIGH; // Last read state of the button

/**
 * @brief Initializes serial communication.
 */
void setupSerial() 
{
  Serial.begin(115200);
  while (!Serial) 
  {
    // Wait for Serial Monitor
  } // while
} // setupSerial()

/**
 * @brief Scan I2C bus to see what is connected.
 */
void scanI2cBus() 
{
  byte error, address;
  int nDevices;
  Serial.println("<scanI2cBus> Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) 
    {
      Serial.print("<scanI2cBus> I2C device found at address 0x");
      if (address < 16) 
      {
        Serial.print("0");
      } // if
      Serial.println(address, HEX);
      nDevices++;
    } // if
    else if (error == 4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16) 
      {
        Serial.print("0");
      } // if
      Serial.println(address, HEX);
    } // else if
  } // for
  if (nDevices == 0) 
  {
    Serial.println("No I2C devices found\n");
  } // if
  else 
  {
    Serial.println("done\n");
  } // else
} // scanI2cBus() 

/**
 * @brief Callback function for rotary encoder.
 * 
 * @param value The value of the rotary encoder.    
 */
void knobCallback(long value)
{
  Serial.printf("<knobCallback> Value: %ld\n", value);
} // knobCallback()

/**
 * @brief Callback function for button press on rotary encoder.
 * 
 * @param duration The duration in milliseconds that the button was pressed.
 */
void buttonCallback(unsigned long duration)
{
  Serial.printf("<buttonCallback> boop! button was down for %lu ms\n", duration); 
} // buttonCallback()

/**
 * @brief Initializes the LCD.
 */
void setupLCD()
{
  lcd.init(); // Initialize the LCD
  lcd.clear(); // Clear the screen
  lcd.noBacklight(); // Turn off the backlight
  delay(1000); // Wait for 1 second
  lcd.backlight(); // Turn on the backlight
  int column = 0; // Initialize column variable
  int row = 0; // Initialize row variable
  lcd.setCursor(column, row); // Set cursor to desired column and row
  lcd.print(" Meccano Remote"); // Display message on LCD
  row = 1; // Jump to second row
  lcd.setCursor(column, row); // Set cursor to desired column and row
  lcd.print(" Firmware V1.0"); // Display message on LCD
} // setupLCD()

/**
 * @brief Initializes the rotary encoder.
 */
void setupRotaryEncoder() 
{
  rotaryEncoder.setEncoderType(EncoderType::HAS_PULLUP);
  rotaryEncoder.setBoundaries(1, 10, true);
  rotaryEncoder.onTurned(&knobCallback);
  rotaryEncoder.onPressed(&buttonCallback);
  rotaryEncoder.begin();
} // setupRotaryEncoder()

/**
 * @brief Initializes the left joystick button.
 */
void setUpLeftJoystickButton()
{
  pinMode(L_SW_PIN, INPUT_PULLUP); // Set L_SW_PIN as input with internal pull-up
  analogSetAttenuation(ADC_11db); // Set ADC attenuation for VRX and VRY pins
} // setUpLeftJoystickButton()

/**
 * @brief Initializes the right joystick button.
 */
void setUpRightJoystickButton()
{
  pinMode(R_SW_PIN, INPUT_PULLUP); // Set R_SW_PIN as input with internal pull-up
  analogSetAttenuation(ADC_11db); // Set ADC attenuation for VRX and VRY pins
} // setUpRightJoystickButton()

/**
 * @brief Initializes the RGB LED pins.
 * @todo Fix colouring
 *  Red 255, green 255, blue 0 = blue <-- correct
 *  Red 255, green 0, blue 255 = Black <--- incorrect, should be green. Need analog GPIO pin
 *  Red 0, green 255, blue 255 = red <-- correct
 */
void setupRgbLed()
{
  pinMode(RGB_RED_PIN, OUTPUT); // Set RGB red pin as output
  pinMode(RGB_GREEN_PIN, OUTPUT); // Set RGB green pin as output
  pinMode(RGB_BLUE_PIN, OUTPUT); // Set RGB blue pin as output
  analogWrite(RGB_RED_PIN, 255); // Set red LED
  analogWrite(RGB_GREEN_PIN, 0); // Set green LED
  analogWrite(RGB_BLUE_PIN, 255); // Set blue LED
} // setupRgbLed()

/**
 * @brief Checks the state of the left joystick and updates the serial output.
 */
void checkLeftJoystick()
{
  // Read left joystick X and Y values
  valueX_L = analogRead(L_VRX_PIN);
  valueY_L = analogRead(L_VRY_PIN);
  
  // Read button with debouncing
  int reading = digitalRead(L_SW_PIN);
  if (reading != lastButtonState_L) 
  {
    lastDebounceTime_L = millis(); // Record time of state change
  } // if
  if (millis() - lastDebounceTime_L > debounceDelay_L) 
  {
    if (reading != bValue_L) 
    {
      bValue_L = reading;
      if (bValue_L == LOW) // Active-low button (pressed)
      { 
        Serial.println("<loop> The leftJoystickButton is pressed");
      } // if
      else // Released
      { 
        Serial.println("<loop> The leftJoystickButton is released");
      } // else
    }
  }
  lastButtonState_L = reading;
  
  // Print joystick state only if X, Y, or button value has changed
  if (valueX_L != prevValueX_L || valueY_L != prevValueY_L || bValue_L != prevBValue_L) 
  {
    Serial.print("<loop> x = ");
    Serial.print(valueX_L);
    Serial.print(", y = ");
    Serial.print(valueY_L);
    Serial.print(" : leftJoystickButton = ");
    Serial.println(bValue_L);
    
    prevValueX_L = valueX_L;
    prevValueY_L = valueY_L;
    prevBValue_L = bValue_L;
  } // if
} // checkLeftJoystick()

/**
 * @brief Checks the state of the right joystick and updates the serial output.
 */
void checkRightJoystick()
{
  // Read right joystick X and Y values
  valueX_R = analogRead(R_VRX_PIN);
  valueY_R = analogRead(R_VRY_PIN);
  
  // Read button with debouncing
  int reading = digitalRead(R_SW_PIN);
  if (reading != lastButtonState_R) 
  {
    lastDebounceTime_R = millis(); // Record time of state change
  } // if
  if (millis() - lastDebounceTime_R > debounceDelay_R) 
  {
    if (reading != bValue_R) 
    {
      bValue_R = reading;
      if (bValue_R == LOW) // Active-low button (pressed)
      { 
        Serial.println("<loop> The rightJoystickButton is pressed");
      } // if
      else // Released
      { 
        Serial.println("<loop> The rightJoystickButton is released");
      } // else
    }
  }
  lastButtonState_R = reading;
  
  // Print joystick state only if X, Y, or button value has changed
  if (valueX_R != prevValueX_R || valueY_R != prevValueY_R || bValue_R != prevBValue_R) 
  {
    Serial.print("<loop> x = ");
    Serial.print(valueX_R);
    Serial.print(", y = ");
    Serial.print(valueY_R);
    Serial.print(" : rightJoystickButton = ");
    Serial.println(bValue_R);
    
    prevValueX_R = valueX_R;
    prevValueY_R = valueY_R;
    prevBValue_R = bValue_R;
  } // if
} // checkRightJoystick()

/**
 * @brief Setup function.
 */
void setup() 
{
  setupSerial();
  Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C bus
  scanI2cBus(); // Scan the I2C bus for devices
  setupLCD(); // Initialize the LCD
  Serial.println("<setup> LCD initialized.");
  setupRotaryEncoder(); // Initialize the rotary encoder
  Serial.println("<setup> Rotary encoder initialized.");
  setUpLeftJoystickButton(); // Initialize the left joystick button
  Serial.println("<setup> Left joystick button initialized.");
  setUpRightJoystickButton(); // Initialize the left joystick button
  Serial.println("<setup> Right joystick button initialized.");
  setupRgbLed(); // Initialize the RGB LED pins
  Serial.println("<setup> RGB LED pins initialized.");
  Serial.println("<setup> End of setup.");
} // setup()

/**
 * @brief Main loop.
 */
void loop() 
{
  checkLeftJoystick(); // Check left joystick state
  checkRightJoystick(); // Check right joystick state
  delay(100); // Add a small delay to avoid flooding the serial output
} // loop()