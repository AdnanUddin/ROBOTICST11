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

void init(void){

    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins in PORTA as outputs
    TRISB = 0b000000100;         // set RB2 as input
    ANSEL = 0x00;               // ignore this

    init_comms(); //Prepare the usart
}

int main(void) {

    init(); //Intialize the setups

    while(1){
        putch('1');
        __delay_ms(500);
        putch('2');
        __delay_ms(500);
        putch('3');
        __delay_ms(500);
    }
}

