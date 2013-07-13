#include <HMC58X3.h>
#include <Wire.h>
#include <Servo.h> 
 
Servo myservo;

//timer interrupts
//by Amanda Ghassaei
//June 2012
//http://www.instructables.com/id/Arduino-Timer-Interrupts/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

//timer setup for timer0, timer1, and timer2.
//For arduino uno or any board with ATMEL 328/168.. diecimila, duemilanove, lilypad, nano, mini...

//this code will enable all three arduino timer interrupts.
//timer0 will interrupt at 2kHz
//timer1 will interrupt at 1Hz
//timer2 will interrupt at 8kHz

//storage variables
int i = 0;
int E1 = 5;  
int M1 = 4;
int E2 = 6;
int M2 = 7;


boolean toggle0 = 0;
boolean toggle1 = 0;
boolean toggle2 = 0;
int x_pos=0;
int y_pos=0;

char mstat;
char mx;
char my;
  
int minx=1000;
int maxx=-1000;
int miny=1000;
int maxy=-1000;
  
 
int speedx, speedy; 
boolean RIJ;
boolean STIFT;
int FINALHEADING;
int ANGLE;
int ENDPOINT;

//int speeds[5] = {0,50,100,170,255};
  
#define FWD HIGH
#define BACKWD LOW

unsigned long sensorTimer;
unsigned long motorTimer;
float heading;
int t1;
int calibratex;int calibratey;

HMC58X3 magn;

void setup(void){
  
  //set pins as outputs
  pinMode(13, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT); 
  
  Wire.begin();
  Serial.begin(9600);
  Serial.print("starting");
  mouse_init();
  myservo.attach(12);
  
  // no delay needed as we have already a delay(5) in HMC5843::init()
  magn.init(false); // Dont set mode yet, we'll do that later on.
  // Calibrate HMC using self test, not recommended to change the gain after calibration.
  magn.calibrate(1, 32); // Use gain 1=default, valid 0-7, 7 not recommended.
  // Single mode conversion was used in calibration, now set continuous mode
  magn.setMode(0);
  
  
  motor(1,FWD,50);
  motor(2,BACKWD,50);
  
  Serial.print("calibrating:  ");
  
  t1=millis();
  
  while (millis() - t1 < 5000) {
    delay(10);
    getKompas();
  }
  
      
      Serial.print(calibratex);
      Serial.print(" - ");
      Serial.println(calibratey);

  calibratex=(maxx+minx)/2;
  calibratey=(maxy+miny)/2;
  
      Serial.print("calibrated:  ");
      Serial.print(calibratex);
      Serial.print(" - ");
      Serial.print(calibratey);

  motor(1,FWD,0);
  motor(2,BACKWD,0);
  
  myservo.write(80);
  delay(1000);
  //myservo.write(92);
  delay(500);
  myservo.write(80);
  //myservo.write(92);
  
  
  
  fetch_instr();
    
}//end setup

void loop(){

//  motor(int m, int d, int s) {
  
  if(millis() - sensorTimer > 50 ) {
      sensorTimer = millis();
     
      leesMuis();
      getKompas();
/*           
      Serial.print("x: ");
      Serial.print(x_pos);
      Serial.print(" y: ");
      Serial.print(y_pos);
      
      Serial.print(" max x:");
  Serial.print(maxx);
  Serial.print(" min x:");
  Serial.print(minx);

  Serial.print(" max y:");
  Serial.print(maxy);
  Serial.print(" min y:");
  Serial.print(miny);
  
  
      Serial.print(" Heading: ");
      Serial.println(heading );     
*/
  }
  
  if ((millis() - motorTimer > 100 ) && (RIJ < 2)) {  // 
    
    if (RIJ = 1) {
        Serial.println("Ready to drive");
        Serial.println(x_pos);
        Serial.println(ENDPOINT);
        bijsturen_via_heading();
    }
    //if (RIJ = 0) {draai();}
    //if (((RIJ=1) && (x_pos > ENDPOINT)) || ((RIJ=0) && (heading=FINALHEADING))) {
    
    
    //motor(1,FWD,0);
    //motor(2,FWD,0);
    //myservo.write(80);
    //fetch_instr();
    


  }
    //if (RIJ=2) {
    
      //motor(1,FWD,0);
      //motor(2,FWD,0);
      
    //}
      
  //}
   
  
}


void motor(int m, int d, int s) {
  
  if (m == 1) {
    digitalWrite(M1, d);
    analogWrite(E1,s);
  }

  if (m == 2) {
    digitalWrite(M2, d);
    analogWrite(E2,s);
  }

}


void bijsturen_via_sensor(){
  
  if (x_pos < y_pos) {
      speedx=speedx+1;
      speedy=speedy-1;
    } 
  
    if (x_pos > y_pos) {
      speedx=speedx-1;
      speedy=speedy+1;
    }
    
    if (speedx > 255) speedx = 255;   if (speedx < 0) speedx = 0;
    if (speedy > 255) speedy = 255;   if (speedy < 0) speedy = 0;
  
   motor(1,FWD,speedx);
   motor(2,FWD,speedy);
   
}

void bijsturen_via_heading(){
  Serial.print("Final heading: ");
  Serial.println(FINALHEADING);
  Serial.print("Heading: ");
  Serial.println(heading);
  if (FINALHEADING > heading) {
      speedx=speedx+1;
      speedy=speedy-1;
  } 
  
    if (FINALHEADING < heading) {
      speedx=speedx-1;
      speedy=speedy+1;
    }
    
    if (speedx > 255) speedx = 255;   if (speedx < 0) speedx = 0;
    if (speedy > 255) speedy = 255;   if (speedy < 0) speedy = 0;
  
   motor(1,FWD,speedx);
   motor(2,FWD,speedy);
   
}
void draai(){
  
  int v = heading - FINALHEADING;
  if (v < 0) {v += 360;}
  if (v > 180) {v -= 360;}
  Serial.println(v);
  
  if (ANGLE < 0) {  //naar links
      speedx=128 * (v/10);
      speedy=128 * (v/10);
      if (speedx > 255) speedx = 255;   if (speedx < 25) speedx = 25;
      if (speedy > 255) speedy = 255;   if (speedy < 25) speedy = 25;
  
      motor(1,FWD,speedx);
      motor(2,BACKWD,speedy);
  } 
  
  if (ANGLE > 0) { // naar rechts
      speedx=128 * (v/10);
      speedy=128 * (v/10);
      if (speedx > 255) speedx = 255;   if (speedx < 0) speedx = 25;
      if (speedy > 255) speedy = 255;   if (speedy < 0) speedy = 25;
  
      motor(1,BACKWD,speedx);
      motor(2,FWD,speedy);
    }
    
    
   
}




