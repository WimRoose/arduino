void updateLEDDIGITS(int c[3])  {
   int ledbinaries[3];
   switch (c[0])  {
    
    case '1':
     ledbinaries[0]=een1;
     break;  
    case '2':
     ledbinaries[0]=twee1;
     break;
    case '3':
     ledbinaries[0]=drie1;
     break;  
    case '4':
     ledbinaries[0]=vier1;
     break;
    case '5':
     ledbinaries[0]=vijf1;
     break;  
    case '6':
     ledbinaries[0]=zes1;
     break;
    case '7':
     ledbinaries[0]=zeven1;
     break;  
    case '8':
     ledbinaries[0]=acht1;
     break;
    case '9':
     ledbinaries[0]=negen1;
     break;  
    case '0':
     ledbinaries[0]=nul1;
     break; 
   }
   switch (c[1])  {
    
    case '1':
     ledbinaries[1]=een2;
     break;  
    case '2':
     ledbinaries[1]=twee2;
     break;
    case '3':
     ledbinaries[1]=drie2;
     break;  
    case '4':
     ledbinaries[1]=vier2;
     break;
    case '5':
     ledbinaries[1]=vijf2;
     break;  
    case '6':
     ledbinaries[1]=zes2;
     break;
    case '7':
     ledbinaries[1]=zeven2;
     break;  
    case '8':
     ledbinaries[1]=acht2;
     break;
    case '9':
     ledbinaries[1]=negen2;
     break;  
    case '0':
     ledbinaries[1]=nul2;
     break; 
   }
   switch (c[2])  {
    
    case '1':
     ledbinaries[2]=een3;
     break;  
    case '2':
     ledbinaries[2]=twee3;
     break;
    case '3':
     ledbinaries[2]=drie3;
     break;  
    case '4':
     ledbinaries[2]=vier3;
     break;
    case '5':
     ledbinaries[2]=vijf3;
     break;  
    case '6':
     ledbinaries[2]=zes3;
     break;
    case '7':
     ledbinaries[2]=zeven3;
     break;  
    case '8':
     ledbinaries[2]=acht3;
     break;
    case '9':
     ledbinaries[2]=negen3;
     break;  
    case '0':
     ledbinaries[2]=nul3;
     break; 
   }   
  updateShiftRegister4(ledbinaries);
}

void updateShiftRegister4(int leds[3])
{
   digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, LSBFIRST, leds[2]);
    shiftOut(dataPin4, clockPin4, LSBFIRST, leds[1]);
    shiftOut(dataPin4, clockPin4, LSBFIRST, leds[0]);
   digitalWrite(latchPin4, HIGH);
}
