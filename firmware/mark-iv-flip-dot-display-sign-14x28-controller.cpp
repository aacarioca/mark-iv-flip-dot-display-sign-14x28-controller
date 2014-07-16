/*
DisplayController.h - Library for Controlling a 14x28 bits FlipDot display sign using two FP2800A.
Created by Antonio Carioca, March 3, 2014.
*/

//#include "Arduino.h"

#include <avr/pgmspace.h>
#include "mark-iv-flip-dot-display-sign-14x28-controller.h"

/* CONSTANTS */
//const int DISPLAY_SIZE = 4;
const int DISPLAY_PIXEL_WIDTH = 28;
const int DISPLAY_PIXEL_HEIGHT = 14;
const int DISPLAY_SUBPANEL_QTY = 2;

//=== F O N T ===
// Font courtesy of aspro648
// coden taken from
// http://www.instructables.com/files/orig/FQC/A1CY/H5EW79JK/FQCA1CYH5EW79JK.txt
// The @ will display as space character.
// NOTE: MOVING ALL THE ARRAY BELOW TO PROGMEM


DotDisplay::DotDisplay(int dataPin, int clockPin, int latchPin, int enableSubPanel1Pin, int enableSubPanel2Pin, int fontWidth, int fontHeight, prog_uchar fonteParam[][5]){
	//DotDisplay::DotDisplay(int dataPin, int clockPin, int latchPin, byte fonteParam[][5]){

	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(enableSubPanel1Pin, OUTPUT);
	pinMode(enableSubPanel2Pin, OUTPUT);
	//disable FP2800A's
	digitalWrite(enableSubPanel1Pin, LOW);
	digitalWrite(enableSubPanel2Pin, LOW);

	_dataPin = dataPin;
	_clockPin = clockPin;
	_latchPin = latchPin;
	_enableSubPanel1Pin = enableSubPanel1Pin;
	_enableSubPanel2Pin = enableSubPanel2Pin;
	_fontWidth = fontWidth;
	_fontHeight = fontHeight;
	_fonteParam = fonteParam; 
	
        _maxNumRows = floor((DISPLAY_PIXEL_HEIGHT+1)/(_fontHeight));
        _maxRowLength = floor((DISPLAY_PIXEL_WIDTH * DISPLAY_SUBPANEL_QTY+1) / (_fontWidth+1));
        _maxMessageLength = _maxRowLength * _maxNumRows;

}

void DotDisplay::setSerial(HardwareSerial* hwPrint){
	printer = hwPrint; //operate on the address of print
	if(printer) {
		printer->begin(9600);
	}
}


void DotDisplay::setDot(byte col, byte row, bool on){

	
        //accidentally reversed two data pins, so reversing back on the code here
        //on = !on;
  
        //2 pins - Data
	//5 pins - Column
	//4 pins - Rows

	//4 pins - Enable FP2800A (4 subpanels)
	byte subPanel = 1; 
	//disable FP2800A's
	digitalWrite(_enableSubPanel1Pin, LOW);
	digitalWrite(_enableSubPanel2Pin, LOW);

	//enables next sunpanel
	if(col>=DISPLAY_PIXEL_WIDTH){
		subPanel =  floor(col / DISPLAY_PIXEL_WIDTH)+1;
		col=col-DISPLAY_PIXEL_WIDTH;
	}

        if(printer) {
          printer->print("col: ");
	  printer->print(col);
	  printer->print(", ");
	  printer->print("subPanel: ");
	  printer->println(subPanel);
	}

	// IGNOREx4 + ROWx4 + IGNOREx1 + COLUMNx5 + DATAx2
	byte dataPins = on?1:2;
	byte colFirstThreeDigits = (col % 7)+1;
	byte colLastTwoDigits = floor(col/7);
	byte colByte = colFirstThreeDigits | (colLastTwoDigits << 3);
	byte rowFirstThreeDigits = (row % 7)+1;
        byte rowLastDigit = row<7;
	byte rowByte = rowFirstThreeDigits | (rowLastDigit << 3);
	byte firstbyte = (dataPins) | (colByte << 2);
	byte secondbyte = rowByte;
	
	digitalWrite(_latchPin, LOW); 
	shiftOut(_dataPin, _clockPin, LSBFIRST, firstbyte); 
	shiftOut(_dataPin, _clockPin, LSBFIRST, secondbyte);  
	digitalWrite(_latchPin, HIGH);
	//delay(1);
	
	//pulse the FP2800A's enable pins
	if(subPanel == 1){
		digitalWrite(_enableSubPanel1Pin, HIGH); 
		delay(1);
		digitalWrite(_enableSubPanel1Pin, LOW);
	} else if (subPanel == 2) {
		digitalWrite(_enableSubPanel2Pin, HIGH); 
		delay(1);
		digitalWrite(_enableSubPanel2Pin, LOW);
	}
}

//void DotDisplay::updateDisplay(char *textMessage){
void DotDisplay::updateDisplay(char textMessage[]){
	int currentColumn = 0; 
        int currentRow = 0; 
	
	//goes through all characters
	for (int ch = 0; ch < (_maxMessageLength);ch++){  
		//get a character from the message
		int alphabetIndex = textMessage[ch] - ' '; //Subtract '@' so we get a number
		
		//Serial.println(alphabetIndex);
		if ((alphabetIndex < 0) or (ch >=strlen(textMessage))) alphabetIndex=0; 
		
		//push it to the next row if necessary
                if((currentColumn + _fontWidth) > (DISPLAY_PIXEL_WIDTH * DISPLAY_SUBPANEL_QTY)){
                  currentColumn=0;
                  currentRow=currentRow+_fontHeight;
                }


                //set all the bits in the next _fontWidth columns on the display
		for(byte col = currentColumn; col<(currentColumn+_fontWidth); col++){
			
			byte calculatedColumn = (col)%(_fontWidth+1);
			//for(byte row = 0; row < _fontHeight; row++)
                        int characterRow = 0;
                        for(byte row = currentRow; row < (currentRow + _fontHeight); row++){
				bool isOn = bitRead(pgm_read_byte(&(_fonteParam[alphabetIndex][calculatedColumn])),6-characterRow);//pgm_read_byte(&(mainPatterns[currentPattern][0]));
				setDot(col, row, isOn);
				if(printer) {
					//printer->print(isOn);
				}
                                characterRow++;
			}
			if(printer) {
				//printer->println("");
			}
		}
		if(printer) {
			//printer->println("*******");
		}
		currentColumn = currentColumn+(_fontWidth+1);
	        }
}
