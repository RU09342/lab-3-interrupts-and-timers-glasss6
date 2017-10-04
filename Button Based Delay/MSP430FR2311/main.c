#include <msp430.h>

/**
 * main.c
 Blink onboard LED with adjustable frequency using interrupts and TimerA module. 
 Hold down BTN0 to change frequency dependent on time button held down.
 MSP430FR2311
 Stephen Glass
 */

/* Speed constants */
// Timer is called every 0.1s. Speed = Time Desired/0.1
#define SPEED_1 1       // 0.1 seconds
#define SPEED_2 5       // 0.5 second
#define SPEED_3 10
#define SPEED_4 20
#define SPEED_5 40
#define SPEED_6 60
#define SPEED_7 80
#define SPEED_8 100
#define SPEED_9 120
#define SPEED_10 150

#define LED0    BIT0
#define LED1    BIT0

#define BTN0    BIT1

#define LED0DIR	P1DIR
#define LED1DIR	P2DIR

#define LED0OUT	P1OUT
#define LED1OUT	P2OUT

#define BTN0REN	P1REN
#define BTN0OUT	P1OUT
#define BTN0IES	P1IES
#define BTN0IE  P1IE
#define BTN0IFG	P1IFG

unsigned int timerCount = 1;        // Counter to check button to change speed
unsigned int ledCount = 1;          // Counter to check to blink LED
unsigned int ledSpeed = 1;          // declare int to keep track of the speed
unsigned int enabled = 0;           // declare int to keep track of when the button was pressed
unsigned int hzSpeed = SPEED_1;

void initializeTimer(int capture);
void setSpeed(int speed);

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;         // stop watchdog timer
    M5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode

    LED0DIR |= (LED0);                // configure P1.0 as output
    LED1DIR |= (LED1);                // configure P4.7 as output
    LED0OUT &= ~(LED0);               // reset the LEDs
    LED1OUT &= ~(LED1);               // reset the LEDs

    BTN0REN |= BTN0;                  // puller-resistor on the button pin P1.1
    BTN0OUT |= BTN0;                  // writes "1" to portpin, telling the resistor to pullup
    BTN0IES |= BTN0;                  // triggers when you press the button, "~BIT1" for when release
    BTN0IE |= BTN0;                   // enables selector-mask for generating interrupts on the pin
    BTN0IFG &= BTN0;

    initializeTimer(10); 			  // Initialize timer for 10Hz

    __enable_interrupt();             // enable interrupts

    __bis_SR_register(LPM0 + GIE);    // LPM0 with interrupts enabled
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

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) // function called when the port is interrupted (button pressed)
{
    // Button to change the speed of the blinking LED
    enabled ^= 0x01; // Toggle enable for checking to change blink frequency
    BTN0IFG &= ~BTN0; // Reset the interupt flag
    BTN0IES ^= BTN0; // This will trigger the edge so when it is released it will toggle the enable again
}

// Timer B0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer0_B0 (void)
{
    // Timer portion to increase the speed
    if(timerCount >= 10) // 0.1 seconds 10 times, called every 1s
    {
        LED1OUT &= ~(LED1); // Turn off LED used to show speed changing
        if(enabled > 0)
        {
            if(ledSpeed >= 10) ledSpeed = 1; // If speed setting is at its maximum, reset it
            else ledSpeed++; // Increment the speed setting each time the button is pressed
            LED1OUT |= (LED1); // Show LED to indicate speed has changed
            setSpeed(ledSpeed);
        }
        timerCount = 1; // Reset the counter variable
    }
    else timerCount++; // Increment the counter variable until 10s

    if(ledCount >= hzSpeed)
    {
        LED0OUT ^= (LED0); // Toggle LED to blink
        ledCount = 1; // Reset the counter
    }
    else ledCount++; // Increment the counter until it reaches threshold
}

void setSpeed(int speed) // Sets the hzSpeed to match constant definitions
{
    if(speed == 1) hzSpeed = SPEED_1;
    else if(speed == 2) hzSpeed = SPEED_2;
    else if(speed == 3) hzSpeed = SPEED_3;
    else if(speed == 4) hzSpeed = SPEED_4;
    else if(speed == 5) hzSpeed = SPEED_5;
    else if(speed == 6) hzSpeed = SPEED_6;
    else if(speed == 7) hzSpeed = SPEED_7;
    else if(speed == 8) hzSpeed = SPEED_8;
    else if(speed == 9) hzSpeed = SPEED_9;
    else if(speed == 10) hzSpeed = SPEED_10;
    else hzSpeed = SPEED_1;
}
