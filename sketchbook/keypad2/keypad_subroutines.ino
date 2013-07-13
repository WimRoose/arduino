// error codes

#define TICKETPRINTED = 0
#define WRONGCODE = 1
#define UNKNOWNERROR = 2


void checkCode()  {
    
   Serial.println();
   delay(1000);
   listenToSerial();
   
}

void listenToSerial()
{
  if (Serial.available())     {      // if data is available on hardwareserial port ==> data is comming from PC or notebook

    while(Serial.available())          // reading data into char array 
    {
      serialBuffer[countSerial]=Serial.read();     // writing data into array
      if(countSerial == 4)break;
      countSerial++;
    }
    lcd.clear();
    //lcd.print(serialBuffer); 
    //Serial.println(serialBuffer);
    if (strcmp (serialBuffer, "1") == 0) {
      
      lcd.print("Ticket wordt");
      lcd.setCursor(0, 1);
      lcd.print("geprint!");
      clearBuffer(serialBuffer,countSerial);              // call clearBufferArray function to clear the storaged data from the array
    countSerial = 0;
      listenToError();
    }
    else {
     lcd.print("Foute code, geef");
     lcd.setCursor(0, 1);
      //lcd.print("code opnieuw in");
      delay(100);
      lcd.print("code opnieuw in");
    }
    clearBuffer(serialBuffer,countSerial);              // call clearBufferArray function to clear the storaged data from the array
    countSerial = 0;
  }
  delay(100); 
}

void clearBuffer(char * buffer, int counter)              // function to clear buffer array
{
  for (int i=0; i<=counter;i++)
  { 
    buffer[i]=NULL;
  }                  // clear all index of array with command NULL
}

void listenToError()
{
  int received=0;
  while (received != 1) {
  if (Serial.available())     {      // if data is available on hardwareserial port ==> data is comming from PC or notebook

    while(Serial.available())          // reading data into char array 
    {
      serialBuffer[countSerial]=Serial.read();     // writing data into array
      if(countSerial == 4)break;
      countSerial++;
    }
    lcd.clear();
    received=1;
    if (strcmp (serialBuffer, "11111") == 0) {
      
      lcd.print("Ticket geprint!");
      lcd.setCursor(0, 1);
      lcd.print(serialBuffer);
      delay (2000);
      lcd.clear();
      lcd.print("Geef code in");
    }
    else {
     lcd.print("Unknown error");
     lcd.setCursor(0, 1);
      lcd.print(serialBuffer);
     delay (2000);
     lcd.clear();
      lcd.print("Geef code in");
    }
    clearBuffer(serialBuffer,countSerial);              // call clearBufferArray function to clear the storaged data from the array
    countSerial = 0;
  }
  delay(100); 
  }
  delay(100);
}
