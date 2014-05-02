//combo of HIGH white and LOW black will light LED

const int whiteAnode[] = { 2, 3, 4, 5, 6};
const int blackCathode[]   = { 8,9,10,11,12};
long intrvl = 100; // interval at which to do something (milliseconds)
int list[] ={};
void turnOnByBinary(int s[]);
int pixels[100][5] = {  
   {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,1,1,0},{0,1,1,1,0},{0,1,1,1,0},{0,1,1,1,0},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1},{0,1,1,1,1}
};
long numOfRows = sizeof(pixels)/10;

void setup() {
  Serial.begin(4800);
  for (int i = 0; i < 5; i++){
    pinMode(whiteAnode[i], OUTPUT);  
    pinMode(blackCathode[i], OUTPUT);
  } 
}

void loop() {  
resetPins();
//go thru each row of pixel data 
for(int l=0; l< numOfRows; l++){
  int list[] = {0};
  //create local list from pixel data row
  for(int j = 0; j<5;j++){
    list[j] = pixels[l][j];
  }
  //use list to turn on those leds for certain amount of time
  turnOnByBinary(list, intrvl);
//  for(int k = 0; k<5; k++){
//    Serial.println(list[k]);
//  }
//  Serial.println("  ");
}
}

void turnOnByBinary(int r[], unsigned long intrvl){  
    setBlackLow();
    unsigned long start = millis();
    while (millis() - start <= intrvl){
      //really quickly, loop thru each element and flash it (the row) on 
      for (int i = 0; i < 5; i++){
        if (r[i] == 1){
          digitalWrite(whiteAnode[i], HIGH);
          digitalWrite(whiteAnode[i], LOW);
        }
      }  
    }
    
    resetPins();
}


void resetPins() {
  for (int pin = 0; pin < 5; pin++){
    digitalWrite(whiteAnode[pin], LOW);
    digitalWrite(blackCathode[pin], HIGH);
  }
}

void setBlackLow() {
  for (int pin = 0; pin < 5; pin++){
    digitalWrite(blackCathode[pin], LOW);
  }
}


