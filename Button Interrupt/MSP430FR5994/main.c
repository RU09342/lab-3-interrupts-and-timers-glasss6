#include <msp430.h>

/**
 * blink.c
 Blink onboard LEDs with different speed controlled by pressing a button
 MSP430FR5994
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

unsigned int speed = 1;             // declare int to keep track of the speed
unsigned int enabled = 0;           // declare int to keep track of when the button was pressed

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode (needed for FR5994)

    P1DIR |= (BIT0 + BIT1);         // configure P1.0 and P1.1 as output
    P1OUT &= ~(BIT0 + BIT1);        // reset the LEDs

    P5REN |= (BIT5 + BIT6);         // puller-resistor on the button pin P5.5/5.6
    P5OUT |= (BIT5 + BIT6);         // writes "1" to portpin, telling the resistor to pullup
    P5IES |= (BIT5 + BIT6);         // triggers when you press the button, "~BIT3" for when release
    P5IE |= (BIT5 + BIT6);          // enables selector-mask for generating interrupts on the pin

    __enable_interrupt();           // enable interrupts

    while(1)
    {
        if(enabled > 0) // if the button was pressed and enable was set
        {
            P1OUT ^= (BIT0);            // toggle P1.0 
        }
        else
        {
            P1OUT ^= (BIT1);            // toggle P1.1
        }

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
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void) // function called when the port is interrupted (button pressed)
{
    if(P5IFG & BIT5)
    {
       	if(speed >= 10) speed = 1; // If speed setting is at its maximum, reset it
        else speed++; // Increment the speed setting each time the button is pressed
        P5IFG &= ~BIT5; // P1.1 (button) IFG cleared
    }
    else if(P5IFG & BIT6)
    {
        enabled ^= 0x01;  // toggle the enabled int on/off (this determines which LED is blinking)
        P5IFG &= ~BIT6;   // P1.2 (button) IFG cleared
        P1OUT &= ~(BIT0 + BIT1); // Clear the LEDs so they start in OFF state
    }
}
