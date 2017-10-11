# Button Interrupt
## Stephen Glass

## main.c
### Compatibility
* MSP430G2553
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430FR5529

NOTE: Boards with more than one button include additional functionality! (E.g: FR5994, FR6989, FR5529)

### Description
main.c will blink an LED of your choosing at different speeds! Pressing button 1 will allow you to choose whether you want LED 1 or LED 2 to blink. Pressing button 2 will cycle through the speeds at which the LED will blink. Pressing button 2 will cycle through the following blink speeds:
* SPEED_1 25000uS
* SPEED_2 50000uS
* SPEED_3 75000uS
* SPEED_4 100000uS
* SPEED_5 125000uS
* SPEED_6 150000uS
* SPEED_7 175000uS
* SPEED_8 200000uS
* SPEED_9 250000uS
* SPEED_10 300000uS
The speed will reset after pressing button 2 more than the highest cycle amount.

This code uses button interupts to function. When a button on the board is pressed, it will toggle and interrupt function and perform actions to make the LEDs flash at the different cycles.

## Extra Work
Pressing 1 button will alternate which LED is blinking. Pressing button 2 will cycle through the speeds at which it will blink.