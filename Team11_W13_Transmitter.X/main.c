/**
 *@file:   main.c
 *@author: Michael
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
#define ON 1 //Define on State for LEDS
#define OFF 0 //Define off state for LEDS

// Define motor control buttons
#define FORWARD_LEFT_BUTTON RA0
#define FORWARD_RIGHT_BUTTON RA1
#define BACKWARD_LEFT_BUTTON RA2
#define BACKWARD_RIGHT_BUTTON RA3

#define FORWARD_LEFT RB0
#define FORWARD_RIGHT RB1
#define BACKWARD_LEFT RB2
#define BACKWARD_RIGHT RB3


// Define constants
#define TRUE 1
#define FALSE 0

#define LOW 0
#define HIGH 1

void init(void){

    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins in PORTA as outputs
    TRISB = 0b000000100;         // set RB2 as input
    ANSEL = 0x00;               // ignore this

    init_comms(); //Prepare the usart
}

int main(void) {
   init(); // call the function above
   char motorLeft;
   char motorRight;
   char teamLED;
   char command;

   int leftForward = FALSE;
   int rightForward = FALSE;
   int leftBackward = FALSE;
   int rightBackward = FALSE;

   while(TRUE){
        if (RA6 == 1) {
            teamLED = 0b00010000;
        }
        else {
            teamLED = 0b00000000;
        }

         // Pressing FORWARD_LEFT (ACTIVE_LOW)
        if(FORWARD_LEFT_BUTTON == LOW && leftBackward == FALSE) {
            leftForward = TRUE;
            motorLeft = 0b00000100;
            __delay_ms(100);
        }
        else if (FORWARD_LEFT_BUTTON == HIGH && leftForward == TRUE) {
            leftForward = FALSE;
            motorLeft = 0b00000000;
            __delay_ms(100);
        }

        // Pressing FORWARD_RIGHT (ACTIVE_LOW)
        if(FORWARD_RIGHT_BUTTON == LOW && rightBackward == FALSE) {
            rightForward = TRUE;
            motorRight = 0b00000001;
            __delay_ms(100);
        }
        else if(FORWARD_RIGHT_BUTTON == HIGH && rightForward == TRUE) {
            rightForward = FALSE;
            motorRight = 0b00000000;
            __delay_ms(100);
        }

        // Pressing BACKWARD_LEFT (ACTIVE_LOW)
        if(BACKWARD_LEFT_BUTTON == LOW && leftForward == FALSE) {
            leftBackward = TRUE;
            motorLeft = 0b00001000;
            __delay_ms(100);
        }
        else if(BACKWARD_LEFT_BUTTON == HIGH && leftBackward == TRUE) {
            leftBackward = FALSE;
            motorLeft = 0b00000000;
            __delay_ms(100);
        }

        // Pressing BACKWARD_RIGHT (ACTIVE_LOW)
        if(BACKWARD_RIGHT_BUTTON == LOW && rightForward == FALSE) {
            rightBackward = TRUE;
            motorRight = 0b00000010;
            __delay_ms(100);
        }
        if(BACKWARD_RIGHT_BUTTON == HIGH && rightBackward == TRUE) {
            rightBackward = FALSE;
            motorRight = 0b00000000;
            __delay_ms(100);
        }

        // Address Byte
        putch(0b01011011);
        command = ((0b011|teamLED)|motorLeft)|motorRight;
        putch(command);
        putch(command);

    }
}
