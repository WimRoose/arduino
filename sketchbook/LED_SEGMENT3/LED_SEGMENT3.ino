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
int dataPin3 = 38;
int latchPin3 = 36;
int clockPin3 = 34;
int bufferSERIAL[5];

float timeCount = 0;
int leds[2];
int potPin = 3;
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


  
int nul[3]={0,0,0};  
int een[3]={246,45,243};
int twee[3]={255,255,255};
int drie[3]={128,4,16};

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
  updateShiftRegister(nul);
  
}

void loop() 
{
  //Serial.println("waiting....");
  delay(50);
//updateShiftRegister(nul);
//delay(1000);
//updateShiftRegister(een);
//delay(1000);
drawMatrices();
//if(millis() - Timer > 5 ) {  
  //Timer = millis();
  //val = analogRead(potPin);
  //Serial.println(val);
  int i=0;
        // if data is available on hardwareserial port ==> data is comming from PC or notebook
  if (Serial.available())  {
    while(Serial.available())          // reading data into char array 
    {
      
        bufferSERIAL[i]=Serial.read();     // writing data into array
        if (bufferSERIAL[i] == 13) break;
        i++;
        
    }
    //}
  
   //if (bufferSERIAL[0] == '1'){
    //Serial.println("yes");
    //Serial.println(bufferSERIAL[0]);
    //Serial.println(bufferSERIAL[1]);
    //Serial.println(bufferSERIAL[2]);
    int leds[3];
    leds[2]=bufferSERIAL[0];
    leds[1]=bufferSERIAL[1];
    leds[0]=bufferSERIAL[2];
    Serial.println();
    Serial.write(bufferSERIAL[0]);
    Serial.print("-");
    Serial.write(bufferSERIAL[1]);
    Serial.print("-");
    Serial.write(bufferSERIAL[2]);
    Serial.println();
    Serial.write(leds[0]);
    Serial.print("-");
    Serial.write(leds[1]);
    Serial.print("-");
    Serial.write(leds[2]);
    Serial.println();
    for (int i=0;i<6;i++)  {
        bufferSERIAL[i]=NULL;     // writing data into array
    }
    
    updateLEDDIGITS(leds);
    
   }
   //}   

  //} 
} 





void updateShiftRegister(int leds[3])
{
   digitalWrite(latchPin1, LOW);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[2]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[1]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[0]);
   digitalWrite(latchPin1, HIGH);
}
