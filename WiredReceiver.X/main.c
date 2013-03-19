/**
 *@file:   main.c
 *@author: Michael, JDAlfaro
 *
 *@date March 11, 2013
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

#define A RA1
#define B RA0
#define C RA7
#define D RA6
#define E RA3
#define F RA2
#define G RA4

#define LOW 0
#define HIGH 1

void init(void){

    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins in PORTA as outputs
    TRISB = 0b000000100;         // set RB2 as input
    ANSEL = 0x00;               // ignore this

    PORTA = 0x00;
    PORTB = 0x00;

    init_comms(); //Prepare the usart
}
// Display - on the 7 Segment Display (ACTIVE_LOW
barDisplay(void){
    A = HIGH;
    B = HIGH;
    C = HIGH;
    D = HIGH;
    E = HIGH;
    F = HIGH;
    G = LOW;
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

void fourDisplay(void){
    A = HIGH;
    B = LOW;
    C = LOW;
    D = HIGH;
    E = HIGH;
    F = LOW;
    G = LOW;
}


int main(void) {
    char temp;
    init(); //Intialize the setups

    while(1){
        temp = getche();

        if (temp == '1')
            oneDisplay();
        else if (temp == '2')
            twoDisplay();
        else if (temp == '3')
            threeDisplay();
        else if (temp == '4')
            fourDisplay();
        else
            barDisplay();
    }
}

