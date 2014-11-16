/*
 * File:   serial.c
 * Author: Shamnad
 *
 * Created on 20 October 2014, 01:00
 */

// include the header for serial library:
#include "serial.h"


/*******************************************************************************
* This file provides the functions for the Serial port(Hardware)
*******************************************************************************/

unsigned char read_buffer[BUF_SIZE];
int rx_buffer_save_pointer = 0;   // This is a circular buffer save counter.
int rx_buffer_read_pointer = 0;   // This is a circular buffer read counter.
int rx_buffer_available = 0; //The available bytes in the buffer. Countable backwards from rx_buffer_save_pointer
// Start the Serial port
void Serial_begin(unsigned long baud)
{
//    TXSTA: TRANSMIT STATUS AND CONTROL REGISTER
//    *********************************************
//    TX9: 9-bit Transmit Enable bit
//1 = Selects 9-bit transmission
//0 = Selects 8-bit transmission
    TX9 = 0;
//    TXEN: Transmit Enable bit
//1 = Transmit enabled
//0 = Transmit disabled
    TXEN = 1;
//    SYNC: EUSART Mode Select bit
//1 = Synchronous mode
//0 = Asynchronous mode
    SYNC = 0;
//BRGH: High Baud Rate Select bit
//Asynchronous mode:
//1 = High speed
//0 = Low speed
    BRGH = 0;

//RCSTA: RECEIVE STATUS AND CONTROL REGISTER
//    *********************************************
//    SPEN: Serial Port Enable bit
//1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
//0 = Serial port disabled (held in Reset)
    SPEN = 1;
//    RX9: 9-bit Receive Enable bit
//1 = Selects 9-bit reception
//0 = Selects 8-bit reception
    RX9 = 0;
//    CREN: Continuous Receive Enable bit
//Asynchronous mode:
//1 = Enables receiver
//0 = Disables receiver
    CREN = 1;

//    BAUDCTL: BAUD RATE CONTROL REGISTER
//    *********************************************
//SCKP: Synchronous Clock Polarity Select bit
//Asynchronous mode:
//1 = Transmit inverted data to the RB7/TX/CK pin
//0 = Transmit non-inverted data to the RB7/TX/CK pin
    SCKP = 0;
//    BRG16: 16-bit Baud Rate Generator bit
//1 = 16-bit Baud Rate Generator is used
//0 = 8-bit Baud Rate Generator is used
    BRG16 = 1;
//    ABDEN: Auto-Baud Detect Enable bit
//Asynchronous mode:
//1 = Auto-Baud Detect mode is enabled (clears when auto-baud is complete)
//0 = Auto-Baud Detect mode is disabled
    ABDEN = 0;

//    The divider value is depends on SYNC, BRGH and BRG16. That can be 64,16 or 4
    unsigned int divider = 16;
    unsigned int BaudVal = (_XTAL_FREQ/baud/divider)-1;
    SPBRGH = (BaudVal & 0xff00) >>  8;
    SPBRG = BaudVal & 0x00ff;

    //Enable interrupts
//    Clear Flags
    TXIF = 0;
    RCIF = 0;
//    Enable Receive interrupt
    PEIE = 1;
    TXIE = 0;
    RCIE = 1;
    GIE = 1;

}

// Reads incoming serial data. Returns the first byte of incoming serial data available.
// Supports byte only.
unsigned char Serial_read(void)
{
    if (rx_buffer_available)
    {
        if (rx_buffer_read_pointer == BUF_SIZE)
            rx_buffer_read_pointer = 0;
        rx_buffer_available--;
        return read_buffer[rx_buffer_read_pointer++];
    }
    else
        return 0;   // No data available
}

// Writes binary data to the serial port. Supports single byte only.
void Serial_write(unsigned char x)
{
        while (!TRMT);
        TXREG =  x;
}

//Prints data to the serial port. Supports Strings only.
void Serial_print(unsigned char *str)
{
     while(*str)
     {
        while (!TRMT);
        TXREG =  *str++;
     }
}
void Serial_ReadISR(void)
{
    if (rx_buffer_save_pointer == BUF_SIZE)
        rx_buffer_save_pointer = 0;
    read_buffer[rx_buffer_save_pointer++] = RCREG;
    rx_buffer_available++;
    RCIF = 0;
}
// Prints data to the serial port as human-readable ASCII text followed by a carriage
// return character (ASCII 13, or '\r') and a newline character (ASCII 10, or '\n').
// This command takes the same forms as Serial_print().
void Serial_println(unsigned char *str)
{
    Serial_print(str);
    while (!TRMT);
    TXREG =  CR;
    while (!TRMT);
    TXREG =  LF;
}


// Number of available data bytes
unsigned char Serial_available(void)
{
    return rx_buffer_available;
}



// Stop Serial port(Pins will be available for generic use)
void Serial_end(void);

// Read data from serial buffer until the target string of given length is found.
// The function returns true if target string is found, false if it times out.
bit Serial_find(unsigned char str)
{
    return 0;
}


// Reads data from the serial buffer until a target string of given length or
// terminator string is found. The function returns true if the target
// string is found, false if it times out.
bit Serial_findUntil(unsigned char str, unsigned char terminator)
{
    return 0;
}

//Waits for the transmission of outgoing serial data to complete.
void Serial_flush(void)
{
    rx_buffer_save_pointer = 0;   // This is a circular buffer save counter.
    rx_buffer_read_pointer = 0;   // This is a circular buffer read counter.
    rx_buffer_available = 0; //The available bytes in the buffer. Countable backwards from rx_buffer_save_pointer
}

// Reads characters from the serial port into a buffer. The function terminates
// if the determined length has been read, or it times out.
// Returns the number of characters placed in the buffer. A 0 means no valid data was found.
unsigned char Serial_readBytes(unsigned char buffer[], unsigned char length)
{
    return 0;
}

// Reads characters from the serial buffer into an array. The function terminates
// if the terminator character is detected, the determined length has been read, or it times out.
// Returns the number of characters placed in the buffer. A 0 means no valid data was found.
unsigned char Serial_readBytesUntil(unsigned char str, unsigned char buffer[], unsigned char length)
{
    return 0;
}

