// Send message to I2C 16x2 LCD diplay
//
// Wiring for HUZZAH32 Feather:
//   SDA: GPIO23 (physical pin 17, labeled "SDA" on the board)
//   SCL: GPIO22 (physical pin 18, labeled "SCL" on the board)
//
// Connect your I2C device's SDA and SCL lines to these pins.
//
// Open the Serial Monitor at 115200 baud to view the results.

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object for 16x2 display at I2C address 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);

/**
 * @brief STandrad Arduino setup funciotn that runs at the start of the program.
 */
void setup() 
{
  // Initialize I2C bus on the correct pins for HUZZAH32 Feather
  // Wire.begin(SDA, SCL):
  //   SDA = GPIO23
  //   SCL = GPIO22
  Wire.begin(23, 22); 

  // Start serial communication at 115200 baud
  Serial.begin(115200);
 
  // Wait for Serial Monitor to open (not always needed, but good for USB serial)
  while (!Serial) 
  {
    delay(10); // Wait for Serial to be ready
  } //while()
  Serial.println("\nI2C Scanner ready");

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0); // First column, first row
  lcd.print("Hello, World!");
} // setup()

/**
 * @brief Standard Arduino main routine.
 */
void loop() 
{
} // loop()
