#define G 10
#define A 7
#define B 8
#define E 2
#define D 3
#define C 4
#define DP 5
#define F 9


void setup()

{

pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
pinMode(C, OUTPUT);
pinMode(D, OUTPUT);
pinMode(E, OUTPUT);
//pinMode(F, OUTPUT);
pinMode(G, OUTPUT);
pinMode(DP, OUTPUT);

}

void loop ()

{

digitalWrite(A,HIGH);
delay(500);
digitalWrite(A,LOW);
delay(500);
digit8();
delay(1000);

}


