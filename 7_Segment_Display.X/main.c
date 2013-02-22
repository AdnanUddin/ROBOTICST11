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

void zero(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = LOW;
    F = LOW;
    G = HIGH;
}

void one(void){
    A = HIGH;
    B = LOW;
    C = LOW;
    D = HIGH;
    E = HIGH;
    F = HIGH;
    G = HIGH;
}

void two(void){
    A = LOW;
    B = LOW;
    C = HIGH;
    D = LOW;
    E = LOW;
    F = HIGH;
    G = LOW;
}

void three(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = HIGH;
    F = HIGH;
    G = LOW;
}

void four(void){
    A = HIGH;
    B = LOW;
    C = LOW;
    D = HIGH;
    E = HIGH;
    F = LOW;
    G = LOW;
}

void five(void){
    A = LOW;
    B = HIGH;
    C = LOW;
    D = LOW;
    E = HIGH;
    F = LOW;
    G = LOW;
}

void six(void){
    A = LOW;
    F = LOW;
    G = LOW;
    C = LOW;
    D = LOW;
    E = LOW;
    B = HIGH;
}

void seven(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = HIGH;
    E = HIGH;
    F = HIGH;
    G = HIGH;
}

void eight(void){
    A = LOW;
    B = LOW;
    C = LOW;
    D = LOW;
    E = LOW;
    F = LOW;
    G = LOW;
}

void nine(void){
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
        one();
        __delay_ms(1000);
        two();
        __delay_ms(1000);
        three();
        __delay_ms(1000);
        four();
        __delay_ms(1000);
        five();
        __delay_ms(1000);
        six();
        __delay_ms(1000);
        seven();
        __delay_ms(1000);
        eight();
        __delay_ms(1000);
        nine();
        __delay_ms(1000);
        zero();
        __delay_ms(1000);
    }
}