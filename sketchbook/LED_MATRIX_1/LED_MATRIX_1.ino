// 2-dimensional array of row pin numbers:
const int rownum[8] = {
22,23,24,25,50,51,52,53 };
// 2-dimensional array of column pin numbers:
const int colnum[8] = {
31,30,33,32,35,34,37,36};

float timeCount = 0;

int h[8][8] = {
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,1,1,1,1,0},
{0,0,1,1,1,1,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0}};

int e[8][8] = {
{0,0,1,1,1,1,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,1,1,1,0},
{0,0,0,0,1,1,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,1,1,1,1,1,0}};

int l[8][8] = {
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,1,0},
{0,0,1,1,1,1,1,0}};

int o[8][8] = {
{0,0,0,1,1,1,0,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,1,0,0,0,1,0},
{0,0,0,1,1,1,0,0}};

int smile[8][8] = {
{0,0,0,0,0,0,0,0},
{0,1,1,0,0,1,1,0},
{0,1,1,0,0,1,1,0},
{0,1,1,0,0,1,1,0},
{0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,1,0},
{0,0,1,0,0,1,0,0},
{0,0,0,1,1,0,0,0}};

int blank[8][8] = {
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}};

void setup()

{


// iterate over the pins:
for (int thisPin = 0; thisPin < 8; thisPin++) {
// initialize the output pins:
pinMode(colnum[thisPin], OUTPUT);
pinMode(rownum[thisPin], OUTPUT);
// take the col pins (i.e. the cathodes) high to ensure that
// the LEDS are off:
digitalWrite(colnum[thisPin], LOW);
digitalWrite(rownum[thisPin], HIGH);
}

}

void loop() {
// This could be rewritten to not use a delay, which would make it appear brighter
delay(5);
timeCount += 1;
if(timeCount < 200) {
drawScreen(h);
} else if (timeCount < 230) {
// do nothing
} else if (timeCount < 400) {
drawScreen(e);
} else if (timeCount < 430) {
// nothing
} else if (timeCount < 600) {
drawScreen(l);
} else if (timeCount < 630) {
// nothing
} else if (timeCount < 800) {
drawScreen(l);
} else if (timeCount < 830) {
// nothing
} else if (timeCount < 1000) {
drawScreen(o);
} else if (timeCount < 1030) {
// nothing
} else if (timeCount < 1200) {
drawScreen(smile);
} else if (timeCount < 1230) {
// nothing
} else {
// back to the start
timeCount = 0;
}
}

int row(int i) {
if(i == 1) {
return 22;
} else if (i == 2) {
return 23;
} else if (i == 3) {
return 24;
} else if (i == 4) {
return 25;
} else if (i == 5) {
return 50;
} else if (i == 6) {
return 51;
} else if (i == 7) {
return 52;
} else if (i == 8) {
return 53;
}
}

int col(int i) {
if(i == 1) {
return 31;
} else if (i == 2) {
return 30;
} else if (i == 3) {
return 33;
} else if (i == 4) {
return 32;
} else if (i == 5) {
return 35;
} else if (i == 6) {
return 34;
} else if (i == 7) {
return 37;
} else if (i == 8) {
return 36;
}
}

void drawScreen(int character[8][8]) {
for(int j = 0; j < 8; j++) {
// Turn the row on
int rowNumber = j + 1;
digitalWrite(row(rowNumber), LOW);
for (int k = 0; k < 8; k++) {
// draw some letter bits
int columnNumber = k + 1;
if(character[j][k] == 1) {
digitalWrite(col(columnNumber), HIGH);
}

digitalWrite(col(columnNumber), LOW);
}
digitalWrite(row(rowNumber), HIGH);
}
}

