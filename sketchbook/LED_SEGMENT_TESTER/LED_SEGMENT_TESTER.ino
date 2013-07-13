/*
     Code voor 2 matrices
*/

//SCORE
int dataPin1 = 26;
int latchPin1 = 24;
int clockPin1 = 22;
//HIGHSCORE
int dataPin2 = 33;
int latchPin2 = 31;
int clockPin2 = 29;
int bufferSERIAL[5];

float timeCount = 0;
int leds[2];
int potPin = 3;
unsigned long Timer;
int val;

int nul1=119;
int nul2=231;
int nul3=119;
int een1=20;
int een2=33;
int een3=33;
int twee1=179;
int twee2=203;
int twee3=213;
int drie1=182;
int drie2=107;
int drie3=241;
int vier1=212;
int vier2=45;
int vier3=163;
int vijf1=230;
int vijf2=110;
int vijf3=242;
int zes1=231;
int zes2=238;
int zes3=246;
int zeven1=52;
int zeven2=35;
int zeven3=97;
int acht1=247;
int acht2=239;
int acht3=247;
int negen1=246;
int negen2=111;
int negen3=243;

int nul=238;
int een=40;
int twee=205;
int drie=103;
int vier=43;
int vijf=103;
int zes=231;
int zeven=44;
int acht=239;
int negen=111;
  
int nult[3]={247,239,247};  
int eent[3]={76,76,76};
int tweet[3]={205,205,205};
int driet[3]={128,4,16};

void setup() 
{
  pinMode(latchPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);  
  pinMode(clockPin1, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);  
  pinMode(clockPin2, OUTPUT);
  
  Serial.begin(9600);
  updateShiftRegister1(nult);
  
}

void loop() 
{
updateShiftRegister2(nult);
delay(1000);
updateShiftRegister1(tweet);
delay(1000);

int val=analogRead(potPin);
Serial.println(val);
delay(50);
    
   //}   

  //} 

}


void updateShiftRegister1(int leds[3])
{
   digitalWrite(latchPin1, LOW);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[2]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[1]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[0]);
   digitalWrite(latchPin1, HIGH);
}
void updateShiftRegister2(int leds[3])
{
   digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, leds[2]);
    shiftOut(dataPin2, clockPin2, LSBFIRST, leds[1]);
    shiftOut(dataPin2, clockPin2, LSBFIRST, leds[0]);
   digitalWrite(latchPin2, HIGH);
}
