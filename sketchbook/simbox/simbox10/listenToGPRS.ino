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

