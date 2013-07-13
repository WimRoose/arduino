

//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 

#include <SoftwareSerial.h>
#include <string.h>
#include <SPI.h>
#include <Ethernet.h>

SoftwareSerial GPRS(7,8); //initialiseer digital pins voor software serial comm tussen arduino en GPRS shield

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(10,200,200,199);
IPAddress ip(192,168,2,5);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

char bufferGPRS[128]; // buffer array for data recieve over serial port. Let op!!! Buffer size in SoftwareSerial lib is maar 64 bytes! 
char bufferSERIAL[64];
char bufferWEB[6];
int countGPRS=0;     // counter for bufferGPRS array
int countSERIAL=0;     // counter for bufferGPRS array
int countWEB=0;
char newMessage[14] = "\r\n+CMTI: \"SM\"";  // typische melding als er een nieuwe sms binnenkomt
char * pn; // char pointer voor strstr (returnt een pointer naar de eerste occerence vd te zoeken string). pn is een poiter naar een read-only char array
char telnummer[13]; // array of chars
char message[13]; // array of chars
int alreadyStarted=0;

void setup()
{
  if (alreadyStarted == 0){
    powerUpOrDown();
    alreadyStarted=1;
  }
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  GPRS.write("AT+CPIN=\"6486\"\r"); // geef PINCODE in
  delay(100);
  GPRS.write("AT+CMGF=1\r"); // set GPRS-shield in textmode
  delay(100);
  GPRS.write("\r"); // blijft soms haperen, vandaar extra carriage return
  delay(100);
  Ethernet.begin(mac, ip); // start the Ethernet connection and the server:
  server.begin();
}

void loop()
{
  if (GPRS.available()) {

    while(GPRS.available())          // reading data into char array 
    
    {
      bufferGPRS[countGPRS++]=GPRS.read();     // writing incoming char into array
      if(countGPRS == 128)break;
    }
    //Serial.print("Buffer="); // debug
    //Serial.println(countGPRS); // debug
    Serial.println("****** BEGIN GPRS ******");
    Serial.println(bufferGPRS);
    Serial.println("****** END GPRS ******");
    
    pn=strstr(bufferGPRS,"\"+"); // zoek naar telefoonnumer in antwoord GPRS, in case of AT+CMGR=X dus
    if (pn!=NULL) {    // als er een occurence is (pn is pointer naar locatie in array)
     
     Serial.print("Phone number found!-> ");
     
     for (int j=0;j<12;j++) {
      telnummer[j]=pn[j+1];  // wijs data van pointerlocatie naar volgend char in array toe aan arraynummer zoveel 
      
      // An array is just a sequence of variables. But there is a rule, that C++ looks arrays as if they were pointers. What does it means? It means that if you write arr, compiler takes it as &arr[0] (except in three conditions that I'll tell you soon), that is the address of the first element of the array. It has a type "pointer to T" where T is the type of array elements (that is int in our example). If you add 1 to it it will point to the second element of the array.

    //So it takes &arr as what?
     //It is one of the exceptions where the rule does not apply. It takes it as a pointer to array. It will again point to the first element of the array, but if you add one to this pointer, it will point to the address of the place right after the last element of the array (just like you skipped the array). It is a pointer to the whole the array. The value of &arr and arr is the same (address of the first element). But their type is different. Here &arr has type "pointer to the array of T" (compare it to the type of arr).
     //http://www.cplusplus.com/forum/articles/9/  
     }
     pn=strstr(pn,"\r"); // ga op zoek naar CR in gevonden string (= begin van textboodschap)
     if (pn!=NULL) {
       for (int j=0;j<12;j++) {
         message[j]=pn[j+2];
       }
     }
     Serial.println(telnummer);
     Serial.print("message-> ");
     Serial.println(message);
     
     if (strcmp (telnummer, "+32495221978") == 0)  {
      
      Serial.println("Telefon klopski");
       
     }
     if (strncmp (message, "404#",4) == 0)  {
      
      Serial.println("Code ook klopski, openen deuren");
      
      GPRS.write("AT+CMGD=4,4\r"); // verwijder ALLE sms'en
      delay(100);
     }
          
    }
 
    if (strncmp (bufferGPRS, newMessage,12) == 0)  { // check of er een nieuwe sms is binnengekomen
      Serial.print("New SMS at index ");
      Serial.println(bufferGPRS[14]);
      Serial.println("Checking SMS...");
      GPRS.write("AT+CMGR="); // commando dat nieuwe sms op indexlocatie bufferGPRS[14] toont.
      GPRS.write(bufferGPRS[14]);
      GPRS.write("\r");
    }
    delay(100);
  }
  clearBufferArray();              // call clearBufferArray function to clear the storaged data from the array
  countGPRS = 0;
  
  webserving();
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
void clearBufferArray3()              // function to clear buffer array
{
  for (int i=0; i<countWEB;i++)
  { 
    bufferWEB[i]=NULL;
  }                  // clear all index of array with command NULL
}
void powerUpOrDown()
{
   pinMode(9, OUTPUT);
  digitalWrite(9,LOW);
  delay(1000);
  digitalWrite(9,HIGH);
  delay(2000);
  digitalWrite(9,LOW);
  delay(3000);
}
void webserving()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    
    while (client.connected()) {
      if (client.available()) {
        
          char c =client.read();     // writing data into array. De omweg via char c was nodig, aangezien bufferWEB[countWEB++]=client.read() niet werkte :-/
          bufferWEB[countWEB++] = c;
        
        //client.print("Received char ->");  //debug
        //client.println(c);
        //client.print("Buffer ->");
        //client.println(bufferWEB);
        // client.println((int)c); //debug
        
        if (c == '\n') { // line feed: commando ontvangen!
         
           // client.println("Line feed detected!");  // debug
           client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println();
           if (strcmp (bufferWEB, "404#\r\n") == 0)  {
         
            client.println("****** BEGIN WEBSERVER ******");
            client.println("404# received");
            client.println("****** END WEBSERVER ******");
            clearBufferArray3();
            countWEB=0;
            break;
           }
           else {
           
            client.println("****** BEGIN WEBSERVER ******");
            client.println("Blablabla!");
            client.println("****** END WEBSERVER ******");
            clearBufferArray3();
            countWEB=0;
            break;  
          } 
                 
        }
               
      }
    }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    
    
  }
}


