
#include "SevSeg.h"

#include "LedControl.h"

LedControl lc=LedControl(14,16,15,4);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=1000;  // Delay between Frames

// Put values in arrays
byte stonks[] =
{
   B00000000,  
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte stonks5[] =
{
   B00011000,  
   B00100100,
   B01011010,
   B00100100,
   B01011010,
   B00100100,
   B01011010,
   B00100100
};

byte stonks4[] =
{
   B00011000,  
   B00100100,
   B01011010,
   B00100100,
   B01011010,
   B00100100,
   B01000010,
   B00000000
};

byte stonks3[] =
{
   B00000000,  
   B00011000,
   B00100100,
   B01000010,
   B00011000,
   B00100100,
   B01000010,
   B00000000
};

byte stonks2[] =
{
   B00000000,  
   B00000000,
   B00011000,
   B00100100,
   B01000010,
   B00000000,
   B00000000,
   B00000000
};
byte stonks1[] =
{
   B00000000,  
   B00011000,
   B00100100,
   B01000010,
   B00000000,
   B01111110,
   B00000000,
   B00000000
};

byte stonks0[] =
{
   B00000000,  
   B00000000,
   B00000000,
   B00000000,
   B01111110,
   B00000000,
   B00000000,
   B00000000
};

byte stonks_1[] =
{
   B00000000,  
   B00000000,
   B01111110,
   B00000000,
   B01000010,
   B00100100,
   B00011000,
   B00000000
};

byte stonks_2[] =
{
   B00000000,  
   B00000000,
   B00000000,
   B01000010,
   B00100100,
   B00011000,
   B00000000,
   B00000000
};

byte stonks_3[] =
{
   B00000000,  
   B01000010,
   B00100100,
   B00011000,
   B01000010,
   B00100100,
   B00011000,
   B00000000
};

byte stonks_4[] =
{
   B00000000,  
   B01000010,
   B00100100,
   B01011010,
   B00100100,
   B01011010,
   B00100100,
   B00011000
};

byte stonks_5[] =
{
   B00100100,  
   B01011010,
   B00100100,
   B01011010,
   B00100100,
   B01011010,
   B00100100,
   B00011000
};

byte* stonkss[11] = {stonks_5, stonks_4, stonks_3, stonks_2, stonks_1, stonks0, stonks1, stonks2, stonks3, stonks4, stonks5};

SevSeg sevseg; //Initiate a seven segment controller object
int value = 0;
int newValue = 0;
const int MaxChars = 6;
char strValue[MaxChars+1];
int index = 0;
bool readStonks = 0;
int stonkDegree = 6;

//  Take values in Arrays and Display them
void setStonk(int stonk)
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,stonkss[stonk][i]);
  }
}

void setup() {
    lc.shutdown(0,false);
    lc.setIntensity(0,1);
    lc.clearDisplay(0);
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
    //for (int i = 0; i < 11; i++){
        //setStonk(i);
	//delay(delayTime);
    //}
    sevseg.setNumber(3141, 3);
}



void serialEvent()
{
   while(Serial.available()) 
   {
      char ch = Serial.read();
      Serial.write(ch);
      if(readStonks){
	    stonkDegree = ch-48;
            readStonks = 0;
      } else if(ch==':'){
            readStonks = 1;
      } else if(index < MaxChars && isDigit(ch)) { 
            strValue[index++] = ch; 
      } else { 
            strValue[index] = 0; 
            newValue = atoi(strValue); 
	    sevseg.setNumber(newValue,0);
            setStonk(stonkDegree);
	    index = 0;
            value = newValue;
      }  
   }
}

void loop() {
    sevseg.refreshDisplay(); // Must run repeatedly
}
