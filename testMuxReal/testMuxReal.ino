
/*

test mux with regular leds
there are 8 leds per mux

 */  

 

int a0 = 2;
int a1 = 3;
int a2 = 4;
int output = 7;
int bin[3];
long previousMillis;

int columnStates[4][8] = { {0,1,1,1,1,0,1,0}, {0,0,0,0,1,0,1,0}, {0,1,0,1,0,0,1,0},{0,0,0,1,0,0,0,0} };


void setup(){
  
  pinMode(a0, OUTPUT);    
  pinMode(a1, OUTPUT);    
  pinMode(a2, OUTPUT);    
  pinMode(output, OUTPUT);    // common pin 
  
  Serial.begin(9600);
  
}

 

void loop () {
  for (int n = 0; n <= 3; n++){ //first bracket number of columnStates
    myDelay(2000, n); //parameter is number of milliseconds to keep column on
  }
}

void myDelay(unsigned long duration, unsigned long columnNum ){
  unsigned long start = millis();
  while (millis() - start <= duration){
    for (int adrs = 0; adrs <= 7; adrs++){  
      int tstate = columnStates[columnNum][adrs];  
      lightLED(adrs, tstate); //pass the led number and the corresponding state it should be 
      
      Serial.print(tstate);
    }
  }
  for (int adrs = 0; adrs <= 7; adrs++){  
      lightLED(adrs, 0); //turn all lights off in between frames
  }
  delay(1000);
  
}


void lightLED(int dec, int state){

    decToBin(dec);
    int x = bin[0];
    int y = bin[1];
    int z = bin[2];
    
    digitalWrite(a0,z);
    digitalWrite(a1,y);
    digitalWrite(a2,x);

    digitalWrite(output, state);
    
    bin[0] = 0;
    bin[1] = 0;
    bin[2] = 0; 
}


void decToBin( int dec ){
  
  if (dec == 0){
    bin[0] = 0;
    bin[1] = 0;
    bin[2] = 0;
  } else if (dec == 1){
    bin[0] = 0;
    bin[1] = 0;
    bin[2] = 1;
  } else if (dec == 2){
    bin[0] = 0;
    bin[1] = 1;
    bin[2] = 0;
  } else if (dec == 3){
    bin[0] = 0;
    bin[1] = 1;
    bin[2] = 1;
  } else if (dec == 4){
    bin[0] = 1;
    bin[1] = 0;
    bin[2] = 0;
  } else if (dec == 5){
    bin[0] = 1;
    bin[1] = 0;
    bin[2] = 1;
  } else if (dec == 6){
    bin[0] = 1;
    bin[1] = 1;
    bin[2] = 0;
  } else if (dec == 7){
    bin[0] = 1;
    bin[1] = 1;
    bin[2] = 1;
  } 
}

