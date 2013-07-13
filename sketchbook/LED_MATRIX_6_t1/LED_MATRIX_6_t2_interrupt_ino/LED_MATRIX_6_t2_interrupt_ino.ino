int latchPin = 4;
int clockPin = 7;
int dataPin = 2;
float timeCount = 0;
byte cols = 0;
byte rows = 0;
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
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  
}

void loop() 
{
  //leds={0,0};
  //updateShiftRegister(leds);
  timeCount += 1;
if(timeCount < 1000) {
for (int i=0;i<8;i++) {
   
    updateShiftRegister(drawLittleHeart[i]);
    
  }
} else if (timeCount < 1200) {

} else if (timeCount < 2000) {
for (int i=0;i<8;i++) {
   
    updateShiftRegister(drawLittleHeart2[i]);
    
  }
} else if (timeCount < 2200) {
// do nothing
} else if (timeCount < 3000) {
for (int i=0;i<8;i++) {
   
    updateShiftRegister(drawLittleHeart3[i]);
    
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

void updateShiftRegister(int leds[2])
{
   digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds[1]);
    shiftOut(dataPin, clockPin, LSBFIRST, leds[0]);
   digitalWrite(latchPin, HIGH);
}

