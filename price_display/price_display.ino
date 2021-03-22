
#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object
int value = 0;
int newValue = 0;
const int MaxChars = 4;
char strValue[MaxChars+1];
int index = 0;

void setup() {
    Serial.begin(9600);
    //Serial.print("start\r\n");

    byte numDigits = 4;  
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0; 
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(10);

    sevseg.setNumber(3141, 3);
}

void serialEvent()
{
   while(Serial.available()) 
   {
      char ch = Serial.read();
      Serial.write(ch);
      if(index < MaxChars && isDigit(ch)) { 
            strValue[index++] = ch; 
      } else { 
            strValue[index] = 0; 
            newValue = atoi(strValue); 
	    sevseg.setNumber(newValue,0);
            index = 0;
            value = newValue;
      }  
   }
}

void loop() {

    sevseg.refreshDisplay(); // Must run repeatedly
}
