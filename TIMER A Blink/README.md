# TIMER A BLINK
## Stephen Glass

## main.c
### Compatibility
* MSP430G2553
* MSP430FR2311 (TIMER B)
* MSP430FR5994
* MSP430FR6989
* MSP430FR5529

### Description
main.c will program the Timer A module (Timer B for MSP430FR2311) to interrupt at a specified interval. The code will automatically configure the timer registers (Capture control, clock speed, etc.) to interrupt at the correct times. When the timer is interrupted, it will flash an onboard LED.

## Functions
### initializeTimer(int capture)
This function will initialize the TimerA/B module with the timing of your choosing. This is done by using the SMCLK and using any clock dividers neccessary to achieve correct timing. We set the capture compare registers to compare to certain calculated integer to get the correct timing.
* int capture = time in hertz to cycle

Example:
initializeTimer(20); // Initialize a timer for 20Hz