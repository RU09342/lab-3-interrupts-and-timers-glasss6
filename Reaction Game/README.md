# Reaction Game
## Stephen Glass

## main.c
### Compatibility
* MSP4306989

### Description
The reaction game is designed for the MSP430FR6989 and utilizes the LCD display. The goal of the 2-player game is to be the first player to press your buttom 10 times. The first player to press the button 10 times wins. Each time you press the button it updates your score on the LCD display and blinks an LED to indicate that you successfully pushed the button. When you win, it will display it on the screen! After winning, the game will automatically reset after a few seconds and you can start another round with your friend!

This code utilizes the driverlib LCD display library. The code has software debouncing for the buttons to make sure that each button press is fair and accurate.

## YouTube Video Demonstration
![YouTube Video](https://img.youtube.com/vi/Fg25mOs-a4c/0.jpg)](https://www.youtube.com/watch?v=Fg25mOs-a4c)


## hal_LCD.c
This is part of the driverlib library by Texas Instruments. This file creates some basic functions for displaying characters on the LCD screen. This code is used to show the score on the LCD display and showing the winner of the LCD.