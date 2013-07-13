/*
     Code voor 2 matrices
*/

int dataPin1 = 26;
int latchPin1 = 24;
int clockPin1 = 22;
int dataPin2 = 32;
int latchPin2 = 30;
int clockPin2 = 28;
int dataPin3 = 38;
int latchPin3 = 36;
int clockPin3 = 34;
char bufferSERIAL[5];

float timeCount = 0;
int leds[2];
int potPin = 0;
unsigned long Timer;
int LEVEL=1;
int SCORE=0;
int HSCORE=0;
boolean LEVELCHANGED=false;
boolean SCORECHANGED=false;


int val;

int nul[3]={0,0,0};
int een[3]={4,0,0};
int twee[3]={255,0,0};

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
  updateShiftRegister(een);
  
}

void loop() 
{
if (LEVELCHANGED == true) {
   if (LEVEL == 1) {updateShiftRegister(een);}
   if (LEVEL == 2) {updateShiftRegister(twee);}
   LEVELCHANGED = false;  
}
//delay(1000);
//updateShiftRegister(een);
//delay(1000);
//updateShiftRegister(twee);
//delay(1000);
if(millis() - Timer > 5 ) {  
  Timer = millis();
  //val = analogRead(0);
  //Serial.println(val);
  if (Serial.available())     {      // if data is available on hardwareserial port ==> data is comming from PC or notebook

    while(Serial.available())          // reading data into char array 
    {
      for (int i=0;i<5;i++)  {
        bufferSERIAL[i]=Serial.read();     // writing data into array
      }
    }
  if (bufferSERIAL[0] == '1') {
    LEVEL=1;
    LEVELCHANGED = true;
  }
  if (bufferSERIAL[0] == '2') {
    LEVEL=2;
    LEVELCHANGED = true;
  }
  if (bufferSERIAL[0] == '3') {
    LEVEL=3;
    LEVELCHANGED = true;
  }
  //if ((int)bufferSERIAL[0] != LEVEL){
  //  LEVEL=(int)bufferSERIAL[0];
  //  LEVELCHANGED = true;
  //}
  //  Serial.println(LEVEL);
  //  Serial.println(bufferSERIAL);
    
  for (int i=0;i<5;i++)  {
        bufferSERIAL[i]= NULL;     // writing data into array
      } 
  } 
  
      

}
}
void updateShiftRegister(int e[3])
{
   digitalWrite(latchPin1, LOW);
    shiftOut(dataPin1, clockPin1, LSBFIRST, e[2]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, e[1]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, e[0]);
   digitalWrite(latchPin1, HIGH);
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
