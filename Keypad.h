/* 
 * File:   Keypad.h
 * Author: Shamnad
 *
 * Created on 12 October 2014, 02:07
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include "system.h"

// Pin defines for Keypad
//connect to the row pinouts of the keypad
#define KP_ROW1			RB0
#define KP_ROW2			RB1
#define KP_ROW3			RB2
#define KP_ROW4			RB3
//connect to the column pinouts of the keypad
#define KP_COL1			RB4
#define KP_COL2			RB5
#define KP_COL3			RB6
#define KP_COL4			RB7

//Direction control
#define KP_ROW1_dir             TRISB0
#define KP_ROW2_dir             TRISB1
#define KP_ROW3_dir             TRISB2
#define KP_ROW4_dir             TRISB3
#define KP_COL1_dir             TRISB4
#define KP_COL2_dir             TRISB5
#define KP_COL3_dir             TRISB6
#define KP_COL4_dir             TRISB7

//Interrupt-on-change; Required pins only
#define KP_COL1_interrupt       IOCB4
#define KP_COL2_interrupt       IOCB5
#define KP_COL3_interrupt       IOCB6
#define KP_COL4_interrupt       IOCB7


/*******************************************************************************
* PRIVATE CONSTANTS                                                            *
*******************************************************************************/
//Set the amount of milliseconds the keypad will wait until it accepts
//a new keypress/keyEvent. This is the "time delay" debounce method.
#define DEBOUNCE_DELAY      10
//Set the amount of milliseconds the user will have to hold a button
//until the HOLD state is triggered.
#define KEYHOLD_DELAY       300

#define ROWS                4
#define COLS                4

#define PRESSED             'P'
#define RELEASED            'R'
#define WITH_ISR            1
#define WITHOUT_ISR         0

// Keymap - Edit this according to your custom requirements
const char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','X'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};

// Function prototypes
void Keypad_begin(unsigned char Keypad_ISR_Enable);
void Select_ROW(unsigned char row);
void Keypad_busEnable(void);
void LCD_busEnable(void);
unsigned char Keypad_ISR(void);
unsigned char Keypad_waitForKey(void);
unsigned char Keypad_ALTwaitForKey(void);
unsigned char Keypad_getKey(void);
unsigned char Keypad_ALTgetKey(void);
unsigned char findKey_inRow(unsigned char row);
unsigned char Keypad_getKeyState(unsigned char row, unsigned char col);
bit Confirm_COL(unsigned char col);

#endif	/* KEYPAD_H */

