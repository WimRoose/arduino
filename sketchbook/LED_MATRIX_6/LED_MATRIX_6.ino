int SER_Pin = 2;   //pin 14 on the 75HC595
int RCLK_Pin = 4;  //pin 12 on the 75HC595
int SRCLK_Pin = 7; //pin 11 on the 75HC595
/*
Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
*/

int latchPin = 4;
int clockPin = 7;
int dataPin = 2;

byte cols = 0;
byte rows = 0;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  cols = 0;
  rows = 0;
  //updateShiftRegister();
  digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, cols);
   shiftOut(dataPin, clockPin, LSBFIRST, rows);
   digitalWrite(latchPin, HIGH);
  delay(500);
  cols = 129;
  rows = 124;
    //updateShiftRegister();
    digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, rows);
   shiftOut(dataPin, clockPin, LSBFIRST, cols);
   digitalWrite(latchPin, HIGH);
    delay(500);
  //for (int i = 0; i < 8; i++)
  //{
   // bitSet(leds, i);
   // leds=256;
   // updateShiftRegister();
   // delay(500);
  //}
}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
 //  shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
