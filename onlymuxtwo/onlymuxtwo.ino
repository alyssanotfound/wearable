
/*
ic 4514
only using bottom chip bc top one is dim
white is ground, red is 5V
Light on 0
 */  

int b0 = 8; //orange wire
int b1 = 9; //yellow
int b2 = 10; //green
int b3 = 11; //blue
int bOutput = 12; //grey
int bLatch = 1; //purple

int NumColumns = 4;
int bin[4];

byte columnStates[4][16] = { {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1}
                            };


void setup(){
  pinMode(b0, OUTPUT);    
  pinMode(b1, OUTPUT);    
  pinMode(b2, OUTPUT); 
  pinMode(b3, OUTPUT);   
  pinMode(bOutput, OUTPUT);    // common pin 
  pinMode(bLatch, OUTPUT);
  Serial.begin(9600);
  digitalWrite(bLatch, HIGH);
}

 

void loop () {

  for (int adrs = 0; adrs <= 15; adrs++){  
      lightLED(adrs, 1); //turn off all LEDs
  }

  for (int adrs2 = 0; adrs2 <= 15; adrs2++){  //turn on each LED 
      lightLED(adrs2, 0);
      delay(100);
  }
//  for (int n = 0; n < NumColumns; n++){ 
//    myDelay(100, n); //parameter is number of milliseconds to keep column on
//  }
  
}

void myDelay(unsigned long duration, unsigned long columnNum ){
  unsigned long start = millis(); //duration the frame should stay on
  while (millis() - start <= duration){
    Serial.println("start new column: " );
    Serial.println(columnNum );
    for (int adrs = 0; adrs <= 15; adrs++){  
      byte tstate = columnStates[columnNum][adrs];  
      lightLED(adrs, tstate); //pass the led number and the corresponding state it should be 
      delay(1); //otherwise the light bleeds
      lightLED(adrs, 1); //turn off led 
       
    }
    for (int adrs = 0; adrs <= 15; adrs++){  
      lightLED(adrs, 1); //turn all lights off
      }
  } 
}


void lightLED(int dec, byte state){
    decToBinary(dec); 
    byte w = bin[0];
    byte x = bin[1];
    byte y = bin[2];
    byte z = bin[3];
    
    digitalWrite(b0,z);
    digitalWrite(b1,y);
    digitalWrite(b2,x);
    digitalWrite(b3,w);
    digitalWrite(bOutput, state);
    dec = 0;
}

void decToBinary( byte dec ){
    bin[3] = dec%2;
    bin[2] = (dec>>1)%2;
    bin[1] = (dec>>2)%2;
    bin[0] = (dec>>3)%2;
}

