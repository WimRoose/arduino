int SER_Pin = 23;   //pin 14 on the 75HC595
int RCLK_Pin = 22;  //pin 12 on the 75HC595
int SRCLK_Pin = 24; //pin 11 on the 75HC595

//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];
float timeCount = 0;
void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


  //reset all register pins
  clearRegisters();
  //writeRegisters();
}               


//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}


void loop(){

  timeCount += 1;
if(timeCount < 10000) {
digitalWrite(RCLK_Pin, LOW);
  
    digitalWrite(SRCLK_Pin, LOW);

    digitalWrite(SER_Pin, HIGH);
    digitalWrite(SRCLK_Pin, HIGH);
    
  digitalWrite(RCLK_Pin, HIGH);
} else if (timeCount < 12000) {
// do nothing
} else if (timeCount < 20000) {
digitalWrite(RCLK_Pin, LOW);

  
    digitalWrite(SRCLK_Pin, LOW);

    digitalWrite(SER_Pin, LOW);
    digitalWrite(SRCLK_Pin, HIGH);
   

  
  digitalWrite(RCLK_Pin, HIGH);
} else if (timeCount < 22000) {
// do nothing

} else {
// back to the start
timeCount = 0;
}
}


