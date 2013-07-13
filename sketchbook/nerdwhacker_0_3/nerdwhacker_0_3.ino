/*
     Code voor 2 matrices
*/
//LEDMATRIX1
int dataPin1 = 27;
int latchPin1 = 25;
int clockPin1 = 23;
int dataPin2 = 32;
int latchPin2 = 30;
int clockPin2 = 28;
int dataPin3 = 38;
int latchPin3 = 36;
int clockPin3 = 34;
//SCORE LED1
int dataPin4 = 26;
int latchPin4 = 24;
int clockPin4 = 22;
//HIGHSCORE LED2
int dataPin5 = 33;
int latchPin5 = 31;
int clockPin5 = 29;
//LEDMATRIX2
int dataPin6 = 53;
int latchPin6 = 51;
int clockPin6 = 49;
int dataPin7 = 47;
int latchPin7 = 45;
int clockPin7 = 43;
int dataPin8 = 41;
int latchPin8 = 39;
int clockPin8 = 37;

//PIEZO
int piezo1=0;
int piezo2=1;
int piezo3=2;
int piezo4=3;
int piezo5=4;
int piezo6=5;
int piezo7=6;
int piezo8=7;
int piezo9=8;
int piezo10=9;
int piezo11=10;
int piezo12=11;
int piezos[12]={piezo1,piezo2,piezo3,piezo4,piezo5,piezo6,piezo7,piezo8,piezo9,piezo10,piezo11,piezo12};
char plexis[12]={'a','b','c','d','e','f','g','h','i','j','k','l'};
int treshhold = 80;
int wait = 0;

//LEDS
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
int drie=109;
int vier=43;
int vijf=103;
int zes=231;
int zeven=44;
int acht=239;
int negen=111;

int bufferSERIAL[5];

float timeCount = 0;
int leds[2];
unsigned long Timer;
unsigned long Timer2;
int val;
int LEVENS=3;
char plexi;
char lasthit;
int SCORE;
int HIGHSCORE;

int drawRows[8][2]={
  {255,127},
  {255,191},
  {255,223},
  {255,239},
  {255,247},
  {255,251},
  {255,253},
  {255,254}};

int drawNothing[8][2]={
  {0,0},
  {0,0},
  {0,0},
  {0,0},
  {0,0},
  {0,0},
  {0,0},
  {0,0}};
  
/*int drawLittleHeart[8][2]={
  {66,127},
  {165,191},
  {153,223},
  {129,239},
  {66,247},
  {36,251},
  {24,253},
  {24,254}};
*/
int drawLittleHeart[8][2]={
  {6,127},//96
  {9,191},//144
  {72,223},//72
  {18,239},//19
  {18,247},//19
  {72,251},//72
  {9,253},//144
  {6,254}};

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

  
  
/*
int nul[3]={0,0,0};  
int een[3]={246,45,243};
int twee[3]={255,255,255};
int drie[3]={128,4,16};
*/
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
  pinMode(latchPin4, OUTPUT);
  pinMode(dataPin4, OUTPUT);  
  pinMode(clockPin4, OUTPUT);
  pinMode(latchPin5, OUTPUT);
  pinMode(dataPin5, OUTPUT);  
  pinMode(clockPin5, OUTPUT);
  pinMode(latchPin6, OUTPUT);
  pinMode(dataPin6, OUTPUT);  
  pinMode(clockPin6, OUTPUT);
  pinMode(latchPin7, OUTPUT);
  pinMode(dataPin7, OUTPUT);  
  pinMode(clockPin7, OUTPUT);
  pinMode(latchPin8, OUTPUT);
  pinMode(dataPin8, OUTPUT);  
  pinMode(clockPin8, OUTPUT);
  Serial.begin(9600);
  
  
}

void loop() 
{
  // UPDATE HIGH SCORE
  if (LEVENS == 0)  {
    if (SCORE > HIGHSCORE) {
      HIGHSCORE = SCORE;
      updateHIGHSCOREDIGITS(leds);
    }
  }
  //for (int i=0;i<8;i++) {
  //            updateShiftRegister6(drawNothing[i]);
  //            updateShiftRegister7(drawNothing[i]);
  //            updateShiftRegister8(drawNothing[i]);
  //}
  //Serial.println(HIGHSCORE);
  //Serial.println(SCORE);
  timeCount += 1;
  if(timeCount < 1000) {
    for (int i=0;i<8;i++) {
      switch (LEVENS)  {  
        
      case 0:
        updateShiftRegister1(drawNothing[i]);
        updateShiftRegister2(drawNothing[i]);
        updateShiftRegister3(drawNothing[i]);
      break;
        
      case 1:
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawNothing[i]);
      updateShiftRegister3(drawNothing[i]);
     /* updateShiftRegister6(drawLittleHeart[i]);
      updateShiftRegister7(drawNothing[i]);
      updateShiftRegister8(drawNothing[i]);*/
      break;
      case 2:
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      updateShiftRegister3(drawNothing[i]);
     /* updateShiftRegister6(drawLittleHeart[i]);
      updateShiftRegister7(drawLittleHeart[i]);
      updateShiftRegister8(drawNothing[i]);*/
      break;
      case 3:
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      updateShiftRegister3(drawLittleHeart[i]);
   /*   updateShiftRegister6(drawLittleHeart[i]);
      updateShiftRegister7(drawLittleHeart[i]);
      updateShiftRegister8(drawLittleHeart[i]);*/
      break;
      }
    
  }
  } else if (timeCount < 1200) {

  } else if (timeCount < 2000) {
    for (int i=0;i<8;i++) {
   
      switch (LEVENS)  {  
        
      case 0:
        updateShiftRegister1(drawNothing[i]);
        updateShiftRegister2(drawNothing[i]);
        updateShiftRegister3(drawNothing[i]);
      break;  
        
      case 1:
      updateShiftRegister1(drawLittleHeart[i]);
      break;
      case 2:
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      break;
      case 3:
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      updateShiftRegister3(drawLittleHeart[i]);
      break;
      }
    
  }
  } else if (timeCount < 2200) {
  // do nothing
  } else if (timeCount < 3000) {
    for (int i=0;i<8;i++) {
   
      switch (LEVENS)  {  
        
      case 0:
        updateShiftRegister1(drawNothing[i]);
        updateShiftRegister2(drawNothing[i]);
        updateShiftRegister3(drawNothing[i]);
      break;  
        
      case 1:
      updateShiftRegister1(drawLittleHeart[i]);
      break;
      case 2:
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      break;
      case 3:
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      updateShiftRegister3(drawLittleHeart[i]);
      break;
      }     
    
    }
  } else if (timeCount < 3200) {

  } else {
  // back to the start
  timeCount = 0;
}
  /*if(millis() - Timer > 5 ) {  
    Timer = millis();
    val = analogRead(potPin);
    Serial.println(val);
  }*/
  // READ PIEZOS
  if(millis() - Timer > 50 ) {  
    Timer = millis();
        
        int highest=0;
	int val=0;
	plexi='z';  
    
        for (int i=0;i<12;i++)  {
	
            val = analogRead(piezos[i]);
            //Serial.print(piezos[i]);
            //Serial.print(" - ");
  	    //Serial.println(val);
  	    if ((val > treshhold) && (val > highest)) {plexi=plexis[i];highest=val;}
	    /*if (highest > 600)  {
              updateShiftRegister6(drawRows[i]);
              updateShiftRegister7(drawRows[i]);
              updateShiftRegister8(drawRows[i]);
            }
            else if (highest > 200)  {
              updateShiftRegister6(drawRows[i]);
              updateShiftRegister7(drawRows[i]);
              updateShiftRegister8(drawNothing[i]);
            }
            else {
              updateShiftRegister6(drawRows[i]);
              updateShiftRegister7(drawNothing[i]);
              updateShiftRegister8(drawNothing[i]);
            }
            */
        }
        //Serial.println(plexi);
        //Serial.println(lasthit);
        //lasthit=plexi;
        if (plexi != 'z' && wait == 0) {
          Serial.println(plexi);
          //Serial.print(" - ");
  	  //Serial.println(highest);
          wait=1;
          
        }
        else  {
          wait=0; //sla beurt over
        }
        
  // READ OPENFRAMEWORKS
  int i=0;
        // if data is available on hardwareserial port ==> data is comming from PC or notebook
  if (Serial.available())  {
    while(Serial.available())          // reading data into char array 
    {
      
        bufferSERIAL[i]=Serial.read();     // writing data into array
        if (bufferSERIAL[i] == 13) break;
        i++;
        
    }
    int leds[3];
    leds[2]=bufferSERIAL[0];
    leds[1]=bufferSERIAL[1];
    leds[0]=bufferSERIAL[2];
    /*
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
    */
    // SHOW SCORE ON LEDDIGITS
    updateSCOREDIGITS(leds);
    
    
    
    char life=bufferSERIAL[3];
    //Serial.println(life);
    switch (life)  {
     
     case '0':
     LEVENS=0;
     break;
     case '1':
     LEVENS=1;
     break;
     case '2':
     LEVENS=2;
     break;
     case '3':
     LEVENS=3;
     break;
      
    }
    // UPDATE HIGH SCORE
  if (LEVENS == 0)  {
    if (SCORE > HIGHSCORE) {
      HIGHSCORE = SCORE;
      updateHIGHSCOREDIGITS(leds);
    }
  }
    for (int i=0;i<6;i++)  {
        bufferSERIAL[i]=NULL;     // writing data into array
    }
   }
   }   
  
} 






