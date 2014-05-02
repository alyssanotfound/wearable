
/*

ic 4514

 */  

 

int a0 = 6;
int a1 = 7;
int a2 = 2;
int a3 = 3;
int aOutput = 4;
int aLatch = 1;

int b0 = 8;
int b1 = 9;
int b2 = 10;
int b3 = 11;
int bOutput = 12;
int bLatch = 0;

int NumColumns = 2;
int bin[4];

byte columnStates[2][32] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
  
}

 

void loop () {

  for (int adrs = 0; adrs <= 31; adrs++){  
      lightLED(adrs, 1); //turn all lights off in between frames - 1 is LOW
  }
  
//lightLED(12, 0);
//delay(1000);

  for (int adrs2 = 0; adrs2 <= 31; adrs2++){  
      lightLED(adrs2, 0);
      delay(500);
  }
//  for (int n = 0; n < NumColumns; n++){ 
//    myDelay(1000, n); //parameter is number of milliseconds to keep column on
//  }
  
}

void myDelay(unsigned long duration, unsigned long columnNum ){
  unsigned long start = millis();
  

  while (millis() - start <= duration){
    Serial.println("start new column: " );
    Serial.println(columnNum );
    for (int adrs = 0; adrs <= 31; adrs++){  
      byte tstate = columnStates[columnNum][adrs];  
      lightLED(adrs, tstate); //pass the led number and the corresponding state it should be 
      delay(1); //otherwise the light bleeds 
    }
  }
  for (int adrs = 0; adrs <= 31; adrs++){  
      lightLED(adrs, 2); //turn all lights off in between frames - 1 is LOW
  }

  
}


void lightLED(int dec, byte state){

    
    decToBin(dec);
    
    byte w = bin[0];
    byte x = bin[1];
    byte y = bin[2];
    byte z = bin[3];
    
    Serial.print( dec);
    Serial.print(" ----> ");
    Serial.print(w );
    Serial.print(x );
    Serial.print(y );
    Serial.print(z );
    Serial.print(" is ");
    
    if (dec <= 15){
      digitalWrite(bLatch, LOW);
      digitalWrite(aLatch, HIGH);
      digitalWrite(a0,z);
      digitalWrite(a1,y);
      digitalWrite(a2,x);
      digitalWrite(a3,w);
      digitalWrite(aOutput, state);
      Serial.println(" sent to top. ");
    } else if (dec > 15) {
      digitalWrite(bLatch, HIGH);
      digitalWrite(aLatch, LOW);
      digitalWrite(b0,z);
      digitalWrite(b1,y);
      digitalWrite(b2,x);
      digitalWrite(b3,w);
      digitalWrite(bOutput, state);
      Serial.println(" sent to bottom. ");
    }
    dec = 0;
//    digitalWrite(tempOutput, state); //send 0 to make the selected pin HIGH
    
     
}


void decToBin( byte dec ){
  
  if (dec == 0 || dec == 16){
    bin[0] = 0;
    bin[1] = 0;
    bin[2] = 0;
    bin[3] = 0;
  } else if (dec == 1 || dec == 17){
    bin[0] = 0;
    bin[1] = 0;
    bin[2] = 0;
    bin[3] = 1;
  } else if (dec == 2 || dec == 18){
    bin[0] = 0;
    bin[1] = 0;
    bin[2] = 1;
    bin[3] = 0;
  } else if (dec == 3 || dec == 19){
    bin[0] = 0;
    bin[1] = 0;
    bin[2] = 1;
    bin[3] = 1;
  } else if (dec == 4 || dec == 20){
    bin[0] = 0;
    bin[1] = 1;
    bin[2] = 0;
    bin[3] = 0;
  } else if (dec == 5 || dec == 21){
    bin[0] = 0;
    bin[1] = 1;
    bin[2] = 0;
    bin[3] = 1;
  } else if (dec == 6 || dec == 22){
    bin[0] = 0;
    bin[1] = 1;
    bin[2] = 1;
    bin[3] = 0;
  } else if (dec == 7 || dec == 23){
    bin[0] = 0;
    bin[1] = 1;
    bin[2] = 1;
    bin[3] = 1;
  } else if (dec == 8 || dec == 24){
    bin[0] = 1;
    bin[1] = 0;
    bin[2] = 0;
    bin[3] = 0;
  } else if (dec == 9 || dec == 25){
    bin[0] = 1;
    bin[1] = 0;
    bin[2] = 0;
    bin[3] = 1;
  } else if (dec == 10 || dec == 26){
    bin[0] = 1;
    bin[1] = 0;
    bin[2] = 1;
    bin[3] = 0;
  } else if (dec == 11 || dec == 27){
    bin[0] = 1;
    bin[1] = 0;
    bin[2] = 1;
    bin[3] = 1;
  } else if (dec == 12 || dec == 28){
    bin[0] = 1;
    bin[1] = 1;
    bin[2] = 0;
    bin[3] = 0;
  } else if (dec == 13 || dec == 29){
    bin[0] = 1;
    bin[1] = 1;
    bin[2] = 0;
    bin[3] = 1;
  } else if (dec == 14 || dec == 30){
    bin[0] = 1;
    bin[1] = 1;
    bin[2] = 1;
    bin[3] = 0;
  } else if (dec == 15 || dec == 31){
    bin[0] = 1;
    bin[1] = 1;
    bin[2] = 1;
    bin[3] = 1;
  } 
}

