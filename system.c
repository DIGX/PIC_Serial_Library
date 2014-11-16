/*
 * File:   system.c
 * Author: Shamnad.T
 * Ver: 1.0
 * Created on Oct 8, 2014
 */
#include "system.h"

void Osc_Setup (unsigned char CLK_SRC)
{
//    Input = INTERNAL/EXTERNAL Clock Source - Frequency will be set using _XTAL_FREQ
    unsigned char clock_sel;
    
//    Auto Set Clock Frequency
    switch (_XTAL_FREQ)
    {
            case 8000000:
                clock_sel = 0b01110000;
                break;
            case 4000000:
                clock_sel = 0b01100000;
                break;
            case 2000000:
                clock_sel = 0b01010000;
                break;
            case 1000000:
                clock_sel = 0b01000000;
                break;
            case 500000:
                clock_sel = 0b00110000;
                break;
            case 250000:
                clock_sel = 0b00100000;
                break;
            case 125000:
                clock_sel = 0b00010000;
                break;
            default:
                clock_sel = 0b01110000;
    }

    OSCCON = OSCCON & 0b10001111;
    OSCCON = OSCCON | clock_sel;

//    Select INTERNAL or EXTERNAL Clock Source
    SCS = CLK_SRC;
}

void System_Setup (void)
{
//    ENABLE/DISABLE Pullups
    PULLUP_ENABLE;
//    DISABLE all Analog Pins by default.
    ANSEL = 0x00;
    ANSELH = 0x00;
}

