/**
 * main.c
 Blink onboard LEDs using the TimerA module
 MSP430FR6989
 Stephen Glass
 */

#include <msp430.h>

#define LED_0 BIT0
#define LED_1 BIT7
#define LED0_OUT P1OUT
#define LED0_DIR P1DIR
#define LED1_OUT P9OUT
#define LED1_DIR P9DIR

void initializeTimer(int capture);

unsigned int timerCount = 0;
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // needed for FR series

    LED0_DIR |= (LED_0); // Set P1.0 and P1.6 to output direction
    LED1_DIR |= (LED_1);
    LED0_OUT &= ~(LED_0); // Set the LEDs off
    LED1_OUT &= ~(LED_1);

    __enable_interrupt();
    _no_operation();


    // Startup clock system with max DCO setting ~8MHz
    CSCTL0_H = CSKEY >> 8;                    // Unlock clock registers
    CSCTL1 = DCOFSEL_3 | DCORSEL;
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
    CSCTL0_H = 0;                         // Lock CS registers

    initializeTimer(500); // Initialize timer at 500Hz or 0.002s

    //__bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

void initializeTimer(int hertz) // Seconds = 1/Hz
{
    TA1CCTL0 = CCIE + CAP;
    int capture = (8000000)/hertz; // Count to this. SMCLK = 8Mhz
    TA1CCR0 = capture;
    TA1CTL = TASSEL_2 + MC_1 + TAIE; // SMCLK, UP-MODE, TAIE = 1
}

// Timer A0 interrupt service routine
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1_A1 (void)
{
    if(timerCount >= 5000) // 0.002s called 5000 times, 10s total
    {
        LED0_OUT ^= (LED_0); // Switch on the LEDs
        LED1_OUT ^= (LED_1);
        timerCount = 0; // Reset the counter variable
    }
    else timerCount++; // Increment the counter variable until 10s
    switch(TA1IV); // Read and clear interrupt flag
}
