# Button Based Delay
## Stephen Glass

## main.c
### Compatibility
* MSP430G2553
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430FR5529

### Description
main.c sets up the microcontroller to initially blink and LED at a rate of 10Hz upon restarting or powering up. Then utilizing one of the buttons on board, a user can set the delay or blinking rate of the LED by holding down a button. The duration in which the button is depressed should then become the new rate at which the LED blinks.

## Functions
### initializeTimer(int capture)
This function will initialize the TimerA/B module with the timing of your choosing.
* int capture = time in hertz to cycle

Example:
initializeTimer(20); // Initialize a timer for 20Hz

### Extra Work
## Reset Button
Press Button 2 to reset the timer to the initial 10Hz.