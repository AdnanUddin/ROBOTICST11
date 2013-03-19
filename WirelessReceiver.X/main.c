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

#define A RB1
#define B RB0
#define C RA3
#define D RA7
#define E RA6
#define F RB4
#define G RB3

#define ON 1
#define OFF 0

void init(void){

    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins in PORTA as outputs
    TRISB = 0b000000100;         // set RB2 as input
    ANSEL = 0x00;               // ignore this

    PORTA = 0x00;
    PORTB = 0x00;

    init_comms(); //Prepare the usart
}
// Active High
allOff(void){
    A = OFF;
    B = OFF;
    C = OFF;
    D = OFF;
    E = OFF;
    F = OFF;
    G = OFF;
}
// Active High
drawOne(void){
    allOff();
    B = ON;
    C = ON;
}
// Active High
drawTwo(void){
    allOff();
    A = ON;
    B = ON;
    D = ON;
    E = ON;
    G = ON;
}
// Active High
drawThree(void){
    allOff();
    A = ON;
    B = ON;
    C = ON;
    D = ON;
    G = ON;
}

int main(void) {
    char temp;
    init(); //Intialize the setups

    while(1){
        temp = getche();

        if (temp == '1')
            drawOne();
        else if (temp == '2')
            drawTwo();
        else if (temp == '3')
            drawThree();
        else {
            allOff();
            G = ON;
        }
    }
}

