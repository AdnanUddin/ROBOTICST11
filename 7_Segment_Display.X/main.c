/*
 * File:   main.c
 * Author: Rafi, JDAlfaro
 *
 * Description: Cycles from 0 to 9 in 1 second intervals
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

// Define pins for segments
#define A RA1
#define B RA0
#define C RA7
#define D RA6
#define E RA3
#define F RA2
#define G RA4

// Define constants
#define TRUE 1
#define FALSE 0

#define LOW 0
#define HIGH 1

void init(void){

    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins in PORTA as outputs
    TRISB = 0x00;               // set all pins in PORTB as outputts
    ANSEL = 0x00;               // ignore this // dont modify

    // initialize segments to OFF
    A = HIGH;
    B = HIGH;
    C = HIGH;
    D = HIGH;
    E = HIGH;
    F = HIGH;
    G = HIGH;
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

int main() {
   init(); // call the function above

   while(TRUE){
        zeroDisplay();
        __delay_ms(1000);
        oneDisplay();
        __delay_ms(1000);
        twoDisplay();
        __delay_ms(1000);
        threeDisplay();
        __delay_ms(1000);
        fourDisplay();
        __delay_ms(1000);
        fiveDisplay();
        __delay_ms(1000);
        sixDisplay();
        __delay_ms(1000);
        sevenDisplay();
        __delay_ms(1000);
        eightDisplay();
        __delay_ms(1000);
        nineDisplay();
        __delay_ms(1000);
    }
}