
#include "mark-iv-flip-dot-display-sign-14x28-controller/mark-iv-flip-dot-display-sign-14x28-controller.h"
//#include <avr/pgmspace.h>


byte FONTE[][5] = {
//prog_uchar FONTE[][5] PROGMEM = {
  {0,0,0,0,0},
  {0,56,125,56,0},// !
  {80,96,0,80,96},//"
  {20,127,20,127,20},//#
  {18,42,127,42,36},//$
  {98,100,8,19,35},//%
  {54,73,85,34,5},//&
  {0,80,96,0,0},//'(7)
  {0,28,34,65,0},//(
  {0,65,34,28,0},//)
  {20,8,62,8,20},//*
  {8,8,62,8,8},//+
  {0,5,6,0,0},//,(12)
  {8,8,8,8,8},//-
  {0,3,3,0,0},//.(14)
  {2,4,8,16,32},// /
  {62,69,73,81,62},//0
  {17,33,127,1,1},//1
  {33,67,69,73,49},//2
  {34,65,73,73,54},//3
  {12,20,36,127,4},//4
  {114,81,81,81,78},//5
  {62,73,73,73,38},//6
  {64,71,72,80,96},//7
  {54,73,73,73,54},//8
  {50,73,73,73,62},//9
  {0,54,54,0,0},//:(26)
  {0,53,54,0,0},//;(27)
  {8,20,34,65,0},//<
  {20,20,20,20,20},//=
  {0,65,34,20,8},//>
  {32,64,69,72,48},//?
  {62,73,87,85,62},//@
  {31, 36, 68, 36, 31},    //A
  {127, 73, 73, 73, 54},   //B
  {62, 65, 65, 65, 34},    //C
  {127, 65, 65, 34, 28},   //D
  {127, 73, 73, 65, 65},   //E
  {127, 72, 72, 72, 64},   //F
  {62, 65, 65, 69, 38},    //G
  {127, 8, 8, 8, 127},     //H
  {0, 65, 127, 65, 0},     //I
  {2, 1, 1, 1, 126},       //J
  {127, 8, 20, 34, 65},    //K
  {127, 1, 1, 1, 1},       //L
  {127, 32, 16, 32, 127},  //M
  {127, 32, 16, 8, 127},   //N
  {62, 65, 65, 65, 62},    //O
  {127, 72, 72, 72, 48},   //P
  {62, 65, 69, 66, 61},    //Q
  {127, 72, 76, 74, 49},	//R
  {50, 73, 73, 73, 38},		//S
  {64, 64, 127, 64, 64},	//T
  {126, 1, 1, 1, 126},		//U
  {124, 2, 1, 2, 124},		//V
  {126, 1, 6, 1, 126},		//W
  {99, 20, 8, 20, 99},		//X
  {96, 16, 15, 16, 96},		//Y
  {67, 69, 73, 81, 97},		//Z
  {0,127,65,65,0},//[
  {32,16,8,4,2},//
  {0,65,65,127,0},
  {16,32,64,32,16},//^
  {1,1,1,1,1},//_
  {0,64,32,16,0},//`
  {2,21,21,14,1},//a
  {64,126,9,17,14},//b
  {14,17,17,17,10},//c
  {14,17,74,127,1},//d
  {14,21,21,21,9},//e
  {1,9,63,72,32},//f
  {9,21,21,21,30},//g
  {127,8,8,8,7},//h
  {0,0,46,1,1},//i
  {2,1,1,1,94},//j
  {1,127,4,10,17},//k
  {0,65,127,1,0},//l
  {31,16,14,16,31},//m
  {31,8,16,16,15},//n
  {14,17,17,17,14},//o
  {127,20,20,20,8},//p
  {8,20,20,31,1},//q
  {31,8,16,16,8},//r
  {9,21,21,21,18},//s
  {16,16,126,17,18},//t
  {30,1,1,30,1},//u
  {28,2,1,2,28},//v
  {30,1,6,1,30},//w
  {17,10,4,10,17},//x
  {16,9,6,8,16},//y
  {17,19,21,25,17},//z
  {8,54,65,65,0},//{
  {0,0,127,0,0},//|(92)
  {0,65,65,54,8},//}
  {32,64,32,16,32},//~ 
};


//DATA DS (pin 14) to Ardunio DigitalPin 11 (blue wire)
//CLOCK SH_CP (pin 11) to to Ardunio DigitalPin 12 (yellow wire)
//LATCH ST_CP (pin 12) to Ardunio DigitalPin 8 (green wire) 
//DotDisplay(int dataPin, int clockPin, int latchPin, int enableSubPanel1Pin, int enableSubPanel2Pin, int fontWidth, int fontHeight, prog_uchar fonteParam[][5]){
DotDisplay myDotDisplay(3,2,4,6,5,5,7,FONTE);


int sentencesSize = 15;
char sentences[][20] = {
"Antonio  Carioca",
"Te sinto mais bela",
"But I    like it",
"Maricota!!!!!",
"Hey, ho, let's go",
"Come as  you are",
"Don't    Panic",
"Keep calmCarry on",
"Time's onmy side",
"AdventureTime!",
"Home,    Home again",
"Brasilia 17 horas",
"Does any body know",
"Gone to  the Beach",
"Beer     time"
};
int sentPos;


void setup() {
  Serial.begin(9600);
  //HardwareSerial* hwPrint;
  //hwPrint = &Serial; 
  //myDotDisplay.setSerial(hwPrint);
  //int inPin = 7;   // choose the input pin (for a pushbutton)
  pinMode(7, INPUT_PULLUP);    // declare pushbutton as input
  sentPos = 0;
}

void loop() {
  int val = digitalRead(7);  // read input value
  //Serial.println(val);
  if (val == LOW) {
    for(int column = 0; column <28*2; column++){
      for(int row = 0; row <14; row++){
        myDotDisplay.setDot(column,row,0);
      }
    }
    int modPos = sentPos % sentencesSize;
    myDotDisplay.updateDisplay(sentences[modPos]);
    sentPos = sentPos + 1;
  }
}




