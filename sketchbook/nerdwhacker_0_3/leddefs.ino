void updateSCOREDIGITS(int c[3])  {
   int ledbinaries[3];
   switch (c[0])  {
    
    case '1':
     ledbinaries[0]=een1;
     SCORE=1;
     break;  
    case '2':
     ledbinaries[0]=twee1;
     SCORE=2;
     break;
    case '3':
     ledbinaries[0]=drie1;
     SCORE=3;
     break;  
    case '4':
     ledbinaries[0]=vier1;
     SCORE=4;
     break;
    case '5':
     ledbinaries[0]=vijf1;
     SCORE=5;
     break;  
    case '6':
     ledbinaries[0]=zes1;
     SCORE=6;
     break;
    case '7':
     ledbinaries[0]=zeven1;
     SCORE=7;
     break;  
    case '8':
     ledbinaries[0]=acht1;
     SCORE=8;
     break;
    case '9':
     ledbinaries[0]=negen1;
     SCORE=9;
     break;  
    case '0':
     ledbinaries[0]=nul1;
     SCORE=0;
     break; 
   }
   switch (c[1])  {
    
    case '1':
     ledbinaries[1]=een2;
     SCORE=SCORE+10;
     break;  
    case '2':
     ledbinaries[1]=twee2;
     SCORE=SCORE+20;
     break;
    case '3':
     ledbinaries[1]=drie2;
     SCORE=SCORE+30;
     break;  
    case '4':
     ledbinaries[1]=vier2;
     SCORE=SCORE+40;
     break;
    case '5':
     ledbinaries[1]=vijf2;
     SCORE=SCORE+50;
     break;  
    case '6':
     ledbinaries[1]=zes2;
     SCORE=SCORE+60;
     break;
    case '7':
     ledbinaries[1]=zeven2;
     SCORE=SCORE+70;
     break;  
    case '8':
     ledbinaries[1]=acht2;
     SCORE=SCORE+80;
     break;
    case '9':
     ledbinaries[1]=negen2;
     SCORE=SCORE+90;
     break;  
    case '0':
     ledbinaries[1]=nul2;
     break; 
   }
   switch (c[2])  {
    
    case '1':
     ledbinaries[2]=een3;
     SCORE=SCORE+100;
     break;  
    case '2':
     ledbinaries[2]=twee3;
     SCORE=SCORE+200;
     break;
    case '3':
     ledbinaries[2]=drie3;
     SCORE=SCORE+300;
     break;  
    case '4':
     ledbinaries[2]=vier3;
     SCORE=SCORE+400;
     break;
    case '5':
     ledbinaries[2]=vijf3;
     SCORE=SCORE+500;
     break;  
    case '6':
     ledbinaries[2]=zes3;
     SCORE=SCORE+600;
     break;
    case '7':
     ledbinaries[2]=zeven3;
     SCORE=SCORE+700;
     break;  
    case '8':
     ledbinaries[2]=acht3;
     SCORE=SCORE+800;
     break;
    case '9':
     ledbinaries[2]=negen3;
     SCORE=SCORE+900;
     break;  
    case '0':
     ledbinaries[2]=nul3;
     break; 
   }   
  updateShiftRegister4(ledbinaries);
}

void updateHIGHSCOREDIGITS(int c[3])  {
   int ledbinaries[3];
   switch (c[0])  {
    
    case '1':
     ledbinaries[0]=een;
     break;  
    case '2':
     ledbinaries[0]=twee;
     break;
    case '3':
     ledbinaries[0]=drie;
     break;  
    case '4':
     ledbinaries[0]=vier;
     break;
    case '5':
     ledbinaries[0]=vijf;
     break;  
    case '6':
     ledbinaries[0]=zes;
     break;
    case '7':
     ledbinaries[0]=zeven;
     break;  
    case '8':
     ledbinaries[0]=acht;
     break;
    case '9':
     ledbinaries[0]=negen;
     break;  
    case '0':
     ledbinaries[0]=nul;
     break; 
   }
   switch (c[1])  {
    
    case '1':
     ledbinaries[1]=een;
     break;  
    case '2':
     ledbinaries[1]=twee;
     break;
    case '3':
     ledbinaries[1]=drie;
     break;  
    case '4':
     ledbinaries[1]=vier;
     break;
    case '5':
     ledbinaries[1]=vijf;
     break;  
    case '6':
     ledbinaries[1]=zes;
     break;
    case '7':
     ledbinaries[1]=zeven;
     break;  
    case '8':
     ledbinaries[1]=acht;
     break;
    case '9':
     ledbinaries[1]=negen;
     break;  
    case '0':
     ledbinaries[1]=nul;
     break; 
   }
   
   switch (c[2])  {
    
    case '1':
     ledbinaries[2]=een;
     break;  
    case '2':
     ledbinaries[2]=twee;
     break;
    case '3':
     ledbinaries[2]=drie;
     break;  
    case '4':
     ledbinaries[2]=vier;
     break;
    case '5':
     ledbinaries[2]=vijf;
     break;  
    case '6':
     ledbinaries[2]=zes;
     break;
    case '7':
     ledbinaries[2]=zeven;
     break;  
    case '8':
     ledbinaries[2]=acht;
     break;
    case '9':
     ledbinaries[2]=negen;
     break;  
    case '0':
     ledbinaries[2]=nul;
     break; 
   
   }   
  updateShiftRegister5(ledbinaries);
}

void updateShiftRegister4(int leds[3])
{
   digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, LSBFIRST, leds[2]);
    shiftOut(dataPin4, clockPin4, LSBFIRST, leds[1]);
    shiftOut(dataPin4, clockPin4, LSBFIRST, leds[0]);
   digitalWrite(latchPin4, HIGH);
}

void updateShiftRegister5(int leds[3])
{
   digitalWrite(latchPin5, LOW);
    shiftOut(dataPin5, clockPin5, LSBFIRST, leds[2]);
    shiftOut(dataPin5, clockPin5, LSBFIRST, leds[1]);
    shiftOut(dataPin5, clockPin5, LSBFIRST, leds[0]);
   digitalWrite(latchPin5, HIGH);
}
