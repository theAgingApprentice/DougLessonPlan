# Doug's Arduino Lesson Plan
Material to help learn Arduino programming using the Arduino Uno R4 Wifi dev board.

## Lesson 1: Hello World
Goal: 
Write a program that send the "end of start" in the setup() function and "hello world" in loop() function to the Arduino console. 

New things to learn: 
1. Arduino code structure.
2. Arduino syntax for uisng the serial port.
4. Compiling code.
5. Uploading code via UART.
6. Viewing Serial output.
7. Learn to use the **Serial.println()** command. 
9. Learn to use the **delay()** command. 

Required items: 
1. [Arduno Uno R4 Wifi](https://www.amazon.ca/Arduino-ABX00087-Official-Board-Italy/dp/B0C8V88Z9D/ref=sr_1_5?crid=25PE4DK5C38OD&dib=eyJ2IjoiMSJ9.2C2r60sxjDv1lKq7jkut_pSbIryvHsYkyf0J7IWNHNnRGCLcc2S4OeShbkkdgIz64YwuVZNIvTaut2G_rKaewZbHFYwF2VbEvhvFyr4OXtV9PLSq9MenofSxI9POgnxxBIExQaeblsTEvPg4OT19uA6PYe-CV5RfooweX0ESMpWZrD3eAfJIC9zZ9XzOymIV1kK6YJyw13aN2yNNGw_epRKhMSAROgsRCPhQ6cral57MeXIURSUEvbd8taEpRqMwEovgCIz5F4lFo4v2P8258hTCmVmbJEx2crV7H2rUlqL43wnp3vjkFgmx-fya-PgspmCfHlUWtEwBI6WLq_W6jS9tUN7RwK09uE-7646wYBRAflSpuEXUNrYhowbeMpswa2CjwVAf42-oCaVud8Svqwnoh_nR-PcGUV5iPKH69QZfZPMoBG7XEMHSyFNPEs4x.FbSCzKeln0W7Zh_mlwpCwvopZ517UPK0MPHxmwlx2QU&dib_tag=se&keywords=Arduino+UNO+R4+wifi&qid=1739421207&sprefix=arduino+uno+r4+wifi%2Caps%2C124&sr=8-5) development board. Cheaper clones exists too.
2. A [USB-A to USB-C cable](https://www.amazon.ca/dp/B07DC5PPFV?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1). 
3. The Arduino IDE on your computer.

Wiring required:
There is no wiring required for this lesson.

OK, now you are all set to write your code. Good luck! Hint: You can look at a working example of this code in the answerBook directory if you need help. 

## Lesson 2: Analog Input
Goal: 
Write a program that interprets the joystick input.

New things to learn: 
1. Learn what an **Analog GPIO pin** is.
2. Learn to use the **pinMode()** command.
3. Learn to use the **analogRead()** command.
4. Learn to use the **if()** command.
5. Learn how to refer to the GPIO pins on the development board in your program.

Required items: 
1. Items  from lesson 1, plus
2. A [breadboard and some 24AWG wires](https://www.amazon.ca/Breadboards-Include-Solderless-Jumper-Tweezer/dp/B0BMFXPSVG/ref=sr_1_1_sspa?crid=2ZQ3F5LIOJUHK&dib=eyJ2IjoiMSJ9.1ijnFBfQCFFj2mXhrzrvG4C0_ilj_cGur_qb6AYxPYIYboV72KZnPjl0qEtnzHGbZCBec-AxHOmntukMX6IFXOhOuCrZ6I1oHsojScPtcuF-La4qqqaWKMkemFXWFMhyMnFBk-1mB6-oYbc46RlI625DMlXjmV8yFlsMkxy2Vx_DClSKii0lTYq2PtpO4RAIGswv0gKYodHkHQz8TKEPlDeAQFxJ_i4CcrTZ3Jwe2NN-5aEp0jzg8zEnsO89jxEa5pBKub_3z9wHAI3GSGk1q5XFnObRG1ecGJ3YTlxNqbE.sY_nlNVywq5ArWQKWY7ts-U45I-cBs26XYe6diIOYBQ&dib_tag=se&keywords=breadboard&qid=1739423112&sprefix=breadboard%2Caps%2C112&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1) 
3. A little [PS2 joystick](https://www.amazon.ca/dp/B089VXPHDH?ref=ppx_yo2ov_dt_b_fed_asin_title).

Wiring required:
For this lesson you must connect the joystick to the Arduino board. Here are the connections to make:

1. Connect GND pin on the joystick to a GND pin on the Arduino board.
2. Connect +5V pin on the joystick to the 5V pin on the Ardino board.
3. Connect the VRX pin on the joystick to the A0 pin on the Arduino board.
4. Connect the VRY pin on the joystick to the A1 pin on the Arduino board. 
5. Connect the SW pin on the joystick to the A2 pin on the Arduino board. 

OK, now you are all set to write your code. Good luck! Hint: You can look at a working example of this code in the answerBook directory if you need help. 

## Lesson 3: DC Motor Control
Goal: 
Write a program that spins the shaft of a DC motor.

New things to learn: 
1. Learn how to wire up a motor to your develpoment board using a motor controller.
2. Learn to use the **#define** precompiler macro.
3. Learn to use the **digitalWrite()** command.
4. Learn about the different pins that are available to you. 

Required items: 
1. The items from lesson 1 and 2 plus
2. An electric motor. In our case we will be using the Meccano ER20 universal motor.
3. A [motor controller board](https://www.amazon.ca/hz/mobile/mission?p=NxaXGg4uaBAdUdbX2Ljs300fa2coZlhjr3dNuuM5PCdiR0lDZ3t90FeAFzGH2JxPPMFTkses0GJLsMWubWuqkzRPjA0FwpmP6GJyK6POBSueaKvad25T82iYaHXfiQs2ZIYcnh%2BDPZ0ayiOWRrkdF0Y%2B8HyVha2edsa9T8qbmhtwv1p3cvp1WUQDjh899QcxUxliRyi1Wh0YaB%2FwqzdyqfkUOaxXdiGQsqUwThcphtrwi9n%2FinmWDyu7B%2FoOPYlplk%2FUEbCZ1ZkkNyUnoBtoXjbzqNfvVVO30XrJhSataTkXqubi5s%2Fn7TVOoL0YXfFyFLCUr%2F4iF0Xyn5z7eSnrV33WE8Hko4bUp%2BruZmBP3fepvi96OW%2F%2FldB00vooYBYWGYMmGxFn5pXBBYFEivd6DYTJrCPppWMvBlcYwShYLsxbWfIEQ5520A%3D%3D&ref_=nb_sb_ss_di_ci_mcx_mi_ci-mcx-ksf-of-nv1_0&crid=35R3PKF89TKK2).
4. A [logic level converter](https://www.amazon.ca/dp/B07LG646VS?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_8).
5. Some [Lever nut wire connectors](https://www.amazon.ca/Compact-Splicing-Connector-Assortment-221-2401/dp/B0BXQRVNHL/ref=sr_1_3_sspa?crid=2HY7JRA2TARDH&dib=eyJ2IjoiMSJ9.wNnWW0kKuQegTHCL7k_22gBOEuUrfk8M4S6myRwcThXojkmWagmGioBwikISHTg1PD_DeDJ5gvk1_nIAYoq4HGiEgzLlXIFk-n2yi8SSceBmHJIBiiTvKc_UhbG2VFx3jcPB3AIHlGtFeUwzxRnkYoq01PlpEBUi2X8VEs9FNgze172hEXBjBijL3H-md2a7dTf4EETwhHwj4psiLmYccZgri9k7sm4xmgGqS721vtIS-xAxWD_UJNhJMsAVkB6AkD6yexDwV9UOwr5OPPvoDX34Xx59MmznXMfxyEJCVgo.SN2RZ4ECV-xk9qOugLByuFbgJpnTTPvHizxpOxxXsVs&dib_tag=se&keywords=wire%2Bconnector&qid=1739630460&sprefix=wire%2Bconnector%2Caps%2C118&sr=8-3-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1).

Wiring required:
For this lesson you must connect the joystick to the Arduino board. Here are the connections to make:

1. Connect IN1 pin on the motor controller board to the B2 pin on the line level converter board.
2. Connect IN2 pin on the motor controller board to the B3 pin on the line level converter board.
3. Connect the ENA pin on the motor controller board to the B1 pin on the line level converter board.
4. Connect the 5V terminal on the motor controller board to the 5V rail on your bread board (you decide which one to use).
5. Connect the GND terminal on the motor controller board to both the GND rail next to the 5V rail on your bread board as well as to the GND wire from your power source (use a 3 way lever nut).
6. Connect the OUT1 terminal on the motor controller board to one of the termnal on your motor.
7. Connect the OUT2 terminal on the motor controller board to one of the termnal on your motor.
8. Connect the 3.3V pin of the Arduino board to 3V rail of your breadboard (you decide which one to use).
9. Connect a GND pin on your Arduino board to the GND rail on your bread board associated with the 3V rail that you selected. 
10. Connect the LV in pin of the line level converter board to the 3V power rail of your bread board.
11. Connect the HV pin on the line level converter board to the 5V power rail of your bread board.  
12. Connect the GND pin on the "B side" of the line level converter board to the GND rail beside the 5V rail of your bread board. 
13. Connect the GND pin on the "A side" of the line level converter board to the GND rail beside the 3V rail of your bread board.
14. Connect the A1 pin on the line level converter board to the A5 pin on the Arduino board. 
15. Connect the A2 pin on the line level converter board to the A4 pin on the Arduino board. 
16. Connect the A3 pin on the line level converter board to the A3 pin on the Arduino board. 

OK, now you are all set to write your code. Good luck! Hint: You can look at a working example of this code in the answerBook directory if you need help.  

## Lesson 3a: DC Motor With speed control
Goal: 
Write a program that spins the shaft of a DC motor.

New things to learn: 
1. Learn how PWM works.

Required items: 
1. The items from lesson 1 and 2 plus
2. An electric motor. In our case we will be using the Meccano ER20 universal motor.
3. A [motor controller board](https://www.amazon.ca/hz/mobile/mission?p=NxaXGg4uaBAdUdbX2Ljs300fa2coZlhjr3dNuuM5PCdiR0lDZ3t90FeAFzGH2JxPPMFTkses0GJLsMWubWuqkzRPjA0FwpmP6GJyK6POBSueaKvad25T82iYaHXfiQs2ZIYcnh%2BDPZ0ayiOWRrkdF0Y%2B8HyVha2edsa9T8qbmhtwv1p3cvp1WUQDjh899QcxUxliRyi1Wh0YaB%2FwqzdyqfkUOaxXdiGQsqUwThcphtrwi9n%2FinmWDyu7B%2FoOPYlplk%2FUEbCZ1ZkkNyUnoBtoXjbzqNfvVVO30XrJhSataTkXqubi5s%2Fn7TVOoL0YXfFyFLCUr%2F4iF0Xyn5z7eSnrV33WE8Hko4bUp%2BruZmBP3fepvi96OW%2F%2FldB00vooYBYWGYMmGxFn5pXBBYFEivd6DYTJrCPppWMvBlcYwShYLsxbWfIEQ5520A%3D%3D&ref_=nb_sb_ss_di_ci_mcx_mi_ci-mcx-ksf-of-nv1_0&crid=35R3PKF89TKK2).
4. A [logic level converter](https://www.amazon.ca/dp/B07LG646VS?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_8).
5. Some [Lever nut wire connectors](https://www.amazon.ca/Compact-Splicing-Connector-Assortment-221-2401/dp/B0BXQRVNHL/ref=sr_1_3_sspa?crid=2HY7JRA2TARDH&dib=eyJ2IjoiMSJ9.wNnWW0kKuQegTHCL7k_22gBOEuUrfk8M4S6myRwcThXojkmWagmGioBwikISHTg1PD_DeDJ5gvk1_nIAYoq4HGiEgzLlXIFk-n2yi8SSceBmHJIBiiTvKc_UhbG2VFx3jcPB3AIHlGtFeUwzxRnkYoq01PlpEBUi2X8VEs9FNgze172hEXBjBijL3H-md2a7dTf4EETwhHwj4psiLmYccZgri9k7sm4xmgGqS721vtIS-xAxWD_UJNhJMsAVkB6AkD6yexDwV9UOwr5OPPvoDX34Xx59MmznXMfxyEJCVgo.SN2RZ4ECV-xk9qOugLByuFbgJpnTTPvHizxpOxxXsVs&dib_tag=se&keywords=wire%2Bconnector&qid=1739630460&sprefix=wire%2Bconnector%2Caps%2C118&sr=8-3-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1).

### Wiring Instructions

Here’s how to wire the Arduino UNO R4 WiFi to the L298N for controlling two DC motors:

Power Connections:
1. Connect the positive terminal of your motor power supply (e.g., 7–12V battery) to the VCC (+12V) terminal on the L298N.
2. Connect the negative terminal of the power supply to the GND terminal on the L298N.
3. Connect a GND pin from the Arduino UNO R4 WiFi to the GND terminal on the L298N to ensure a common ground.

Optional: Powering the Arduino from L298N:
1. Your motor power supply is ≤12V and the 5V jumper on the L298N is in place, meaning that the L298N’s onboard regulator provides 5V at the +5V pin.
2. Note: If VCC > 12V, remove the 5V jumper and do not connect the L298N’s +5V pin to the Arduino. Instead, power the Arduino via USB or its VIN pin (6–24V).
3. We will use USB 5V to poswer the Arduino so DO NOT Connect the +5V pin on the L298N to the 5V pin on the Arduino to power it.

Motor Connections:
1. Connect the two terminals of Motor A to OUT1 and OUT2 on the L298N.
2. Connect the two terminals of Motor B to OUT3 and OUT4 on the L298N.
3. Control Pin Connections:
4. Connect ENA on the L298N to a PWM pin on the Arduino, e.g., pin 9.
5. Connect IN1 to pin 8 and IN2 to pin 7 for Motor A direction control.
6. Connect ENB to another PWM pin, e.g., pin 10.
7. Connect IN3 to pin 6 and IN4 to pin 5 for Motor B direction control.

Jumper Configuration:
1. Your motor power supply is ≤12V so keep the 5V enable jumper on the L298N.
2. If the supply was >12V then we would remove the jumper and provide a separate 5V supply to the L298N’s +5V pin (or power the Arduino separately).

### Finding the best ER20 PWM settings
The code answerbook/Lesson3a-DcMotorWithSpeed/main-testPwmSettings.cpp allows you to try different PWM and voltage settings to maximize the PWM range. Full details about this program and its results after testing can be viewed [here](testEr20PwmSettings.md). 

### Lesson 3a code files in answerBook 
In the answerBook/Lesson3a-DcMotorWithSpeed section you will fina a lot of different code files. This is a quick summry of the files you may find most intersting. 
1. main-optimized.cpp ramps up and down the PWM duty cycle over and over using optimal PWM settings for the ER20 Meccano motor.
2. main-testPwmSettings.cpp is used to cycle through diffferent PWM settings to heklp identify the optiaml settings for the ER20 meccano motor. 

## Lesson 4: Servo Motor Control Arduino UNO
Goal: 
Write a program that controls a servo motor. Try uing the values 10, 90, amd 170 to position the motor. 

New things to learn: 
1. Learn how to wire a servo motor to your development board.
2. Learn what a library is.
3. Learn  to use the **Servo.h** library.
4. Learn what *magic numbers* are and how to avoid them using well named variables.
5. Learn what a function is.
6. Learn what a forward declaration is.
7. Learn how to define a function.
8. Learn how to create a function.
9. Learn how to call a function.
10. Learn how to use the **servo.attach()** command.
11. Learn how to use the **servo.write()** command.
    
Required items: 
1. The items from lesson 1 and 2 plus
2. A [servo motor](https://www.amazon.ca/Miuzei-Geared-Helicopter-Arduino-Project/dp/B0BWJ4RKGV/ref=sr_1_3_sspa?crid=2UIMV3196NQB5&dib=eyJ2IjoiMSJ9.JbnywnHviXX_tZOO55IEriZcGtSkhHlYcL1RRF3qYN7PWeU7TgaaRFjFKCLcz_jpo3Vt5vJpChc9pLv7VlzMIDmTOAbLINqShuC2NnRKd92BcQZfdAMlf5jAI7ktFT7oXQp0xo3TD2JQbe5s_HXxLbmiLI_S8XWkHUgLjHW-AOvBLoXmaYXNSFk1SP8ZuUYVhxebiDO0hrSspYVqSBnNS6Eu5I-qi5usAVOrRnJeHIMgb-DJb-OhQW7NRJXolJ-L4jqQrTHephzo-5MPH0us-cXpoNWMBHIA92Ly4a9ab2s.VsiPqcu3ZMRkXlkHeRyx7WXuOMa7uB5-KkTbYGY3bjQ&dib_tag=se&keywords=servo+motor&qid=1739423741&sprefix=servo+motor%2Caps%2C132&sr=8-3-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1)

Wiring required:
For this lesson you must connect a hobby servo motor to the Arduino board. Here are the connections to make:

1. Connect the red wire from the servo motor to the 5V rail on your bread board.
2. Connect the brown wire from the servo motor to the GND rail next to the 5V rail on your bread board.
3. Connect the orange wire from the servo motor to pin ~11 on the Arduino board.  

## Lesson 4a: Direct Servo Motor Control Using the ESP32 

Goal: 
Write a program that controls a servo motor over an I2C bus. 

Wiring required:
For this lesson you must connect a hobby servo motor to the ESP32. Here are the connections to make:

1. Connect the red wire from the servo motor to the 5V rail on your bread board.
2. Connect the brown wire from the servo motor to the GND rail next to the 5V rail on your bread board.
3. Connect the orange wire from the servo motor to physical pin 5, aka GPIO26, aka A0 on the Arduino board.  

IN your Arduino IDE
1. Load the code located in the AnswerBook/Lesson4a-ServoMotorControl/mainArduinoIDEServoDirect/mainArduinoIDEServoDirect.ino directory. 
2. Select the board Adafriot ESP32 feather
3. Select the correct serial (COM) port
4. Save and upload the code to the ESP32

At this point the servo should be rotasting back and forward a small amount. 

## Lesson 4b: Servo Motor Control using the ESP32 and the PCA9685 I23C motoro controller

Goal: Write a program that controls a servo motor over an I2C bus. 

On the Adafruit HUZZAH32 ESP32 Feather:
- SDA (data): GPIO23 (physical pin 17)
- SCL (clock): GPIO22 (physical pin 18)

For wiring see: [here](https://dronebotworkshop.com/esp32-servo/)

Load the code located in the file Lesson4b/i2cMotorControl/i2cServoPca9685/i2cServoPca9685.ino

## Lesson 5: Putting it all together
This will be your chance to take what you have learned and see if you can make a program that spins a motor forward and backward based on input from a Joystick.

## Lesson 6: Bluetooth
This lesson contains 2 projects. One project is for a BlueTooth [Server](answerBook/Lesson6-Bluetooth/uno-r4-bt-server/README.md), and one project is for a BlueTooth [client](answerBook/Lesson6-Bluetooth/esp32-bt-client/README.md). 

## Lesson 7: Using GitHub
While not strictly neccessary, learning to use source control tools allows you to save your code to as cloud based code repository. This is desireable both as an offsite backup for your code as well as making it very easy to share your projets with others. There are two source code anagemetn tools that we will be using. One is called GIT and it runs on your local computer. The other is called GITHUB and it runs on a cloud based server on the internet.

### Some basics
Lets get you started by taking on three basic challenges.

1. Make yourself a [Github account](https://github.com).  
2. Follow Doug Elliott’s Github account.
3. Follow theAging Apprentice’s Github account.

### Copy code from one GITHUB repository to another
We will now copy the "Doug Lesson Plan" repository from theAgingAprentice account to a repository under your GITHUB account. Here are the step to follow:
1. In your web brower go the the "Doug Lesson Plan" repository loated under theAgingAprentice GITHUB account [HERE](https://github.com/theAgingApprentice/DougLessonPlan). 
2. Look for the green button that says "<> Code".
3. Click that button to view a drop down menu. 
4. Copy the HTTPS URL to the clipboard.
5. Now log into your own GITHUB account.
6. Navigatye to the Repositories screen.
7. Click the green NEW button.
8. Click the "Import a repository" link at the top of the page.
9. Paste the URL you copiedin step 4 into the field labelled "The URL for your source repository".
10. Skip a few fields enter a name like "Doug's Arduino Lesson Plan" in the field labelled "Repository name".
11. Click the green button labelled "Begin Import"
12. Close the window saying that you will be emailed when the rewponsitory is cloned.

Eventually you will recieve an email telling you that your new repository is ready.  

### Installing Git on your computer
To do this please follow [these instructions](https://github.com/git-guides/install-git). We will refer to the directory where you cloned the 
Github repository your "cloned directory" in the next steps of this tutorial. 

### Clone a Github repository to your local machine
To do this please follow [these instructions](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository).

### Push your change to your GITHUB respository
Once you have saved new files to your local Git directory you can push your chnages up to the GITHUB respository.  

1. In a terminal window navigate to the directory on your harddrive where your cloned directory is.
2. See if there are chnages to push by tying the command "git status".
3. You *may* need to issue the command "git commit -m "put a summary of your changes here". 
3. To push the changes to your GITHUB repository type "git push origin main". 


# Remote Control
These lessons focus on using an ESP32 to build an Arduino BLE remote control.

## Lesson 8: LCD display

Goal: Write messages to an a 16x2 LCD display via an I2C bus.
See [Radom Nerd tutorial](https://randomnerdtutorials.com/esp32-esp8266-i2c-lcd-arduino-ide/)

Things to learn:
1. I2C bus communication
2. LCD library

Required items:
1. [LCD display](https://www.amazon.ca/Freenove-Display-Compatible-Arduino-Raspberry/dp/B0B76Z83Y4/ref=sr_1_5?crid=SEVKROB1CE7G&dib=eyJ2IjoiMSJ9.G7JwUfzZeH6_nqQz2TNm1-8-1qU_7NU4Xp028WmcjfR-KnHWQscUC2wFE1KfRR3DiL4YjO62ow-WiSc01gSsTuI3aZ_kUJFHC98WB8F_IyP5FY0meQJRHFanZSWMNs_zjr1eJ0qYj7sjrf-ftlEF9LxH24eBGGoOBzW4i7Omlv7FMxr_jCldQVjX42C72i0CAwLMumTQ8467vXt5OwudyA0skt-LMFrqzpVF4i3P4Y9mhXu7cokNpc7I9y1CCvZ0k7mtst7-7Lzt7wDxUQfUdFEl8RvKnpD1R7cpcum5pYk.pelyFjrrtWMLo69oXQq8-KtWBPj9igVv64VMKvHXoHw&dib_tag=se&keywords=lcd%2Bdisplay&qid=1748662669&sprefix=lcd%2Bdisplay%2Caps%2C103&sr=8-5&th=1)

Wiring required:
1. aa
2. bb

## Lesson 9: Rotary encoder
Goal: Get input from a rotary encoder.
See [This tutorial](https://esp32io.com/tutorials/esp32-rotary-encoder)

Things to learn:
1. aaa
2. bbb

Required items:

1. [Rotary encoder](https://www.amazon.ca/dp/B07DFFSZ73?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_1)


## Lesson 10: Joystick revisited

Goal: Read input from 2 joysticks.

See [This tutorial](https://esp32io.com/tutorials/esp32-joystick)

Required items:
1. A little [PS2 joystick](https://www.amazon.ca/dp/B089VXPHDH?ref=ppx_yo2ov_dt_b_fed_asin_title).

Wiring required:
For this lesson you must connect the joystick to the Arduino board. Here are the connections to make:

1. Connect GND pin on the joystick to a GND pin on the Arduino board.
2. Connect +5V pin on the joystick to the 5V pin on the Ardino board.
3. Connect the VRX pin on the joystick to the A0 pin on the Arduino board.
4. Connect the VRY pin on the joystick to the A1 pin on the Arduino board. 
5. Connect the SW pin on the joystick to the A2 pin on the Arduino board. 

OK, now you are all set to write your code. Good luck! Hint: You can look at alesson 2 to remember how this is done. Akso, there is a working example of this code in the answerBook directory if you need help. 

## Lesson 11: RGB LED

Goal: Control the colour of the LED ring on an on/off power switch.

See [This tutorial](https://esp32io.com/tutorials/esp32-rgb-led)

Required items:
1. Closest items I can find: [16mm RBG switch](https://www.amazon.ca/dp/B08TM4V9P6?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_2)

Wiring required:
1. 
2. 
3. 

## Lesson 12: I2C bus

Goal: Detect a device connected to the I2C bus.

### What is I2C?
I2C (Inter-Integrated Circuit) is a communication protocol that allows multiple devices (sensors, displays, etc.) to communicate with a microcontroller using just two wires: SDA (data) and SCL (clock). Each device on the bus has a unique address, and the microcontroller can communicate with each device individually by addressing it.

On the Adafruit HUZZAH32 ESP32 Feather:
- SDA (data): GPIO23 (physical pin 17)
- SCL (clock): GPIO22 (physical pin 18)

Make sure your I2C device's SDA and SCL lines are connected to these pins, and that the device is properly powered.

### I2C Scanner Program
To help you find the address of any I2C device connected to your board, you can use the `i2c_scanner.cpp` program in the `src/` directory. This program scans all possible I2C addresses and prints out any devices it finds to the Serial Monitor. This is useful for troubleshooting wiring and confirming your device is detected by the ESP32.

**How to use:**
1. Connect your I2C device to SDA (GPIO23) and SCL (GPIO22), and power it appropriately.
2. In the Arduino IDE, upload the `i2c_scanner.cpp` program in the Lesson12-I2C folder to your ESP32.
3. Open the Serial Monitor at 115200 baud.
4. The program will print out the addresses of any I2C devices it finds every 5 seconds to the serial output terminal.

Extra credit: Try addign more evices to the I2C bus and see them appear in the output!

**Sample output:**
```
I2C Scanner ready
Scanning I2C bus...
I2C device found at address 0x27 !
done
```
If no devices are found, check your wiring and power connections.

Required items:
1. I2C capable device that you wish to attach

Wiring required:
1. Physical Pin 17 (I2C SDA) is GPIO23
2. Physical Pin 18 (I2C SCL) is GPIO22
3. Make sure device is properly powered

