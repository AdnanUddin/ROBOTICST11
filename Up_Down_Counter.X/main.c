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

#define TRUE 1
#define FALSE 0

#define LOW 0
#define HIGH 1

void init(void){

    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins in PORTA as outputs, might change
    TRISB = 0x01;               // set all pins in PORTB as outputts except RB0
    ANSEL = 0x00;               // ignore this // dont modifu

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
    G = LOW;
    E = LOW;
    D = LOW;
    F = HIGH;
}
void three(void){
    A = LOW;
    B = LOW;
    G = LOW;
    C = LOW;
    D = LOW;
    E = HIGH;
    F = HIGH;
}
void four(void){
    F = LOW;
    B = LOW;
    G = LOW;
    C = LOW;
    A = HIGH;
    D = HIGH;
    E = HIGH;
}
void five(void){
    A = LOW;
    F = LOW;
    G = LOW;
    C = LOW;
    D = LOW;
    B = HIGH;
    E = HIGH;
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

int main(void) {
   init(); // call the function above
   int buttonFlag = 0;
   int zero = 1;
   int one;
   int two;
   int three;
   int four;
   zero();
   while(TRUE){

        if(RB0 == 0) {
            buttonFlag = 1;
        }

        if(zero == 1 && buttonFlag == 1) {
            one();
            buttonFlag = 0;
            one = 1;
            zero = 0;
        }
        if(one == 1 && buttonFlag == 1) {
            two();
            buttonFlag = 0;
            two = 1;
            one = 0;
        }
        if(two == 1 && buttonFlag == 1) {
            three();
            buttonFlag = 0;
            three = 1;
            two = 0;
        }
        if(three == 1 && buttonFlag == 1) {
            four();
            buttonFlag = 0;
            four = 1;
            three =0;
        }
        if(four == 1 && buttonFlag == 1) {
            zero();
            buttonFlag = 0;
            zero = 1;
            four = 0;
        }
    }
}

