void checkCode()  {
    
   Serial.println();
   delay(1000);
   listenToSerial();
   
}

void listenToSerial()
{
  int received=0;
  while (received != 1) {
  if (Serial.available())     {      // if data is available on hardwareserial port ==> data is comming from PC or notebook

    while(Serial.available())          // reading data into char array 
    {
      serialBuffer[countSerial]=Serial.read();     // writing data into array
      if(countSerial == 0)break;
      countSerial++;
    }
    lcd.clear();
    received=1; // we hebben gewacht, en iets ontvangen
    
    if (strcmp (serialBuffer, "0") == 0) { // ticket normaal gezien geprint
      
      lcd.print("Ticket wordt");
      lcd.setCursor(0, 1);
      lcd.print("geprint!");
      //listenToError();
      
    }
    else if (strcmp (serialBuffer, "1") == 0) { // uitgaan van netwerkfout (2do)
     
      lcd.print("Foute code, geef");
      lcd.setCursor(0, 1);
      lcd.print("code opnieuw in");
    
    }
    //else if(strcmp (serialBuffer, "2") == 0) {
    else {
      
      lcd.print("Netwerkfout");
      lcd.setCursor(0, 1);
      
    }
    
    clearBuffer(serialBuffer,countSerial);              // call clearBufferArray function to clear the storaged data from the array
    countSerial = 0;
    delay (2000);
    lcd.clear();
    lcd.print("Geef code in + #");
    lcd.setCursor(0,1);
  }
  //delay(100); 
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


