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
              
        if (c == '\n') { // line feed: commando ontvangen!
         
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
             //sendEmail("404# received");
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
            
            for (int i=0;i<cc;i++) {
              client.println(telefoonNrs[i]);
            }
            sendNrsByEmail(telefoonNrs);
            //sendEmail("#END received");
            cc=0;
            b=0;
            break;
          
          }
          else if (strcmp (bufferWEB, "#READ\r\n") == 0)  {
         
            client.println("****** BEGIN WEBSERVER ******");
            client.println("#READ received");
            client.println("****** END WEBSERVER ******");
            
            for (int i=0;i<1024;i++) {
              
              eepromIntValue = EEPROM.read(i);
              if (eepromIntValue < 255) {  // EEPROM-locaties die nog nooit beschreven zijn hebben de waarde 255
                  eepromValue = (char)eepromIntValue;
                  
                  client.print(eepromValue);
                  delay(50);
                  if ((i+1) % 10 == 0 && i > 0) {
                    client.print("\n");
                  }
              }
            }
            //sendNrsByEmail(telefoonNrs);
            
            //sendEmail("#READ received");
            break;
           }
           
           else if (b=0)  {
           
            client.println("**BEGIN WEBSERVER **");
            client.println("Blablabla!");
            client.println("** END WEBSERVER **");
            //clearBufferArray3();
            //countWEB=0;
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
                      
           }
           clearBufferArray88(bufferWEB, countWEB);
           countWEB=0;
          }      
                       
      }
    }
    clearBufferArray88(bufferWEB, countWEB);
            countWEB=0;
    // give the web browser time to receive the data
    delay(100);
    // close the connection:
    client.stop();
    
    
  }
}
