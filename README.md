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
   
## Lesson 3: DC Motor Control
Goal: 
Write a program that spins the shaft if an electric motor.

New things to learn: 
1. Learn how to wire up a motor to your develpoment board using a motor controller.
2. Learn to use the **#define** precompiler macro.
3. Learn to use the **digitalWrite()** command.
4. Learn about the different pins that are available to you. 

Required items: 
1. The items from lesson 1 and 2 plus
2. An electric motor. In our case we will be using the Meccano ER20 universal motor.
3. A [motor controller board](https://www.amazon.ca/hz/mobile/mission?p=NxaXGg4uaBAdUdbX2Ljs300fa2coZlhjr3dNuuM5PCdiR0lDZ3t90FeAFzGH2JxPPMFTkses0GJLsMWubWuqkzRPjA0FwpmP6GJyK6POBSueaKvad25T82iYaHXfiQs2ZIYcnh%2BDPZ0ayiOWRrkdF0Y%2B8HyVha2edsa9T8qbmhtwv1p3cvp1WUQDjh899QcxUxliRyi1Wh0YaB%2FwqzdyqfkUOaxXdiGQsqUwThcphtrwi9n%2FinmWDyu7B%2FoOPYlplk%2FUEbCZ1ZkkNyUnoBtoXjbzqNfvVVO30XrJhSataTkXqubi5s%2Fn7TVOoL0YXfFyFLCUr%2F4iF0Xyn5z7eSnrV33WE8Hko4bUp%2BruZmBP3fepvi96OW%2F%2FldB00vooYBYWGYMmGxFn5pXBBYFEivd6DYTJrCPppWMvBlcYwShYLsxbWfIEQ5520A%3D%3D&ref_=nb_sb_ss_di_ci_mcx_mi_ci-mcx-ksf-of-nv1_0&crid=35R3PKF89TKK2).

## Lesson 4: Servo Motor Control
Goal: 
Write a program that controls a servo motor.

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

## Lesson 5: Putting it all together
This will be your chance to take what you have learned and see if you can make a program that spins a motor forward and backward based on input from a Joystick.

## Lesson 6: Bluetooth
Teacher has to get this figured out first!

## Lesson 7: Using Gitlab
Make yourself a [Github account](https://github.com) so that you can save your code to this cloud based code repository. We'll discuss this in person.   

## Time to build a project
Let's build a [Meccano Crane](https://github.com/theAgingApprentice/MeccanoCrane). Once yu have a Gitlab accoutn and get some orientaiotn we will use this site to save and share files etc. 

