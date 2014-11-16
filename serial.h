
/*
 * File:   serial.h
 * Author: Shamnad
 *
 * Created on 20 October 2014, 00:07
 */

#ifndef SERIAL_H
#define	SERIAL_H

#include "system.h"

extern char temp10;
// Pin defines for Keypad
//connect to the row pinouts of the keypad
#define KP_ROW1			RB0

/*******************************************************************************
* PRIVATE CONSTANTS                                                            *
*******************************************************************************/
//Set the time-out for serial data read in seconds
#define TIMEOUT         10

//Defined size for incoming buffer
#define BUF_SIZE        64


/*******************************************************************************
* FUNCTION PROTOTYPES                                                          *
*******************************************************************************/
// ISR function to call for Serial Receive Interrupt
void Serial_ReadISR(void);

// Number of available data bytes
unsigned char Serial_available(void);

// Start the Serial port
void Serial_begin(unsigned long speed);

// Stop Serial port(Pins will be available for generic use)
void Serial_end(void);

// Read data from serial buffer until the target string of given length is found.
// The function returns true if target string is found, false if it times out.
bit Serial_find(unsigned char str);


// Reads data from the serial buffer until a target string of given length or
// terminator string is found. The function returns true if the target
// string is found, false if it times out.
bit Serial_findUntil(unsigned char str, unsigned char terminator);

//Waits for the transmission of outgoing serial data to complete.
void Serial_flush(void);

//Prints data to the serial port. Supports Strings only.
void Serial_print(unsigned char *str);

// Prints data to the serial port as human-readable ASCII text followed by a carriage
// return character (ASCII 13, or '\r') and a newline character (ASCII 10, or '\n').
// This command takes the same forms as Serial_print().
void Serial_println(unsigned char *str);

// Reads incoming serial data. Returns the first byte of incoming serial data available.
// Supports byte only.
unsigned char Serial_read(void);

// Reads characters from the serial port into a buffer. The function terminates
// if the determined length has been read, or it times out.
// Returns the number of characters placed in the buffer. A 0 means no valid data was found.
unsigned char Serial_readBytes(unsigned char buffer[], unsigned char length);

// Reads characters from the serial buffer into an array. The function terminates
// if the terminator character is detected, the determined length has been read, or it times out.
// Returns the number of characters placed in the buffer. A 0 means no valid data was found.
unsigned char Serial_readBytesUntil(unsigned char str, unsigned char buffer[], unsigned char length);

// Writes binary data to the serial port. Supports single byte only.
void Serial_write(unsigned char str);



#endif	/* SERIAL_H */