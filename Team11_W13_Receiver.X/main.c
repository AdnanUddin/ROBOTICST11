/**
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
#define ON 1 //Define on State for LEDS
#define OFF 0 //Define off state for LEDS

#define FORWARD_LEFT RB0
#define FORWARD_RIGHT RB1
#define BACKWARD_LEFT RB2
#define BACKWARD_RIGHT RB3

#define FALSE 0
#define TRUE 1

void init(void){

    OSCCON = 0b01100000;	//set frequency to 4MHz
    TRISA = 0x00;               // set all pins as outputs
    TRISB = 0b000000000;
    ANSEL = 0x00;               // ignore this

    init_comms(); //Prepare the usart
}

int main(void) {
   init(); // call the function above
   char temp;
   char command;
   char checksum;

   while(TRUE){
        // Receive address and password
        temp = getche();

        // Check Address
        if (temp ==  0b01011011) {
            command = getche();
            checksum = getche();
            if (command == checksum && (command&0b11100000) == 0b01100000) {
                // Right Motor
                if (command&0b00000011 == 0b00000001) {
                    RA2 = ON;
                    RA3 = OFF;
                } else if (command&0b00000011 == 0b00000010) {
                    RA2 = OFF;
                    RA3 = ON;
                } else {
                    RA2 = OFF;
                    RA3 = OFF;
                }

                // Left Motor
                if (command & 0b00001100 == 0b00000100) {
                    RA0 = ON;
                    RA1 = OFF;
                } else if (command & 0b00001100 == 0b00001000) {
                    RA0 = OFF;
                    RA1 = ON;
                } else {
                    RA0 = OFF;
                    RA1 = OFF;
                }

                // Team LED
                if (command & 0b0001000 == 0b00010000) {
                    RB0 = ON;
                    RB1 = OFF;
                } else {
                    RB0 = OFF;
                    RB1 = ON;
                }
            }
        } else {
            RA0 = OFF;
            RA1 = OFF;
            RA2 = OFF;
            RA3 = OFF;
            RB0 = OFF;
            RB1 = OFF;
        }
    }
}

