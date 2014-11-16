/*
 * File:   Keypad.c
 * Author: Shamnad
 *
 * Created on 12 October 2014, 03:00
 */

// include the header for Keypad library:
#include "Keypad.h"
#include "lcd.h"

/*******************************************************************************
* This file provides the functions for the Custom Matrix Keypad
*******************************************************************************/

/*
  Matrix Keypad Library for PIC16F887
================================================================================
 * Usages examples
 * ----------------------------------------------------------------------------
 * Keypad_begin(WITH_ISR)           - Initialise the Keypad with Keypad Interrupt Enabled(WITH_ISR or WITHOUT_ISR)
 * Key = Keypad_waitForKey()        - Wait until a Key is pressed(It blocks the execution)
 * Key = Keypad_getKey()            - Get the Key if pressed(Non-blocking)
 * Stat = Keypad_getKeyState(2,3)   - Get status of Key positioned at ROW 2 and COL 3(PRESSED or RELEASED)
 *
 * Key = Keypad_ISR()               - ISR for Keypad to call from MAIN Interrupt routine

 
 This code is written utilizing the "Interrupt on Pin Change" feature of PORTB
 in PICmicro devices when working with Keypad INTERRUPT Enabled. Keep the
 COLUMN connections to PORTB4-7 to maintain compatibility with all PICmicro series.

 The circuit:
 * Keypad Row 1 pin any available port define as KP_ROW1 in Keypad.h
 * Keypad Row 2 pin any available port define as KP_ROW2 in Keypad.h
 * Keypad Row 3 pin any available port define as KP_ROW3 in Keypad.h
 * Keypad Row 4 pin any available port define as KP_ROW4 in Keypad.h
 * Keypad Column 1 pin connected to PORTB4 define as KP_COL1 in Keypad.h
 * Keypad Column 2 pin connected to PORTB5 define as KP_COL2 in Keypad.h
 * Keypad Column 3 pin connected to PORTB6 define as KP_COL3 in Keypad.h
 * Keypad Column 4 pin connected to PORTB7 define as KP_COL4 in Keypad.h
 * 4 x 10K resistor: Pullup Resistors need to be connected between Keypad Column pins and VCC.
 * --Only needed if Keypad Column pins connected to ports other than PORTB--
 *
 * Direction Controls defined in Keypad.h
 * eg:-
 * #define KP_ROW1_dir TRISB0
 * #define KP_ROW2_dir TRISB1
 * #define KP_ROW3_dir TRISB2
 * #define KP_ROW4_dir TRISB3
 * #define KP_COL1_dir TRISB4
 * #define KP_COL2_dir TRISB5
 * #define KP_COL3_dir TRISB6
 * #define KP_COL4_dir TRISB7
 */


/*******************************************************************************
* PRIVATE GLOBAL VARIABLES                                                     *
*******************************************************************************/

/*******************************************************************************
* PUBLIC FUNCTION: Keypad_busEnable
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the Matrix Keypad bus.
*
*******************************************************************************/
void Keypad_busEnable()
{
    // This is for 4x4 Matrix keypad. Customize this code for any other size
    KP_COL1     = 1;
    KP_COL2     = 1;
    KP_COL3     = 1;
    KP_COL4     = 1;

    KP_ROW1     = 1;
    KP_ROW2     = 1;
    KP_ROW3     = 1;
    KP_ROW4     = 1;

    KP_ROW1_dir = OUTPUT;
    KP_ROW2_dir = OUTPUT;
    KP_ROW3_dir = OUTPUT;
    KP_ROW4_dir = OUTPUT;

    KP_COL1_dir = INPUT;
    KP_COL2_dir = INPUT;
    KP_COL3_dir = INPUT;
    KP_COL4_dir = INPUT;

    KP_ROW1     = 1;
    KP_ROW2     = 1;
    KP_ROW3     = 1;
    KP_ROW4     = 1;

    KP_COL1     = 1;
    KP_COL2     = 1;
    KP_COL3     = 1;
    KP_COL4     = 1;

    PULLUP_ENABLE;

    // Enable all individual pullups. Ports configured as OUTPUT get it disabled
    //automatically. Change this if you want to disable any port pullups.
    WPUB = 0xFF;
}

/*******************************************************************************
* PUBLIC FUNCTION: LCD_busEnable
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the LCD Keypad bus.
*
*******************************************************************************/
void LCD_busEnable()
{
    KP_ROW1     = 1;
    KP_ROW2     = 1;
    KP_ROW3     = 1;
    KP_ROW4     = 1;

    LCD_4 = 1;          // Data bus = 0
    LCD_5 = 1;
    LCD_6 = 1;
    LCD_7 = 1;

    LCD_RS_dir  = OUTPUT;     // Set as Output
    LCD_E_dir   = OUTPUT;

    LCD_4_dir   = OUTPUT;
    LCD_5_dir   = OUTPUT;
    LCD_6_dir   = OUTPUT;
    LCD_7_dir   = OUTPUT;

    LCD_RS = 1;         // RS  = 0
    LCD_E = 0;          // E  = 0

    LCD_4 = 1;          // Data bus = 0
    LCD_5 = 1;
    LCD_6 = 1;
    LCD_7 = 1;
}

/*******************************************************************************
* PUBLIC FUNCTION: Keypad_ALTgetKey
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the Matrix Keypad.
*
*******************************************************************************/
unsigned char Keypad_ALTgetKey()
{
    unsigned char Key = 0;

    Keypad_busEnable();

    KP_ROW1     = LOW;
    KP_ROW2     = LOW;
    KP_ROW3     = LOW;
    KP_ROW4     = LOW;
    
    if (KP_COL1==1 && KP_COL2==1 && KP_COL3==1 && KP_COL4==1)
    {
        return Key;
    }
    else
    {
            // Start Row Scaning
        for (unsigned char row=1; row<=ROWS; row++)
        {
            Select_ROW(row);
            Key = findKey_inRow(row);
            if (Key)
                break;          // Break the scan if any Key found
        }

        LCD_busEnable();

        __delay_ms(KEYHOLD_DELAY);  //Apply a Typematic/Hold delay
        return Key;
    }
}

/*******************************************************************************
* PUBLIC FUNCTION: Keypad_ALTgetKey
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the Matrix Keypad.
*
*******************************************************************************/
unsigned char Keypad_ALTwaitForKey()
{
    unsigned char Key = 0;

    Keypad_busEnable();


    while(Key==0)   // Loop and wait for Key
    {
        // Start Row Scaning
        for (unsigned char row=1; row<=ROWS; row++)
        {
            Select_ROW(row);
            Key = findKey_inRow(row);
            if (Key)
                break;          // Break the scan if any Key found
        }
    }

    LCD_busEnable();

    __delay_ms(KEYHOLD_DELAY);  //Apply a Typematic/Hold delay
    return Key;
}

/*******************************************************************************
* PUBLIC FUNCTION: Keypad_begin
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the Matrix Keypad.
*
*******************************************************************************/

void Keypad_begin(unsigned char Keypad_ISR_Enable)
{
    // This is for 4x4 Matrix keypad. Customize this code for any other size
    KP_ROW1_dir = OUTPUT;
    KP_ROW2_dir = OUTPUT;
    KP_ROW3_dir = OUTPUT;
    KP_ROW4_dir = OUTPUT;

    KP_COL1_dir = INPUT;
    KP_COL2_dir = INPUT;
    KP_COL3_dir = INPUT;
    KP_COL4_dir = INPUT;

    KP_ROW1     = 0;
    KP_ROW2     = 0;
    KP_ROW3     = 0;
    KP_ROW4     = 0;

    KP_COL1     = 1;
    KP_COL2     = 1;
    KP_COL3     = 1;
    KP_COL4     = 1;

    PULLUP_ENABLE;

    // Enable all individual pullups. Ports configured as OUTPUT get it disabled
    //automatically. Change this if you want to disable any port pullups.
    WPUB = 0xFF;

    if (Keypad_ISR_Enable)
    {
        // Enable Interrupt-on-change feature
        KP_COL1_interrupt = ENABLE;
        KP_COL2_interrupt = ENABLE;
        KP_COL3_interrupt = ENABLE;
        KP_COL4_interrupt = ENABLE;

        RBIF    = 0;                // Initialize interrupt flag
        RBIE    = ENABLE;           // Enable Keypad Interrupt

        GIE     = ENABLE;           // Enable Global Interrupt
    }
}

/*******************************************************************************
* PUBLIC FUNCTION: Keypad_waitForKey
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ unsigned char       - Return pressed KEY
*
* DESCRIPTIONS:
* This function will wait forever until someone presses a key.
* Warning: It blocks all other code until a key is pressed.
* That means no blinking LED's, no LCD screen updates,
* no nothing with the exception of interrupt routines.
*
*******************************************************************************/
unsigned char Keypad_waitForKey(void)
{
    unsigned char Key = 0;
    while(Key==0)
        Key = Keypad_getKey();
    return Key;
}

/*******************************************************************************
* PUBLIC FUNCTION: Keypad_getKey
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ unsigned char       - Return pressed KEY
*
* DESCRIPTIONS:
* Returns the key that is pressed, if any. This function is non-blocking.
*
*******************************************************************************/
unsigned char Keypad_getKey()
{
    unsigned char Key = 0;
    if (KP_COL1==1 && KP_COL2==1 && KP_COL3==1 && KP_COL4==1)
    {
        return Key;
    }
    else
    {
        // Start Row Scaning
        for (unsigned char row=1; row<=ROWS; row++)
        {
            Select_ROW(row);
            Key = findKey_inRow(row);
            if (Key)
                break;          // Break the scan if any Key found
        }

        // Back to normal
        KP_ROW1     = LOW;
        KP_ROW2     = LOW;
        KP_ROW3     = LOW;
        KP_ROW4     = LOW;

        __delay_ms(KEYHOLD_DELAY);  //Apply a Typematic/Hold delay
        return Key;
    }
}

/*******************************************************************************
* PUBLIC FUNCTION: Select_ROW
*
* PARAMETERS:
* ~ row                 - Row position of the Key
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Activates the selected Row of Keypad
*
*******************************************************************************/
void Select_ROW(unsigned char row)
{
    //De-activate all Rows
    KP_ROW1     = HIGH;
    KP_ROW2     = HIGH;
    KP_ROW3     = HIGH;
    KP_ROW4     = HIGH;
    switch (row)
    {
        case 1:
            // Enable first row
            KP_ROW1     = LOW;
            break;
        case 2:
            // Enable second row
            KP_ROW2     = LOW;
            break;
        case 3:
            // Enable third row
            KP_ROW3     = LOW;
            break;
        case 4:
            // Enable fourth row
            KP_ROW4     = LOW;
            break;
    }
}
/*******************************************************************************
* PUBLIC FUNCTION: findKey_inRow
*
* PARAMETERS:
* ~ row                 - Row position of the Key
*
* RETURN:
* ~ unsigned char       - Return Key Value
*
* DESCRIPTIONS:
* Finds the Key Value for a given Row
*
*******************************************************************************/
unsigned char findKey_inRow(unsigned char row)
{
    unsigned char Key = 0;
    static bit Key_Confirmed = FALSE;

    // Check each column
    for (unsigned char col=1; col<=COLS; col++)
    {
        //Check selected column
        Key_Confirmed  = Confirm_COL(col);
        if (Key_Confirmed)
        {
            Key = keys[row-1][col-1]; //Retrieve Key Value
            break;
        }
    }
    return Key;
}

/*******************************************************************************
* PUBLIC FUNCTION: Keypad_getKeyState
*
* PARAMETERS:
* ~ row                 - Row position of the Key
* ~ Column              - Column position of the Key
*
* RETURN:
* ~ unsigned char       - Return present status of the Key
*
* DESCRIPTIONS:
* Returns the current state of any of the keys.
* The states are PRESSED and RELEASED.
*
*******************************************************************************/
unsigned char Keypad_getKeyState(unsigned char row, unsigned char col)
{
    static bit Key_pressed = FALSE;
    Select_ROW(row);
    Key_pressed = Confirm_COL(col);

    // Back to normal
    KP_ROW1     = LOW;
    KP_ROW2     = LOW;
    KP_ROW3     = LOW;
    KP_ROW4     = LOW;

    if(Key_pressed)
        return PRESSED;
    else
        return RELEASED;
}

/*******************************************************************************
* PUBLIC FUNCTION: Confirm_COL
*
* PARAMETERS:
* ~ Column              - Column position of the Key
*
* RETURN:
* ~ bit                 - Confirm a key status of a selected Column
*
* DESCRIPTIONS:
* Returns the current state of any of the keys.
* Confirms the Key is Pressed or NOT(TRUE/FALSE).
*******************************************************************************/
bit Confirm_COL(unsigned char col)
{
    static bit Key_pressed = 0;
    switch (col)
    {
        case 1:
            //Check first column
            if (KP_COL1==0 && KP_COL2==1 && KP_COL3==1 && KP_COL4==1)
            {
                __delay_ms(DEBOUNCE_DELAY);
                //Confirm key
                if (KP_COL1==0 && KP_COL2==1 && KP_COL3==1 && KP_COL4==1)
                    Key_pressed = TRUE;     //Confirm Key is PRESSED
                else
                    Key_pressed = FALSE;    //Confirm Key is RELEASED
            }
            else
                Key_pressed = FALSE;    //Confirm Key is RELEASED
            break;
        case 2:
            //Check second column
            if (KP_COL1==1 && KP_COL2==0 && KP_COL3==1 && KP_COL4==1)
            {
                __delay_ms(DEBOUNCE_DELAY);
                //Confirm key
                if (KP_COL1==1 && KP_COL2==0 && KP_COL3==1 && KP_COL4==1)
                    Key_pressed = TRUE;     //Confirm Key is PRESSED
                else
                    Key_pressed = FALSE;    //Confirm Key is RELEASED
            }
            else
                Key_pressed = FALSE;    //Confirm Key is RELEASED
            break;
        case 3:
            //Check third column
            if (KP_COL1==1 && KP_COL2==1 && KP_COL3==0 && KP_COL4==1)
            {
                __delay_ms(DEBOUNCE_DELAY);
                //Confirm key
                if (KP_COL1==1 && KP_COL2==1 && KP_COL3==0 && KP_COL4==1)
                    Key_pressed = TRUE;     //Confirm Key is PRESSED
                else
                    Key_pressed = FALSE;    //Confirm Key is RELEASED
            }
            else
                Key_pressed = FALSE;    //Confirm Key is RELEASED
            break;
        case 4:
            //Check fourth column
            if (KP_COL1==1 && KP_COL2==1 && KP_COL3==1 && KP_COL4==0)
            {
                __delay_ms(DEBOUNCE_DELAY);
                //Confirm key
                if (KP_COL1==1 && KP_COL2==1 && KP_COL3==1 && KP_COL4==0)
                    Key_pressed = TRUE;     //Confirm Key is PRESSED
                else
                    Key_pressed = FALSE;    //Confirm Key is RELEASED
            }
            else
                Key_pressed = FALSE;    //Confirm Key is RELEASED
            break;
    }
    return Key_pressed;
}


/*******************************************************************************
* PUBLIC FUNCTION: Keypad_ISR
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ unsigned char       - Return pressed KEY
*
* DESCRIPTIONS:
* This function will detect immediately someone presses a key.
* Since this is called from Interrupt, this wont block the main code
*
*******************************************************************************/
unsigned char Keypad_ISR(void)
{
    RBIE = DISABLE;         // Disable Keypad interrupt for a while
    unsigned char Key = 0;
    static bit Key_pressed = FALSE;

    // Start Row Scaning
    for (unsigned char row=1; row<=ROWS; row++)
    {
        Select_ROW(row);
        // Check each column
        for (unsigned char col=1; col<=COLS; col++)
        {
            //Check selected column
            switch (col)
            {
                case 1:
                    //Check first column
                    if (KP_COL1==0 && KP_COL2==1 && KP_COL3==1 && KP_COL4==1)
                        Key_pressed = TRUE;     //Confirm Key is PRESSED
                    else
                        Key_pressed = FALSE;    //Confirm Key is RELEASED

                    break;
                case 2:
                    //Check second column
                    if (KP_COL1==1 && KP_COL2==0 && KP_COL3==1 && KP_COL4==1)
                        Key_pressed = TRUE;     //Confirm Key is PRESSED
                    else
                        Key_pressed = FALSE;    //Confirm Key is RELEASED
                    break;
                case 3:
                    //Check third column
                    if (KP_COL1==1 && KP_COL2==1 && KP_COL3==0 && KP_COL4==1)
                        Key_pressed = TRUE;     //Confirm Key is PRESSED
                    else
                        Key_pressed = FALSE;    //Confirm Key is RELEASED
                    break;
                case 4:
                    //Check fourth column
                    if (KP_COL1==1 && KP_COL2==1 && KP_COL3==1 && KP_COL4==0)
                        Key_pressed = TRUE;     //Confirm Key is PRESSED
                    else
                        Key_pressed = FALSE;    //Confirm Key is RELEASED
                    break;
                default:
                    Key_pressed = FALSE;    //Nothing found
            }
            if (Key_pressed)
            {
                Key = keys[row-1][col-1]; //Retrieve Key Value
                break;
            }
        }
        if (Key)
            break;          // Break the scan if any Key found
    }

    // Back to normal
    KP_ROW1     = LOW;
    KP_ROW2     = LOW;
    KP_ROW3     = LOW;
    KP_ROW4     = LOW;

    RBIF = 0;               // Clear the Keypad interrupt Flag
    RBIE = ENABLE;          // Re-enable Keypad interrupt
    return Key;
}