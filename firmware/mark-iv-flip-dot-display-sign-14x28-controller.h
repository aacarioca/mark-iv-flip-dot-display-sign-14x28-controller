/*
  DisplayController.h - Library for Controlling Max Luminator FlipDot display sign.
  Created by Antonio Carioca, July 4, 2012.
*/

#ifndef mark-iv-flip-dot-display-sign-14x28-controller_h
#define mark-iv-flip-dot-display-sign-14x28-controller_h

//#include "Arduino.h" 
#include <avr/pgmspace.h>

class DotDisplay{
public:
	DotDisplay(int dataPin, int clockPin, int latchPin, int _enableSubPanel1Pin, int _enableSubPanel2Pin, int fontWidth, int fontHeight, prog_uchar fonteParam[][5]);//uses progmem
	//DotDisplay(int dataPin, int clockPin, int latchPin, byte fonteParam[][5]);//uses regular memory
	void setSerial(HardwareSerial* hwPrint);
	byte generateColumnCode (byte col);
	void updateDisplay(char textMessage[]);
	void setDot(byte col, byte row, bool on);
private:
	HardwareSerial* printer;
	int _dataPin;
	int _clockPin;
	int _latchPin;
        int _enableSubPanel1Pin;
        int _enableSubPanel2Pin;
        int _fontWidth;
        int _fontHeight;
        int _maxMessageLength;
        int _maxRowLength;
        int _maxNumRows;
	byte alphabet[][5];
	//byte (*_fonteParam)[5];//regular memory
	prog_uchar (*_fonteParam)[5];//progmem
};

#endif
