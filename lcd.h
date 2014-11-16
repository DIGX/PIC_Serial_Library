/*
 * File:   lcd.h
 * Author: Shamnad.T
 * Ver: 1.0
 * Created on Oct 8, 2014
 */

/*******************************************************************************
* This file provides the functions for the HD44780 based
* LCD display in 4 bit interface
*******************************************************************************/

#ifndef _LCD_H
#define _LCD_H

#include "system.h"

volatile unsigned char           LCDPINS              @ 0x190;
//LCD bit and bitfield definitions
volatile bit LCDPINS_0              @ ((unsigned)&LCDPINS*8)+0;
volatile bit LCDPINS_1              @ ((unsigned)&LCDPINS*8)+1;
volatile bit LCDPINS_2              @ ((unsigned)&LCDPINS*8)+2;
volatile bit LCDPINS_3              @ ((unsigned)&LCDPINS*8)+3;
volatile bit LCDPINS_4              @ ((unsigned)&LCDPINS*8)+4;
volatile bit LCDPINS_5              @ ((unsigned)&LCDPINS*8)+5;
volatile bit LCDPINS_6              @ ((unsigned)&LCDPINS*8)+6;
volatile bit LCDPINS_7              @ ((unsigned)&LCDPINS*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned    LCDPINS_0              : 1;
        unsigned    LCDPINS_1              : 1;
        unsigned    LCDPINS_2              : 1;
        unsigned    LCDPINS_3              : 1;
        unsigned    LCDPINS_4              : 1;
        unsigned    LCDPINS_5              : 1;
        unsigned    LCDPINS_6              : 1;
        unsigned    LCDPINS_7              : 1;
    };
} LCDPINSbits @ 0x190;
#endif


// Pin defines for HD44780 based Character LCD
#define LCD_RS			RA0		// RS pin is used for LCD to differentiate data is command or character
#define LCD_E			RA1		// Enable pin

// Data bus for 4 bit mode
#define LCD_4			RB4
#define LCD_5			RB5
#define LCD_6			RB6
#define LCD_7			RB7

// TRIS Setting for a pins
#define LCD_RS_dir		TRISA0
#define LCD_E_dir		TRISA1

#define LCD_4_dir		TRISB4
#define LCD_5_dir		TRISB5
#define LCD_6_dir		TRISB6
#define LCD_7_dir		TRISB7

/*******************************************************************************
* PRIVATE CONSTANTS                                                            *
*******************************************************************************/
/* The protocol for the LCD
R/S	DB7	DB6	DB5	DB4	DB3	DB2	DB1	DB0	Functions
0	0	0	0	0	0	0	0	1	Clear LCD
0	0	0	0	0	0	0	1	X	Return cursor to home position
0	0	0	0	0	0	1	ID	S	Set cursor move direction
0	0	0	0	0	1	D	C	B	Enable Display/Cursor
0	0	0	0	1	SC	RL	X	X	Move Cursor/Shift Display
0	0	0	1	DL	N	F	X	X	Set Interface length and Display format
0	1	A	A	A	A	A	A	A	Move Cursor to DDRAM
1	D	D	D	D	D	D	D	D	Write a character to Display and DDRAM
X = Don't care
A = Address
*/

/* LCD command bit value and function
Bit name    Bit Function                    if 0                if 1
================================================================================
R/S         Command or Character            Command             Character
ID          Set cursor move direction       Decrement           Increment
S           Specifies to shift display      No shift            Display shift
D           Set display On/Off              Display Off         Display On
C           Cursor On/Off                   Cursor Off          Cursor On
B           Cursor Blink                    Cursor Blink Off    Cursor Blink On
SC          Set cursor move or shift D      Move Cursor         Shift Display
RL          Shift direction                 Shift Left          Shift Right
DL          Sets Interface data length      4-bit Interface     8-bit Interface
N           Number of display line          1 line              2 line
F           Character font                  5x7 dots            5x10 dots
*/

// The command code for the LCD.
#define CLEAR           0b00000001	// Clear the LCD display.
#define HOME		0b00000010	// Return to home.

// The maskable command code to change the configuration of the LCD.
#define ENTRY_MODE_SET	0b00000100	// Bit: 0  0  0  0  0  1  ID S
#define DISPLAY_CONTROL	0b00001000	// Bit: 0  0  0  0  1  D  C  B
#define FUNCTION_SET	0b00100000	// Bit: 0  0  1  DL N  F  0  0

// The mask to change the ENTRY MODE of the LCD.
#define DEC_MODE            0b00000000	// Increment.
#define INC_MODE            0b00000010	// Increment.
#define NO_SHIFT            0b00000000	// No Shift.
#define SHIFT               0b00000001	// Shift.

// The mask to change the DISPLAY CONTROL of the LCD.
#define DISP_OFF            0b00000000	// Display Off.
#define DISP_ON             0b00000100	// Display On.
#define CURS_OFF            0b00000000	// No Cursor.
#define CURS_ON             0b00000010	// Display Cursor.
#define NO_BLINK            0b00000000	// Blink off.
#define BLINK               0b00000001	// Blink Cursor.

// The mask to change the FUNCTION SET of the LCD.
#define DL_8                0b00010000	// Select 8-bit data bus.
#define DL_4                0b00000000	// Select 4-bit data bus.
#define ONE_LINE            0b00000000	// Select Single line display.
#define TWO_LINE            0b00001000	// Select 2-line display.
#define NORMAL_FONT         0b00000000	// Select 5 x 8 dots character.
#define LARGE_FONT          0b00000100	// Select 5 x 10 dots character.

// The maskable command to change the LCD RAM address.
#define SET_DDRAM_ADDRESS   0b10000000	// Bit 0 - 7: Address

// The DDRAM address corresponding to the second row of the LCD.
#define SECOND_ROW			0x40
#define THIRD_ROW			0x10
#define FOURTH_ROW			0x50

// Data and command defines for LCD
#define L_CMD                   0
#define L_DATA                  1
/*******************************************************************************
* PRIVATE FUNCTION PROTOTYPES                                                  *
*******************************************************************************/

void Set_LCD_Pins8(unsigned char rs, unsigned char datain);
void Set_LCD(unsigned char rs, unsigned char datain);
void LCD_setCursor(unsigned char line, unsigned char pos);
void LCD_print(unsigned char line, unsigned char pos, unsigned char *str);
void LCD_BCDprint(unsigned char required_digits, unsigned int the_number);
void LCD_putchar(char datain);
void LCD_begin(void);
void LCD_clear(void);
void LCD_home(void);
void LCD_display(void);
void LCD_noDisplay(void);


#endif
