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

### setSpeed(int speed)
This function will set the speed of the blinking LED. Parameters are an intger 1-10.
* int speed = integer for speed to set corresponding to SPEED_X define

Example:
setSpeed(5); // Sets the blinking LED speed to SPEED_5

### Extra Work
## Reset Button
Press Button 2 to reset the timer to the initial 10Hz.