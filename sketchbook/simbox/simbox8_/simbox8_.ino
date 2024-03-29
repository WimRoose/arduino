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

// Aanpassing nodig in Ethernetlibrary om IP adres van de remote client te achterhalen, nodig om toch enige vorm van access control in te stellen
//
//  I added the following lines to the end of the EthernetClient.cpp file:
//  uint8_t *EthernetClient::getRemoteIP(uint8_t remoteIP[])
//    {
//      W5100.readSnDIPR(_sock, remoteIP);
//      return remoteIP;
//     }
//
//  I then added the following line (under the virtual void stop(); line)to the EthernetClient.h file:
//    uint8_t *getRemoteIP(uint8_t RemoteIP[]);//adds remote ip address
//
//  Finally I used the following code in my sketch to access the remote IP:
//    client.getRemoteIP(rip); // where rip is defined as byte rip[] = {0,0,0,0 };
//
//  to display the IP in the serial monitor, I used:
//
//    for (int bcount= 0; bcount < 4; bcount++)
//       {
//          Serial.print(rip[bcount], DEC);
//          if (bcount<3) Serial.print(".");
//       }
//
//  I'm not sure that this is the most elegant way, but it works in the IDE v1.0

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
#include <EEPROM.h>

SoftwareSerial GPRS(7,8); //initialiseer digital pins voor software serial comm tussen arduino en GPRS shield

// ******** VARIABELEN *********** //

//byte mailserver[] = { 195,130,137,68 }; // 
byte mailserver[] = { 192,168,2,6 };
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x5B, 0x36 }; // Enter a MAC address and IP address for your controller below. (zie etiketje!!!!)
//IPAddress ip(10,200,200,199);
IPAddress ip(192,168,2,50);
EthernetServer server(80);
char telefoonNrs[30][11];
char bufferGPRS[128]; // buffer array for data recieve over serial port. Let op!!! Buffer size in SoftwareSerial lib is maar 64 bytes! 
char bufferSERIAL[64];
char bufferWEB[13];
int countGPRS=0;     // counter for bufferGPRS array
int countSERIAL=0;     // counter for bufferGPRS array
int countWEB=0;
char newMessage[14] = "\r\n+CMTI: \"SM\"";  // typische melding als er een nieuwe sms binnenkomt
char * pn; // char pointer voor strstr (returnt een pointer naar de eerste occerence vd te zoeken string). pn is een poiter naar een read-only char array
char telnummer[13]; // array of chars
char message[13]; // array of chars
byte relayPin=4;
  char eepromValue;
int  eepromIntValue;
//char remoteIPADDR[17];

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
  //for (int i=0;i<1024;i++) {
              
  //    EEPROM.write(i,255);
             
  //}
}

void loop()
{
  
  listenToGPRS();
  webserving();
  listenToSerial();
  Serial.println(freeRam());   // Veeeeeeeery handig!

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
            //client.print("Countweb ->");
            //client.println(countWEB);
           //client.println((int)c); //debug
        
        if (c == '\n') { // line feed: commando ontvangen!
                    
         client.print("B has value ");
         client.println(b);
           if (strcmp (bufferWEB, "404#\r\n") == 0)  {
         
             client.println("****** BEGIN WEBSERVER ******");
             client.print("404# received from ");
             client.getRemoteIP(rip);  
             
             for (int bcount= 0; bcount < 4; bcount++)
               {
                   //remoteIPADDR[ipaddrCount]= rip[bcount];
                   client.print(rip[bcount], DEC);
                   //client.print(remoteIPADDR[ipaddrCount], DEC);
                   //strcat(remoteIPADDR, (char*)rip[bcount]);
                   if (bcount<3) {
                     client.print(".");
                     //remoteIPADDR[ipaddrCount++]='.';
                   }
                   //ipaddrCount++;
               }
             client.println();
             client.println("****** END WEBSERVER ******");
             //sendEmail("404# received");
             //sendEmail(remoteIPADDR);
             sendEmail("404# received");
             break;
            
           }
           
          else if (strcmp (bufferWEB, "###\r\n") == 0)  {
         
            client.println("****** BEGIN WEBSERVER ******");
            client.println("### received, waiting for next nr");
            client.println("****** END WEBSERVER ******");
            //sendEmail("### received");
            b=1;
            
            
           }
           else if (strcmp (bufferWEB, "#END\r\n") == 0)  {
         
            client.println("****** BEGIN WEBSERVER ******");
            client.println("#END received");
            client.println("****** END WEBSERVER ******");
            
            int i;
            for (i=0;i<cc;i++) {
              client.println(telefoonNrs[i]);
            }
            //sendNrsByEmail(telefoonNrs);
            //sendEmail("#END received");
            cc=0;
            b=0;
            //clearBufferArray3();
            //countWEB=0;
            break;
           }
           
           else if (strcmp (bufferWEB, "#READ\r\n") == 0)  {
         
            client.println("****** BEGIN WEBSERVER ******");
            client.println("#READ received");
            client.println("****** END WEBSERVER ******");
            
            int i;
            for (i=0;i<1024;i++) {
              
              eepromIntValue = EEPROM.read(i);
              if ((eepromIntValue > 47) && (eepromIntValue < 58)) {  // EEPROM-locaties die nog nooit beschreven zijn hebben de waarde 255
                  eepromValue = (char)eepromIntValue;
                  
                  client.print(eepromValue);
                  delay(50);
                  //Serial.println(freeRam());
                  //client.print("->");
                  //client.print(i);
                  if ((i+1) % 10 == 0 && i > 0) {
                    client.print("\n");
                  }
              }
            }
            //sendNrsByEmail(telefoonNrs);
            
            //sendEmail("#READ received");
            //clearBufferArray3();
            //countWEB=0;         
            break;
           }
           
           else if (b==0)  {
           
            client.println("**BEGIN WEBSERVER **");
            client.println("Blablabla!");
            client.println("** END WEBSERVER **");
            
            break;
           }
           else {
            
            strcpy ( telefoonNrs[cc], bufferWEB );
            telefoonNrs[cc][10] = '\0';
            client.print("****** ");
            client.println(telefoonNrs[cc]);
            client.println(cc);
            for (int i=0;i<10;i++) {
               EEPROM.write((cc*10)+i, bufferWEB[i] );
               delay(4);
               
            }
            
            cc++;
            
           
           } //else
            //clearBufferArray88(bufferWEB, countWEB);
            clearBufferArray99();
            countWEB=0;
          } //line feed      
                    
      } // if (client.available)
    } // while (client.connected)
    //clearBufferArray88(bufferWEB, countWEB);
    clearBufferArray99();
    countWEB=0;
    // give the web browser time to receive the data
    delay(100);
    // close the connection:
    client.stop();
    
    
  } //if (client)
  
} //void

void clearBufferArray88(char * buffer, int counter)              // function to clear buffer array
{
  for (int i=0; i<counter;i++)
  { 
    buffer[i]=NULL;
  }                  // clear all index of array with command NULL
}
void clearBufferArray99()              // function to clear buffer array
{
  for (int i=0; i<13;i++)
  { 
    bufferWEB[i]=NULL;
  }                  // clear all index of array with command NULL
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
  clearBufferArray88(bufferGPRS,countGPRS);              // call clearBufferArray function to clear the storaged data from the array
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
    clearBufferArray88(bufferSERIAL,countSERIAL);              // call clearBufferArray function to clear the storaged data from the array
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


