

//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 

#include <SoftwareSerial.h>
#include <string.h>


SoftwareSerial GPRS(7, 8);

char bufferGPRS[64]; // buffer array for data recieve over serial port. Let op!!! Buffer size in SoftwareSerial lib is maar 64 bytes! 
char bufferSERIAL[64];
int countGPRS=0;     // counter for bufferGPRS array
int countSERIAL=0;     // counter for bufferGPRS array
char newMessage[14] = "\r\n+CMTI: \"SM\"";  // typische melding als er een nieuwe sms binnenkomt
char * pn; // char pointer voor strstr (returnt een pointer naar de eerste occerence vd te zoeken string). pn is een poiter naar een read-only char array
char telnummer[13]; // array of chars
char message[12]; // array of chars

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
      if(countGPRS == 128)break;
    }
    Serial.print("Buffer=");
    Serial.println(countGPRS);
    Serial.println(bufferGPRS);
    
    
    pn=strstr(bufferGPRS,"\"+"); //zoek naar telefoonnumer in antwoord GPRS, in case of AT+CMGR=X dus
    if (pn!=NULL) {    // als er geen occurence is -> geen NULL pointer
     
     Serial.print("Phone number found!-> ");
     for (int j=0;j<12;j++) {
      telnummer[j]=pn[j+1];  // wijs data van pointerlocatie naar volgend char in array toe aan arraynummer zoveel 
      
      // An array is just a sequence of variables. But there is a rule, that C++ looks arrays as if they were pointers. What does it means? It means that if you write arr, compiler takes it as &arr[0] (except in three conditions that I'll tell you soon), that is the address of the first element of the array. It has a type "pointer to T" where T is the type of array elements (that is int in our example). If you add 1 to it it will point to the second element of the array.

    //So it takes &arr as what?
     //It is one of the exceptions where the rule does not apply. It takes it as a pointer to array. It will again point to the first element of the array, but if you add one to this pointer, it will point to the address of the place right after the last element of the array (just like you skipped the array). It is a pointer to the whole the array. The value of &arr and arr is the same (address of the first element). But their type is different. Here &arr has type "pointer to the array of T" (compare it to the type of arr).
     //http://www.cplusplus.com/forum/articles/9/  
     }
     pn=strstr(pn,"\r");
     if (pn!=NULL) {
      
      
     for (int j=0;j<12;j++) {
       
       message[j]=pn[j+2];
       
     }
     }
   
     Serial.println(telnummer);
     Serial.print("message-> ");
     Serial.println(message);
     
     //AT+CMGR=1
     
    }
    
    
     
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



