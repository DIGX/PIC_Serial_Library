/*
 * File:   lcd.c
 * Author: Shamnad.T
 * Ver: 1.0
 * Created on Oct 8, 2014
 */

// include the header for LCD library:
#include "lcd.h"

/*******************************************************************************
* This file provides the functions for the HD44780 based
* LCD display in 4 bit interface
*******************************************************************************/

/*
  LCD Library for PIC16F887
================================================================================
 * Usages examples
 * ----------------------------------------------------------------------------
 * LCD_begin()                  - Initialise LCD module
 * LCD_display()                - Display ON
 * LCD_noDisplay()              - Display OFF
 * LCD_clear()                  - Display Clear
 * LCD_home()                   - Set cursor to Home position
 * LCD_setCursor(2,5)           - Set cursor to Line 2, character postion 5
 * LCD_print(1,10,"Hello")      - Display message "Hello" at Line 1, character postion 10
 * LCD_putchar('a')             - Print a character at current cursor postion
 * LCD_BCDprint(4,678)          - Print number 678 in 4 digit form(Output: 0678)
 * Set_LCD(0, 0x06)             - Send the command 0x06 to LCD(0=command, 1=data)
 *
 * Other ways to print a char
 * LCD_print(1,10,"a")          - Print as a string to specific location
 * Set_LCD(L_DATA,'a')          - Send the char to current location of LCD as a Data input
 *
 The LCD library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 The circuit:
 * LCD RS pin define as LCD_RS in lcd.h
 * LCD E pin define as LCD_E in lcd.h
 * LCD D4 pin define as LCD_4 in lcd.h
 * LCD D5 pin define as LCD_5 in lcd.h
 * LCD D6 pin define as LCD_6 in lcd.h
 * LCD D7 pin define as LCD_7 in lcd.h
 * LCD R/W pin to ground
 * 10K resistor: connect ends to +5V and ground, wiper to LCD VO pin(LCD pin 3)
 *
 * Connections should be defined in lcd.h along with direction controls
 * eg:-
 * #define LCD_RS_dir TRISB0
 * #define LCD_E_dir TRISB1
 * #define LCD_4_dir TRISB4
 * #define LCD_5_dir TRISB5
 * #define LCD_6_dir TRISB6
 * #define LCD_7_dir TRISB7
 */

/*******************************************************************************
* PRIVATE GLOBAL VARIABLES                                                     *
*******************************************************************************/



/*******************************************************************************
* PUBLIC FUNCTION: LCD_begin
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the LCD display.
*
*******************************************************************************/
void LCD_begin(void)
{
    LCD_RS_dir = 0;     // Set as Output
    LCD_E_dir = 0;

    LCD_4_dir = 0;
    LCD_5_dir = 0;
    LCD_6_dir = 0;
    LCD_7_dir = 0;
    
    LCD_RS = 0;         // RS  = 0
    LCD_E = 0;          // E  = 0

    LCD_4 = 0;          // Data bus = 0
    LCD_5 = 0;
    LCD_6 = 0;
    LCD_7 = 0;

    __delay_ms(100);           // Power on Delay for LCD
    Set_LCD_Pins8(0, 0x03);     // Send 0x30 as command to LCD
    Set_LCD_Pins8(0, 0x03);     // Functions set for 8 bit interfacing
    Set_LCD_Pins8(0, 0x03);     // Repeat 3 times
    Set_LCD_Pins8(0, 0x02);     // Change Functions set to 4 bit interfacing

    Set_LCD(L_CMD, FUNCTION_SET | DL_4 | TWO_LINE | NORMAL_FONT);   // Command entered in 4 bit mode from now on
    Set_LCD(L_CMD, DISPLAY_CONTROL | DISP_OFF);
    Set_LCD(L_CMD, CLEAR);
    Set_LCD(L_CMD, ENTRY_MODE_SET | INC_MODE | NO_SHIFT);
    Set_LCD(L_CMD, DISPLAY_CONTROL | DISP_ON | CURS_OFF);

}

/*******************************************************************************
* PRIVATE FUNCTION: LCD_print
*
* PARAMETERS:
* ~ line		- Line number
* ~ pos                 - Column number
* ~ *str		- Pointer to the message
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Print message at specified starting point.
*
*******************************************************************************/
void LCD_print (unsigned char line, unsigned char pos, unsigned char *str)
{
    // Send the command to jump to the defined position.
    LCD_setCursor(line,pos);

    // Print each character until end
    while(*str)
        Set_LCD(1, *str++);
}

/*******************************************************************************
* PRIVATE FUNCTION: Set_LCD
*
* PARAMETERS:
* ~ rs                  - 0 for command, 1 for data
* ~ datain		- Command/Data
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Set the output of the LCD RS pin and data bus.
*
*******************************************************************************/
void Set_LCD (unsigned char rs, unsigned char datain)
{
    Set_LCD_Pins8(rs, (datain>>4) & 0x0F);
    Set_LCD_Pins8(rs, datain & 0x0F);
}

/*******************************************************************************
* PRIVATE FUNCTION: Set_LCD_Pins8
*
* PARAMETERS:
* ~ rs                  - 0 for command, 1 for data
* ~ datain		- Command/Data(lower nibble only)
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Set the output of the LCD RS pin and data bus but, only the LOWER NIBBLE.
*
*******************************************************************************/
void Set_LCD_Pins8 (unsigned char rs, unsigned char datain)
{
    LCDPINS = datain;

    LCD_RS = rs;

    LCD_4 = LCDPINS_0;
    LCD_5 = LCDPINS_1;
    LCD_6 = LCDPINS_2;
    LCD_7 = LCDPINS_3;

    LCD_E = 1;
    __delay_ms (1);
    LCD_E = 0;
    __delay_ms (10);
}

/*******************************************************************************
* PUBLIC FUNCTION: LCD_clear
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Clear the LCD display and return the cursor to the home position.
*
*******************************************************************************/
void LCD_clear(void)
{
	// Send the command to clear the LCD display.
	Set_LCD(L_CMD, CLEAR);
}

/*******************************************************************************
* PUBLIC FUNCTION: LCD_home
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Return the cursor to the home position.
*
*******************************************************************************/
void LCD_home(void)
{
	// Send the command to return the cursor to the home position.
	Set_LCD(L_CMD, HOME);
}

/*******************************************************************************
* PUBLIC FUNCTION: LCD_display
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Set Display ON.
*
*******************************************************************************/
void LCD_display(void)
{
    Set_LCD(L_CMD, DISPLAY_CONTROL | DISP_ON);
}

/*******************************************************************************
* PUBLIC FUNCTION: LCD_noDisplay
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Set Display OFF.
*
*******************************************************************************/
void LCD_noDisplay(void)
{
    Set_LCD(L_CMD, DISPLAY_CONTROL | DISP_OFF);
}

/*******************************************************************************
* PUBLIC FUNCTION: lcd_goto
*
* PARAMETERS:
* ~ uc_position	- The position that we want to set the cursor at.
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Jump to the defined position of the LCD display.
*
*******************************************************************************/
void LCD_setCursor(unsigned char line, unsigned char pos)
{
	// Send the command to jump to the defined position.
    if (line == 4)
	Set_LCD(L_CMD, (SET_DDRAM_ADDRESS | FOURTH_ROW) + pos - 1);
    else if (line == 3)
	Set_LCD(L_CMD, (SET_DDRAM_ADDRESS | THIRD_ROW) + pos - 1);
    else if (line == 2)
	Set_LCD(L_CMD, (SET_DDRAM_ADDRESS | SECOND_ROW) + pos - 1);
    else
	Set_LCD(L_CMD, SET_DDRAM_ADDRESS + pos - 1);
}



/*******************************************************************************
* PUBLIC FUNCTION: LCD_putchar
*
* PARAMETERS:
* ~ c_data	- The character to display.
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Display a character on the LCD.
*
*******************************************************************************/
void LCD_putchar(char datain)
{
	// Send the data to display.
	Set_LCD(1, (unsigned char)datain);
}

/*******************************************************************************
* PUBLIC FUNCTION: LCD_BCDprint
*
* PARAMETERS:
* ~ required_digits, the_number
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* convert the value in ui_number to BCD(Binary Code Decimal) and display the
* digit according to uc_digit needed.
*
*******************************************************************************/
void LCD_BCDprint(unsigned char required_digits, unsigned int the_number)
{
    unsigned int ui_decimal[5] ={ 0 };
    //extract 5 single digit from ui_number
    ui_decimal[4] = the_number/10000;	// obtain the largest single digit, digit4
    ui_decimal[3] = the_number%10000;	// obtain the remainder
    ui_decimal[2] = ui_decimal[3]%1000;
    ui_decimal[3] = ui_decimal[3]/1000;			// obtain the 2nd largest single digit, digit3
    ui_decimal[1] = ui_decimal[2]%100;
    ui_decimal[2] = ui_decimal[2]/100;			// obtain the 3rd largest single digit, digit2
    ui_decimal[0] = ui_decimal[1]%10;			// obtain the smallest single digit, digit0
    ui_decimal[1] = ui_decimal[1]/10;			// obtain the 4th largest single digit, digit1

    if (required_digits > 5) required_digits = 5;			// limit to 5 digits only
    for( ; required_digits > 0; required_digits--)
    {
            LCD_putchar(ui_decimal[required_digits - 1] + 0x30);
    }
}

