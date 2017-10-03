#include <msp430.h>


/**
 * blink.c
 Blink onboard LEDs with different speed controlled by pressing a button
 MSP430G2553
 Stephen Glass
 */

/* Speed constants */
#define SPEED_1 25000
#define SPEED_2 50000
#define SPEED_3 75000
#define SPEED_4 100000
#define SPEED_5 125000
#define SPEED_6 150000
#define SPEED_7 175000
#define SPEED_8 200000
#define SPEED_9 250000
#define SPEED_10 300000

unsigned int speed = 1;				// declare int to keep track of the speed

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT6);			// configure P1.0 and P1.6 as output
	P1OUT &= ~(BIT0 + BIT6);		// reset the LEDs (both start off)

	P1REN |= BIT3;					// puller-resistor on the button pin P1.3
	P1OUT |= BIT3;					// writes "1" to P1.3, telling the resistor to pullup
	P1IES |= BIT3;					// telling it to trigger when you press the button P1.3, "~BIT3" for when release
	P1IE |= BIT3;					// enables selector-mask on P1.3 for generating interrupts on the pin

	__enable_interrupt(); 			// enable interrupts

	while(1)
	{
		P1OUT ^= (BIT0 + BIT6);			 // toggle P1.0 and P1.6 LEDs

		if(speed == 1) __delay_cycles(SPEED_1);
        else if(speed == 2) __delay_cycles(SPEED_2);
        else if(speed == 3) __delay_cycles(SPEED_3);
        else if(speed == 4) __delay_cycles(SPEED_4);
        else if(speed == 5) __delay_cycles(SPEED_5);
        else if(speed == 6) __delay_cycles(SPEED_6);
        else if(speed == 7) __delay_cycles(SPEED_7);
        else if(speed == 8) __delay_cycles(SPEED_8);
        else if(speed == 9) __delay_cycles(SPEED_9);
        else if(speed == 10) __delay_cycles(SPEED_10);
	}
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) // function called when the port is interrupted (button pressed)
{
	if(speed >= 10) speed = 1; // If speed setting is at its maximum, reset it
	else speed = speed + 1; // Increment the speed setting each time the button is pressed

	P1IFG &= ~BIT3; // P1.3 (button) IFG cleared
}
