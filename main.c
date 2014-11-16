/*
 * File:   main.c
 * Author: Admin
 *
 * Created on 12 October 2014, 01:49
 */

//	Include files
//==========================================================================
#include <htc.h>
#include "system.h"
#include "lcd.h"
#include "Keypad.h"
#include "serial.h"


//   Configuration setting
//==========================================================================

__CONFIG(   FOSC_INTRC_NOCLKOUT &   // Internal oscillator, No clock out
            WDTE_OFF &              // Disable Watchdog Timer.
            PWRTE_ON &              // Enable Power Up Timer.
            BOREN_OFF &             // Disable Brown Out Reset.
            MCLRE_OFF &             // MCLR function is disabled
            LVP_OFF);               // Disable Low Voltage Programming.

//	Function prototypes
//==========================================================================


//	Global variables
//==========================================================================
unsigned char Key = 0;
char inByte = 0;         // incoming serial byte(NB: In Arduino it is INT)


//	Interrupt Service Routines
//==========================================================================
void interrupt ISR(void)
{
    // Add this code in the ISR if Keypad_begin(WITH_ISR) is called
//    if (RBIF)
//    {
//        Key = Keypad_ISR();
//    }
    // Add this code in the ISR if Serial is called
    if (RCIF)
    {
        Serial_ReadISR();
    }

}
//	Main function
//==========================================================================
void main(void)
{
    // Internal Oscillator Configuration for initial run
    OSCCON = 0x01;
    // Specify Clock Source as INTERNAL/EXTERNAL  - Frequency will be set using _XTAL_FREQ
    Osc_Setup(INTERNAL);
    // System_setup Disables all Analog Pins by default. Configure it in Analog function call
    System_Setup();
    // Setup the LCD with number of columns and rows:
    LCD_begin();
    // Start serial port at 9600 baud(or bps)
    Serial_begin(9600);

//    Keypad_begin(WITHOUT_ISR); // Initialise keypad only if it is NOT multiplexed with LCD
    
    Serial_print("Hello world...  ");
    Serial_println("It's a Terminal!");
    Serial_println("Use the Keypad to see any key here.");
    Serial_println("You can also type something in the terminal,");
    Serial_println("Typed characters will be send back.");

    LCD_print(1, 1, "WWW.DIGXTECH.COM");    // LCD display (Please refer lcd.c for detail)
    LCD_print(2, 1, "Key pressed:    ");

    Set_LCD(L_CMD, DISPLAY_CONTROL | DISP_ON | CURS_ON | BLINK);
    LCD_setCursor(2,14);

    //loop forever
    while(1)
    {
        // Use the below line if you want to use Keypad multiplexed with LCD datalines
//        Key = Keypad_ALTwaitForKey();    // Waits until a key is pressed
        // Uncomment this instead of above function if you don't want to wait
        Key = Keypad_ALTgetKey();    // It gets the Key or return 0
        
        if(Key)                     // If Key is available,
        {
            Serial_write(Key);      // Send to Serial port
            LCD_setCursor(2,14);    // Set the Cursor location
            LCD_putchar(Key);       // Print Key on LCD
            Key = 0;                // Reset the Key value
        }
         // If we get a valid byte, send it back
        if (Serial_available() > 0) {
            // Get incoming byte
            inByte = Serial_read();
            // Write to serial
            Serial_write(inByte);
        }
    }
}