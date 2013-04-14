/**Description: Robotics Winter 2013 Team 11
 *
 *@file:   main.c
 *@author: Joshua David Alfaro
 *
 *@date March 4, 2013, 6:27 PM
 */
/*Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "usart.h"

//Config Bits:
// Data Code Protection bit: Data memory code protection is disabled
// Brown Out Reset Selection bits: BOR disabled
// Internal External Switchover bit: Internal/External Switchover mode is disabled
// In-Circuit Debugger Mode bit: In-Circuit Debugger disabled, RB6/ICSPCLK and RB7/ICSPDAT are general purpose I/O pins
// Oscillator Selection bits: INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN
// Fail-Safe Clock Monitor Enabled bit: Fail-Safe Clock Monitor is disabled
// RE3/MCLR pin function select bit: RE3/MCLR pin function is digital input, MCLR internally tied to VDD
// Watchdog Timer Enable bit: WDT disabled and can be enabled by SWDTEN bit of the WDTCON register
// Code Protection bit: Program memory code protection is disabled
// Low Voltage Programming Enable bit: RB3 pin has digital I/O, HV on MCLR must be used for programming
// Power-up Timer Enable bit: PWRT disabled
#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB0, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF, IESO = OFF, FCMEN = OFF

/*Defines*/
#define _XTAL_FREQ 4000000 //Set the speed of the oscillator

// Define motor control buttons
#define FORWARD_LEFT_BUTTON RA2
#define FORWARD_RIGHT_BUTTON RA1
#define BACKWARD_LEFT_BUTTON RA3
#define BACKWARD_RIGHT_BUTTON RA0
#define TOGGLE_TEAM RB0

// Define constants
#define TRUE 1
#define FALSE 0
#define LOW 0
#define HIGH 1

void init(void) {
    OSCCON = 0b01100000;    //set frequency to 4MHz
    TRISA = 0b11111111;           // set all pins in PORTA as inputs
    TRISB = 0b000000001;    // set RB0 as input
    ANSEL = 0x00;           // ignore this

    init_comms(); //Prepare the usart
}

int main(void) {
    init(); // call the function above
    char motorLeft;
    char motorRight;
    char teamLED;
    char command;

    int team = 0;
    int teamButton = FALSE;

    int leftForward = FALSE;
    int rightForward = FALSE;
    int leftBackward = FALSE;
    int rightBackward = FALSE;

    while (TRUE) {
        // TOGGLE_TEAM Button (ACTIVE LOW)
        if (TOGGLE_TEAM == LOW && teamButton == FALSE) {
            teamButton = TRUE;
            if (team == 0) {
                team == 1;
            } else {
                team == 0;
            }
            __delay_ms(100);
        } else if (TOGGLE_TEAM == HIGH && teamButton == TRUE) {
            teamButton = FALSE;
            __delay_ms(100);
        }

        // FORWARD_LEFT Button (ACTIVE_LOW)
        if (FORWARD_LEFT_BUTTON == LOW && leftBackward == FALSE) {
            leftForward = TRUE;
            __delay_ms(100);
        } else if (FORWARD_LEFT_BUTTON == HIGH && leftForward == TRUE) {
            leftForward = FALSE;
            __delay_ms(100);
        }

        // FORWARD_RIGHT Button (ACTIVE_LOW)
        if (FORWARD_RIGHT_BUTTON == LOW && rightBackward == FALSE) {
            rightForward = TRUE;
            __delay_ms(100);
        } else if (FORWARD_RIGHT_BUTTON == HIGH && rightForward == TRUE) {
            rightForward = FALSE;
            __delay_ms(100);
        }

        // Pressing BACKWARD_LEFT (ACTIVE_LOW)
        if (BACKWARD_LEFT_BUTTON == LOW && leftForward == FALSE) {
            leftBackward = TRUE;
            __delay_ms(100);
        } else if (BACKWARD_LEFT_BUTTON == HIGH && leftBackward == TRUE) {
            leftBackward = FALSE;
            __delay_ms(100);
        }

        // Pressing BACKWARD_RIGHT (ACTIVE_LOW)
        if (BACKWARD_RIGHT_BUTTON == LOW && rightForward == FALSE) {
            rightBackward = TRUE;
            __delay_ms(100);
        }
        if (BACKWARD_RIGHT_BUTTON == HIGH && rightBackward == TRUE) {
            rightBackward = FALSE;
            __delay_ms(100);
        }

        // Outputs
        if(team) {
            teamLED = 0b00010000;
            RB1 = HIGH;         // for testing
        }
        else {
            teamLED = 0b00000000;
        }

        if(rightForward) {
            motorRight = 0b00000001;
            RB4 = HIGH;         //for testing
        } else if (rightBackward) {
            motorRight = 0b00000010;
        } else {
            motorRight = 0b00000000;
        }

        if(leftForward) {
            motorLeft = 0b00000100;
            RB3 = HIGH;         // for testing;
        } else if (leftBackward) {
            motorLeft = 0b00001000;
        } else {
            motorLeft = 0b00000000;
        }

        // Transmitter
        putch(0b01011011);
        command = ((0b01100000 | teamLED) | motorLeft) | motorRight;
        putch(command);
        putch(command);
    }
}

