/**
 * main.c
 Blink onboard LEDs using the TimerB module
 MSP430FR2311
 Stephen Glass
 */

#include <msp430.h>

#define LED_0 BIT0
#define LED_1 BIT0
#define LED0_OUT P1OUT
#define LED0_DIR P1DIR
#define LED1_OUT P2OUT
#define LED1_DIR P2DIR

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

    initializeTimer(10); // Initialize timer at 10Hz or 0.1s

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled
}

void initializeTimer(int hertz) // Seconds = 1/Hertz, 10Hz = 0.1s
{
    TB0CCTL0 = CCIE;
    TB0CTL = TBSSEL_2 + MC_1 + ID_3; // SMCLK/8, UPMODE
    // CLK/HERTZ = CAPTURE
    // CLK = 1MHZ/8 = 125kHz
    int capture = (125000)/hertz;
    TB0CCR0 = capture; // (1000000/8)/(12500) = 10 Hz = 0.1 seconds
}

// Timer B0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer0_B0 (void)
{
    if(timerCount >= 100) // 0.1 seconds 100 times, called every 10s
    {
        LED0_OUT ^= (LED_0); // Switch on the LEDs
        LED1_OUT ^= (LED_1);
        timerCount = 0; // Reset the counter variable
    }
    else timerCount++; // Increment the counter variable until 10s
}
