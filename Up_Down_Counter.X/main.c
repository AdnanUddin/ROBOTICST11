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

// Define pins 7 Segment Display
#define A RA1
#define B RA0
#define C RA7
#define D RA6
#define E RA3
#define F RA2
#define G RA4

// Define Up & Down Buttons
#define UP_BUTTON RB0
#define DOWN_BUTTON RB1

// Define constants
#define TRUE 1
#define FALSE 0

#define LOW 0
#define HIGH 1

// public variables
int count;


void init(void){
    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins in PORTA as outputs for 7 Segment Display
    TRISB = 0x03;               // set RBO and RB1 to outputs
    ANSEL = 0x00;               // ignore this // dont modifu

    // Initialize to 7 Segment Display and count to 0
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = LOW;
    F = LOW;
    G = HIGH;
    count = 0;
}

// Display 0 on the 7 Segment Display (ACTIVE_LOW)
void zeroDisplay(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = LOW;
    F = LOW;
    G = HIGH;
}

// Display 1 on the 7 Segment Display (ACTIVE_LOW)
void oneDisplay(void){
    A = HIGH;
    B = LOW;
    C = LOW;
    D = HIGH;
    E = HIGH;
    F = HIGH;
    G = HIGH;
}

// Display 2 on the 7 Segment Display (ACTIVE_LOW)
void twoDisplay(void){
    A = LOW;
    B = LOW;
    C = HIGH;
    D = LOW;
    E = LOW;
    F = HIGH;
    G = LOW;
}

// Display 3 on the 7 Segment Display (ACTIVE_LOW)
void threeDisplay(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = HIGH;
    F = HIGH;
    G = LOW;
}

// Display 4 on the 7 Segment Display (ACTIVE_LOW)
void fourDisplay(void){
    A = HIGH;
    B = LOW;
    C = LOW;
    D = HIGH;
    E = HIGH;
    F = LOW;
    G = LOW;
}

// Display 5 on the 7 Segment Display (ACTIVE_LOW)
void fiveDisplay(void){
    A = LOW;
    B = HIGH;
    C = LOW;
    D = LOW;
    E = HIGH;
    F = LOW;
    G = LOW;
}

// Display 6 on the 7 Segment Display (ACTIVE_LOW)
void sixDisplay(void){
    A = LOW;
    F = LOW;
    G = LOW;
    C = LOW;
    D = LOW;
    E = LOW;
    B = HIGH;
}

// Display 7 on the 7 Segment Display (ACTIVE_LOW)
void sevenDisplay(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = HIGH;
    E = HIGH;
    F = HIGH;
    G = HIGH;
}

// Display 8 on the 7 Segment Display (ACTIVE_LOW)
void eightDisplay(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = LOW;
    F = LOW;
    G = LOW;
}

// Display 9 on the 7 Segment Display (ACTIVE_LOW)
void nineDisplay(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = HIGH;
    F = LOW;
    G = LOW;
}

void countUp(void) {
    count = count + 1;
    if (count > 9)
    {
        count = 0;
    }
}

void countDown(void) {
    count = count - 1;
    if (count < 0)
    {
        count = 9;
    }
}

int main(void) {
   init(); // call the function above
   
   // Set/Reset Variables
   int upButtonFlag = FALSE;
   int downButtonFlag = FALSE;

   while(TRUE){

        // Pressing UP_BUTTON (ACTIVE_LOW)
        if(UP_BUTTON == LOW &&  upButtonFlag == FALSE) {
            countUp();
            upButtonFlag = TRUE;
            __delay_ms(100);
        }
        // Releasing UP_BUTTON
        if(UP_BUTTON == HIGH &&  upButtonFlag == TRUE) {
            upButtonFlag = FALSE;
            __delay_ms(100);
        }

        // Pressing DOWN_BUTTON (ACTIVE_LOW)
        if(DOWN_BUTTON == LOW &&  downButtonFlag == FALSE) {
            countDown();
            downButtonFlag = TRUE;
            __delay_ms(100);
        }
        // Releasing DOWN_BUTTON
        if(DOWN_BUTTON == HIGH &&  downButtonFlag == TRUE) {
            downButtonFlag = FALSE;
            __delay_ms(100);
        }

        // Dispay Patterns
        if(count == 0) {
            zeroDisplay();
        }
        if(count == 1) {
            oneDisplay();
        }
        if(count == 2) {
            twoDisplay();
        }
        if(count == 3) {
            threeDisplay();
        }
        if(count == 4) {
            fourDisplay();
        }
        if(count == 5) {
            fiveDisplay();
        }
        if(count == 6) {
            sixDisplay();
        }
        if(count == 7) {
            sevenDisplay();
        }
        if(count == 8) {
            eightDisplay();
        }
        if(count == 9) {
            nineDisplay();
        }
    }
}

