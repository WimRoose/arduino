

//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 

#include <SoftwareSerial.h>

SoftwareSerial GPRS(7, 8);

char bufferGPRS[64]; // buffer array for data recieve over serial port. Let op!!! Buffer size in SoftwareSerial lib is maar 64 bytes! 
char bufferSERIAL[64];
int countGPRS=0;     // counter for bufferGPRS array
int countSERIAL=0;     // counter for bufferGPRS array
char newMessage[14] = "\r\n+CMTI: \"SM\"";  // typische melding als er een nieuwe sms binnenkomt
void setup()
{
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  GPRS.write("AT+CPIN=\"6486\"\r");
  delay(100);
  GPRS.write("AT+CMGF=1\r");
  delay(100);
}

void loop()
{
  //if (GPRS.available())     {         // if date is comming from softwareserial port ==> data is comming from gprs shield
  //leessms();
  //}
  if (GPRS.available()) {

    while(GPRS.available())          // reading data into char array 
    {
      bufferGPRS[countGPRS++]=GPRS.read();     // writing data into array
      if(countGPRS == 64)break;
      if (bufferGPRS[countGPRS-1] == '\"')  {
        if (bufferGPRS[countGPRS] == '+')  {
          Serial.println("Phone Number found!");
      }
      }
    }
    Serial.print("Buffer=");
    Serial.println(countGPRS);
    Serial.println(bufferGPRS);

    //Serial.println((int)bufferGPRS[0]);
    //Serial.println((int)bufferGPRS[1]);
    //Serial.println((int)bufferGPRS[2]);

    if (strncmp (bufferGPRS, newMessage,12) == 0)  {
      Serial.print("New SMS at index ");
      Serial.println(bufferGPRS[14]);
      Serial.println("Checking SMS...");
      GPRS.write("AT+CMGR=");
      GPRS.write(bufferGPRS[14]);
      GPRS.write("\r");
    }
    //char *loc=strstr(bufferGPRS, "REC");
    //if (loc > 0){
    //  Serial.println(loc);
    //}
    delay(100);
  }
  clearBufferArray();              // call clearBufferArray function to clear the storaged data from the array
  countGPRS = 0;

  if (Serial.available())     {      // if data is available on hardwareserial port ==> data is comming from PC or notebook

    while(Serial.available())          // reading data into char array 
    {
      bufferSERIAL[countSERIAL++]=Serial.read();     // writing data into array
      if(countSERIAL == 64)break;

    }
    GPRS.write(bufferSERIAL);       // write it to the GPRS shield
    clearBufferArray2();              // call clearBufferArray function to clear the storaged data from the array
    countSERIAL = 0;
  }
  delay(100); 

}

void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<countGPRS;i++)
  { 
    bufferGPRS[i]=NULL;
  }                  // clear all index of array with command NULL
}
void clearBufferArray2()              // function to clear buffer array
{
  for (int i=0; i<countSERIAL;i++)
  { 
    bufferSERIAL[i]=NULL;
  }                  // clear all index of array with command NULL
}



