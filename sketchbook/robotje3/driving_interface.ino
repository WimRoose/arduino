// 1) draaien of rijden
// 2) hoek
// 3) afstand
// 4) schrijven
// bijv. (DRAAI, 90, 0, 0)
// bijv.  (RIJ, 90, 10, 1)
//boolean RIJ;
//boolean STIFT;
//int HEADING;
//int DIST;


//int iset[3][4]={{1, 0, 100, 1},{0, 90, 0, 0},{2,0,0,0}};
int iset[2][4]={{1, 0, 300, 1},{2,0,0,0}};

//iset[0]= {RIJ, 0, 10, 1};
//iset[1]= {DRAAI, 90, 10, 0};


void fetch_instr() {
Serial.println("fetching instruction...");  
   RIJ=iset[i][0];
   STIFT=iset[i][3];
   Serial.print("RIJ:");
   Serial.println(RIJ);
   if (RIJ=1)  { 
      Serial.println("Setting instructions for driving FW");
     speedx=200;
     speedy=200; // usual drive speed
     FINALHEADING=heading;
     
     ENDPOINT = 10;
   } 
   
   else {
     
     ANGLE = iset[i][1];
     berekenFinalHeading();
     speedx=0;
     speedy=0;
     
   }
  
  
  
   // set distance (of tijd)
   
  i++; 
}

void berekenFinalHeading(){
 
 int h = heading + iset[i][1];  // + of - 90
 if (h < 0) {FINALHEADING = h + 360;} 
 if (h > 360) {FINALHEADING = h - 360;}

}

