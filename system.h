/*
 * File:   system.h
 * Author: Shamnad.T
 * Ver: 1.0
 * Created on Oct 8, 2014
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include <htc.h>

#define _XTAL_FREQ 8000000

// Specific definitions for our custom framework
#define ON                  1
#define OFF                 0
#define on                  1
#define off                 0
#define HIGH                1
#define LOW                 0
#define high                1
#define low                 0
#define IN                  1
#define OUT                 0
#define in                  1
#define out                 0
#define INPUT               1
#define OUTPUT              0
#define input               1
#define output              0
#define INTERNAL            1
#define EXTERNAL            0
#define internal            1
#define external            0
#define ENABLE              1
#define DISABLE             0
#define enable              1
#define disable             0
#define TRUE                1
#define FALSE               0
#define true                1
#define false               0
#define PULLUP_ENABLE       nRBPU = 0
#define PULLUP_DISABLE      nRBPU = 1
#define CR          13
#define LF          10
#define SERIAL_BUFFER_SIZE          1

// Function prototypes
void Osc_Setup (unsigned char); // INTERNAL/EXTERNAL Oscillator
void System_Setup (void);

#endif	/* SYSTEM_H */

