
/*
ic 4514
chip a is the top chip
white is ground, red is 5V
Light on 0
 */  

 

int a0 = 6; //orange wire
int a1 = 7; //yellow
int a2 = 2; //green
int a3 = 3; //blue
int aOutput = 4; //grey
int aLatch = 5; //purple

int b0 = 8;
int b1 = 9;
int b2 = 10;
int b3 = 11;
int bOutput = 12;
int bLatch = 1;

int NumColumns = 9;
int bin[4];

byte columnStates[9][32] = { {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},{0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},{1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0},{1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0},{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
                            {1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0},{1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1}
                            
                          };


void setup(){
  
  pinMode(a0, OUTPUT);    
  pinMode(a1, OUTPUT);    
  pinMode(a2, OUTPUT); 
  pinMode(a3, OUTPUT);   
  pinMode(aOutput, OUTPUT);    // common pin 
  pinMode(aLatch, OUTPUT);
  pinMode(b0, OUTPUT);    
  pinMode(b1, OUTPUT);    
  pinMode(b2, OUTPUT); 
  pinMode(b3, OUTPUT);   
  pinMode(bOutput, OUTPUT);    // common pin 
  pinMode(bLatch, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  
  for (int adrs2 = 0; adrs2 <= 31; adrs2++){  //turn on each LED 
      lightLED(adrs2, 0);
      delay(100);
      for (int adrs = 0; adrs <= 31; adrs++){  
      lightLED(adrs, 1); //turn off all LEDs
      }
  }
        for (int adrs2 = 0; adrs2 <= 31; adrs2++){  //turn on each LED 
      lightLED(adrs2, 0);
      delay(50);
      for (int adrs = 0; adrs <= 31; adrs++){  
      lightLED(adrs, 1); //turn off all LEDs
      }
  }
}

 

void loop () {

  for (int adrs = 0; adrs <= 31; adrs++){  
      lightLED(adrs, 1); //turn off all LEDs
  }
  delay(1000);
//  for (int adrs2 = 0; adrs2 <= 31; adrs2++){  //turn on each LED 
//      lightLED(adrs2, 0);
//      delay(150);
//      for (int adrs = 0; adrs <= 31; adrs++){  
//      lightLED(adrs, 1); //turn off all LEDs
//      }
//  }
  
    
  for (int n = 0; n < NumColumns; n++){ 
    myDelay(1000, n); //parameter is number of milliseconds to keep column on
  }
  
}

void myDelay(unsigned long duration, unsigned long columnNum ){
  unsigned long start = millis(); //duration the frame should stay on
  Serial.println("start new column: " );
  Serial.println(columnNum );
  while (millis() - start <= duration){
    
    for (int adrs = 0; adrs <= 31; adrs++){  
      byte tstate = columnStates[columnNum][adrs];  
      lightLED(adrs, tstate); //pass the led number and the corresponding state it should be 
      //delay(1); //otherwise the light bleeds
      lightLED(adrs, 1); //turn off led 
       
    }
    for (int adrs = 0; adrs <= 31; adrs++){  
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
    
//    Serial.print( dec);
//    Serial.print(" ----> ");
//    Serial.print(w );
//    Serial.print(x );
//    Serial.print(y );
//    Serial.print(z );
//    Serial.print(" is ");
    
    if (dec <= 15){
      digitalWrite(bLatch, LOW);
      digitalWrite(aLatch, HIGH);
      digitalWrite(a0,z);
      digitalWrite(a1,y);
      digitalWrite(a2,x);
      digitalWrite(a3,w);
      digitalWrite(aOutput, state);
//      Serial.println(" sent to top. ");
    } else if (dec > 15) {
      digitalWrite(bLatch, HIGH);
      digitalWrite(aLatch, LOW);
      digitalWrite(b0,z);
      digitalWrite(b1,y);
      digitalWrite(b2,x);
      digitalWrite(b3,w);
      digitalWrite(bOutput, state);
//      Serial.println(" sent to bottom. ");
    }
    dec = 0;
//    digitalWrite(tempOutput, state); //send 0 to make the selected pin HIGH
    
     
}

void decToBinary( byte dec ){
    bin[3] = dec%2;
    bin[2] = (dec>>1)%2;
    bin[1] = (dec>>2)%2;
    bin[0] = (dec>>3)%2;
}

