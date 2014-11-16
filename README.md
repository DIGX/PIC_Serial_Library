PIC Serial Library
==============

This library is made using 'Arduino-like' functions to reduce the obstacles of converting PIC source code to Arduino and in reverse.

**Function usage Examples**
```c
	Serial_begin(9600); // Start the Serial port
	unsigned char inByte =  Serial_read(); // Reads an incoming character byte
	Serial_write('A'); // Write a char to Serial port
	Serial_print("Hello world"); // Print a string to Serial port
	Serial_println("This is a line"); // Same as Serial_print with a new line added
	unsigned char inCount = Serial_available(); // Returns available bytes in buffer
```