/*
 * File:   main.c
 * Author: JDAlfaro
 *
 */

#include <xc.h>                 //Compiler specific include for uC

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

#define _XTAL_FREQ 8000000 // telling compiler how fast chip is

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
    TRISA = 0xFF;               // set all pins in PORTA to inputs
    TRISB = 0x00;               // set all pins in PORTB to outputs
    ANSEL = 0x00;               // ignore this // dont modify
}

int main(void) {
   init(); // call the function above

   int leftForward = FALSE;
   int rightForward = FALSE;
   int leftBackward = FALSE;
   int rightBackward = FALSE;

   while(TRUE){

         // Pressing FORWARD_LEFT (ACTIVE_LOW)
        if(FORWARD_LEFT_BUTTON == LOW && leftBackward == FALSE) {
            leftForward = TRUE;
            FORWARD_LEFT = HIGH;
            __delay_ms(100);
        }
        if(FORWARD_LEFT_BUTTON == HIGH && leftForward == TRUE) {
            leftForward = FALSE;
            FORWARD_LEFT = LOW;
            __delay_ms(100);
        }

        // Pressing FORWARD_RIGHT (ACTIVE_LOW)
        if(FORWARD_RIGHT_BUTTON == LOW && rightBackward == FALSE) {
            rightForward = TRUE;
            FORWARD_RIGHT = HIGH;
            __delay_ms(100);
        }
        if(FORWARD_RIGHT_BUTTON == HIGH && rightForward == TRUE) {
            rightForward = FALSE;
            FORWARD_RIGHT = LOW;
            __delay_ms(100);
        }

        // Pressing BACKWARD_LEFT (ACTIVE_LOW)
        if(BACKWARD_LEFT_BUTTON == LOW && leftForward == FALSE) {
            leftBackward = TRUE;
            BACKWARD_LEFT = HIGH;
            __delay_ms(100);
        }
        if(BACKWARD_LEFT_BUTTON == HIGH && leftBackward == TRUE) {
            leftBackward = FALSE;
            BACKWARD_LEFT = LOW;
            __delay_ms(100);
        }

        // Pressing BACKWARD_RIGHT (ACTIVE_LOW)
        if(BACKWARD_RIGHT_BUTTON == LOW && rightForward == FALSE) {
            rightBackward = TRUE;
            BACKWARD_RIGHT = HIGH;
            __delay_ms(100);
        }
        if(BACKWARD_RIGHT_BUTTON == HIGH && rightBackward == TRUE) {
            rightBackward = FALSE;
            BACKWARD_RIGHT = LOW;
            __delay_ms(100);
        }
        
    }
}

