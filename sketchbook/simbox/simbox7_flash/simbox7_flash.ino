//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART
//
// Plotseling probleem: webserver werkte niet meer naar behoren (gewoon raar en onlogisch gedrag). Bij debugging bleek bovendien dat Serial niet meer werkte. 
// Oorzaak was het samen draaien van GPRS, webserving en Serial. Een uitcommenten en alles werkte opnieuw. RAM check geintegreerd, en toen bleek dat er geheugen te weinig was;
// Maar komma's en punten aangepast, maar vooral die String in sendEmail was de boosdoener.... Dus aangepast naar char []
// zie ook http://www.arduino.cc/en/Tutorial/Memory !!!

#include <Dns.h>
#include <Dhcp.h>
#include <EthernetClient.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <util.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include <string.h>
#include <SPI.h>
#include <avr/pgmspace.h>

SoftwareSerial GPRS(7,8); //initialiseer digital pins voor software serial comm tussen arduino en GPRS shield

// ******** VARIABELEN *********** //

byte mailserver[] = { 195,130,137,68 }; // 
//byte mailserver[] = { 192,168,2,6 };
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x5B, 0x36 }; // Enter a MAC address and IP address for your controller below. (zie etiketje!!!!)
IPAddress ip(10,200,200,199);
//IPAddress ip(192,168,2,50);
EthernetServer server(80);
char telefoonNrs[30][11];
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
byte relayPin=4;

prog_char telNr_1[] PROGMEM = {};  // prog_uchar werkte niet
prog_char telNr_2[] PROGMEM = {};
PROGMEM const char *tabel[] = 
{
    telNr_1,telNr_2
};
    
char buffer[10];

// ******** END_VARIABELEN *********** //


void setup()
{
  
  
  GPRS.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  GPRS.write("AT+CPIN=\"6486\"\r"); // geef PINCODE in
  delay(100);
  if (GPRS.available()) {
    Serial.println("GPRS data received, shield on");
  }
  else {
    Serial.println("GPRS shield off, turning it on...");   
    powerUpOrDown();
    delay(1000);
    GPRS.write("AT+CPIN=\"6486\"\r"); // geef PINCODE in
    delay(1000);
    
  }
  
  
  GPRS.write("AT+CMGF=1\r"); // set GPRS-shield in textmode
  delay(100);
  GPRS.write("\r\r"); // blijft soms haperen, vandaar extra carriage return
  delay(100);
  Ethernet.begin(mac, ip); // start the Ethernet connection and the server:
  server.begin();
  pinMode(relayPin,OUTPUT);
}

void loop()
{
  
  //listenToGPRS();
  webserving();
  listenToSerial();
  Serial.println(freeRam());   // Veeeeeeeery handig!

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
  byte rip[4]; 
  int cc=0;
  byte b=0; // boolean die op 1 gezet wordt als er een ### is ontvangen, in dat geval moet else blablabla overgeslaan worden
  // listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
        
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
         
           //client.println("Line feed detected!");  // debug
           //client.println("HTTP/1.1 200 OK");
           //client.println("Content-Type: text/html");
           //client.println();
         
           if (strcmp (bufferWEB, "404#\r\n") == 0)  {
         
             client.println("****** BEGIN WEBSERVER ******");
             client.println("404# received");
             client.println("****** END WEBSERVER ******");
             clearBufferArray3();
             countWEB=0;
             //client.println(W5100.readRIPR(remoteIP));
             client.getRemoteIP(rip);   
               for (int bcount= 0; bcount < 4; bcount++)
               {
                   client.print(rip[bcount], DEC);
                   if (bcount<3) client.print(".");
               } 
             sendEmail("404# received");
             break;
            
           }
           
          else if (strcmp (bufferWEB, "###\r\n") == 0)  {
         
            client.println("****** BEGIN WEBSERVER ******");
            client.println("### received, waiting for next nr");
            client.println("****** END WEBSERVER ******");
            clearBufferArray3();
            countWEB=0;
            sendEmail("### received");
            b=1;
            
            
           }
           else if (strcmp (bufferWEB, "#END\r\n") == 0)  {
         
            client.println("****** BEGIN WEBSERVER ******");
            client.println("#END received");
            client.println("****** END WEBSERVER ******");
            clearBufferArray3();
            countWEB=0;
            int i;
            for (i=0;i<cc;i++) {
              client.println(telefoonNrs[i]);
            }
            sendNrsByEmail(telefoonNrs);
            sendEmail("#END received");
            cc=0;
            b=0;
            break;
           }
           
           else if (b=0)  {
           
             
            client.println("**BEGIN WEBSERVER **");
            client.println("Blablabla!");
            client.println("** END WEBSERVER **");
            clearBufferArray3();
            countWEB=0;
            break;
           }
           else {
            
             
              //strcpy_P(buffer, (char*)pgm_read_word(&(tabel[i]))); // Necessary casts and dereferencing, just copy. 
              strcpy_P((char*)&telNr_1[0]+cc, bufferWEB);
            client.print("***aargh** ");
            strcpy_P(buffer, (char*)pgm_read_word(&(tabel[cc])));
            client.print(buffer);
            strcpy ( telefoonNrs[cc], bufferWEB );
            telefoonNrs[cc][10] = '\0';
            client.print("****** ");
            client.println(telefoonNrs[cc]);
            client.println(cc);
            cc++;
            clearBufferArray3();
            countWEB=0;
           
           }
          }      
        
               
      }
    }
    
    // give the web browser time to receive the data
    delay(100);
    // close the connection:
    client.stop();
    
    
  }
}

void listenToGPRS()
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
      digitalWrite(relayPin,HIGH);
       delay(2000);
      digitalWrite(relayPin,LOW);
       delay(1000);
      
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
}

void listenToSerial()
{
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

void sendEmail(char str[])  
{
  //EthernetClient mailclient(mailserver, 25);
  //EthernetClient client = server.available();
  
  EthernetClient mailclient;
  if (mailclient.connect(mailserver, 25)) {
  //if (mailclient.connect()) {
    
    Serial.println("connected");
    mailclient.println("EHLO VOORUIT.BE");
    mailclient.println("MAIL FROM:<simbox@vooruit.be>");
    mailclient.println("RCPT TO:<systeembeheer@vooruit.be>");
    mailclient.println("DATA");
    mailclient.println("SUBJECT: Hellooooo");
    mailclient.println();
    mailclient.println(str);
    mailclient.println(".");
    mailclient.println(".");
  } else {
    Serial.println("connection failed");
  }
  mailclient.stop();
}

void sendNrsByEmail(char str[50][11])  
{
  //EthernetClient mailclient(mailserver, 25);
  //EthernetClient client = server.available();
  
  EthernetClient mailclient;
  if (mailclient.connect(mailserver, 25)) {
  //if (mailclient.connect()) {
    
    Serial.println("connected");
    mailclient.println("EHLO VOORUIT.BE");
    mailclient.println("MAIL FROM:<simbox@vooruit.be>");
    mailclient.println("RCPT TO:<systeembeheer@vooruit.be>");
    mailclient.println("DATA");
    mailclient.println("SUBJECT: Hellooooo");
    mailclient.println();
    int i;
          for (i=0;i<5;i++) {
             mailclient.println(str[i]);
            }
    
    mailclient.println(".");
    mailclient.println(".");
  } else {
    Serial.println("connection failed");
  }
  mailclient.stop();
}
  
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


