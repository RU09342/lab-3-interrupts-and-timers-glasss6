#include <msp430.h>

/**
 * blink.c
 Blink onboard LEDs with different speed controlled by pressing a button
 MSP430F5529
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

    P1DIR |= (BIT0);                // configure P1.0 as output
    P4DIR |= (BIT7);                // configure P4.7 as output
    P1OUT &= ~(BIT0);               // reset the LEDs
    P4OUT &= ~(BIT7);               // reset the LEDs

    P1REN |= BIT1;                  // puller-resistor on the button pin P1.1
    P1OUT |= BIT1;                  // writes "1" to portpin, telling the resistor to pullup
    P1IES |= BIT1;                  // triggers when you press the button, "~BIT1" for when release
    P1IE |= BIT1;                   // enables selector-mask for generating interrupts on the pin

    P2REN |= BIT1;                  // puller-resistor on the button pin P2.1
    P2OUT |= BIT1;                  // writes "1" to portpin, telling the resistor to pullup
    P2IES |= BIT1;                  // triggers when you press the button, "~BIT1" for when release
    P2IE |= BIT1;                   // enables selector-mask for generating interrupts on the pin

    __enable_interrupt();           // enable interrupts


    /*while(1)
    {
        if(enabled > 0) // if the button was pressed and enable was set
        {
            P1OUT ^= (BIT0);            // toggle P1.0
        }
        else
        {
            P4OUT ^= (BIT7);            // toggle P4.7
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
    }*/
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) // function called when the port is interrupted (button pressed)
{
    if(P1IFG & BIT1)
    {
        P1OUT ^= (BIT0);            // toggle P1.0
        P4OUT ^= (BIT7);            // toggle P4.7
        P1IFG &= ~BIT1; // P1.1 (button) IFG cleared
    }
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) // function called when the port is interrupted (button pressed)
{
    if(P2IFG & BIT1)
    {
        enabled ^= 0x01;  // toggle the enabled int on/off (this determines which LED is blinking)
        P2IFG &= ~BIT1;   // P1.2 (button) IFG cleared
        P1OUT &= ~(BIT0); // Clear the LEDs so they start in OFF state
        P4OUT &= ~(BIT7); // Clear the LEDs so they start in OFF state
    }
}
