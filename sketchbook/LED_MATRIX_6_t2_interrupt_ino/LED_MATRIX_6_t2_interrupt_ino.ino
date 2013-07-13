/*
     Code voor 2 matrices
*/

int dataPin1 = 27;
int latchPin1 = 25;
int clockPin1 = 23;
int dataPin2 = 32;
int latchPin2 = 30;
int clockPin2 = 28;
int dataPin3 = 38;
int latchPin3 = 36;
int clockPin3 = 34;


float timeCount = 0;
int leds[2];
int potPin = 0;
unsigned long Timer;
int val;

int drawLittleHeart[8][2]={
  {66,127},
  {165,191},
  {153,223},
  {129,239},
  {66,247},
  {36,251},
  {24,253},
  {24,254}};

int drawLittleHeart2[8][2]={
  {0,127},
  {165,191},
  {153,223},
  {129,239},
  {66,247},
  {36,251},
  {24,253},
  {24,254}};
int drawLittleHeart3[8][2]={
  {0,127},
  {0,191},
  {153,223},
  {129,239},
  {66,247},
  {36,251},
  {24,253},
  {24,254}};   

void setup() 
{
  pinMode(latchPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);  
  pinMode(clockPin1, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);  
  pinMode(clockPin2, OUTPUT);
  pinMode(latchPin3, OUTPUT);
  pinMode(dataPin3, OUTPUT);  
  pinMode(clockPin3, OUTPUT);
  Serial.begin(9600);
  
}

void loop() 
{
  timeCount += 1;
  if(timeCount < 1000) {
    for (int i=0;i<8;i++) {
   
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      updateShiftRegister3(drawLittleHeart[i]);
    
  }
  } else if (timeCount < 1200) {

  } else if (timeCount < 2000) {
    for (int i=0;i<8;i++) {
   
      updateShiftRegister1(drawLittleHeart2[i]);
      updateShiftRegister2(drawLittleHeart2[i]);
      updateShiftRegister3(drawLittleHeart2[i]);
    
  }
  } else if (timeCount < 2200) {
  // do nothing
  } else if (timeCount < 3000) {
    for (int i=0;i<8;i++) {
   
      updateShiftRegister1(drawLittleHeart3[i]);
      updateShiftRegister2(drawLittleHeart3[i]);
      updateShiftRegister3(drawLittleHeart3[i]);     
    
    }
  } else if (timeCount < 3200) {

  } else {
  // back to the start
  timeCount = 0;
}
  
if(millis() - Timer > 5 ) {  
  Timer = millis();
  val = analogRead(0);
  Serial.println(val);
  
}
}

void updateShiftRegister1(int leds[2])
{
   digitalWrite(latchPin1, LOW);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[1]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[0]);
   digitalWrite(latchPin1, HIGH);
}
void updateShiftRegister2(int leds[2])
{
   digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, leds[1]);
    shiftOut(dataPin2, clockPin2, LSBFIRST, leds[0]);
   digitalWrite(latchPin2, HIGH);
}
void updateShiftRegister3(int leds[2])
{
   digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, leds[1]);
    shiftOut(dataPin3, clockPin3, LSBFIRST, leds[0]);
   digitalWrite(latchPin3, HIGH);
}
