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
char bufferWEB[6];
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
  GPRS.write("AT+CPIN=\"8995\"\r"); // geef PINCODE in
  delay(100);
  if (GPRS.available()) {
    Serial.println("GPRS data received, shield on");
  }
  else {
    Serial.println("GPRS shield off, turning it on...");   
    powerUpOrDown();
    delay(1000);
    GPRS.write("AT+CPIN=\"8995\"\r"); // geef PINCODE in
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
  listenToGPRS();
  webserving();
  listenToSerial();
  //Serial.println(freeRam());   // Veeeeeeeery handig!
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

void clearBufferArray88(char * buffer, int counter)              // function to clear buffer array
{
  for (int i=0; i<counter;i++)
  { 
    buffer[i]=NULL;
  }                  // clear all index of array with command NULL
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


