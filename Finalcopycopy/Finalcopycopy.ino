/*
combine WebToYun with Mux code

ic 4514
chip a is the top chip
white is ground, red is 5V
Light on 0
 */ 
 
#include <Process.h>
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
int b;

int bin[4];
String bufferdata;
String giantstring;

void setup()
{
  Bridge.begin();
  Serial.begin(9600);
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

//  //test lights
  for (int adrs2 = 0; adrs2 <= 31; adrs2++){  //turn on each LED 
    lightLED(adrs2, 0);
    delay(150);
  }
  for (int adrs = 0; adrs <= 31; adrs++){  
    lightLED(adrs, 1); //turn off all LEDs
  }

}

void loop()
{
  runCurl();
}

void runCurl() {
  Process p;  

  p.begin("curl"); 
  
  p.addParameter("http://ledshirt.herokuapp.com/textfiles/LEDShirt_test.txt"); 
  
  p.run();
  
  
  //store giant string of data
  while (p.available()>0) {
    char c = p.read();
    //if (c == '*'){             //astrick will be at the start of the text file
      for(int a=0; a<600; a++){
        //how many chars to skip?
        //Serial.println("what block ");
        //Serial.println(a);
        for (int ctt = 264*a; ctt < 264+264*a; ctt++){ //264 for 8*33 bc of commas
        //Serial.println("skip these ");
        //Serial.println(320*a);
        //Serial.println("to ");
        //Serial.println(320+320*a);
        char e = p.read();
        } 
       for (int cth = 0; cth < 264; cth++){ 
        char e = p.read();
        giantstring += e;
       } 
       processString(giantstring);
     }       
  }
}

void processString(String giant){
  Serial.println(giant);
  for(int i=0; i<10;i++){
       String tempb = giantstring.substring(33*i,32+33*i);
       Serial.println(tempb);
       myDelay(500, tempb);
       tempb = "";
     }
  giantstring = "";
}

void myDelay(unsigned long duration, String framedata ){

  unsigned long start = millis(); //duration the frame should stay on 
  //Serial.println(framedata);
  while (millis() - start <= duration){
    
    for (int adrs = 0; adrs <= 31; adrs++){  
      char tstate = framedata.charAt(adrs);  
      //Serial.println(tstate);
      lightLED(adrs, tstate); //pass the led number and the corresponding state it should be 
      //delay(1); //otherwise the light bleeds
      lightLED(adrs, 1); //turn off led 
       
    }
//    for (int adrs = 0; adrs <= 31; adrs++){  
//      lightLED(adrs, 1); //turn all lights off
//    }

  }
  Serial.flush();
//  bufferdata = "";
}


void lightLED(int dec, char state){
    uint8_t hl;
    //Serial.println(state);
    if(state == '0'){
      hl = LOW;
      //Serial.println("go low ");
    } else if(state == '1'){
      hl = HIGH;
      //Serial.println("go high ");
    }
    
    decToBinary(dec);
    
    byte w = bin[0];
    byte x = bin[1];
    byte y = bin[2];
    byte z = bin[3];

    if (dec <= 15){
      digitalWrite(bLatch, LOW);
      digitalWrite(aLatch, HIGH);
      digitalWrite(a0,z);
      digitalWrite(a1,y);
      digitalWrite(a2,x);
      digitalWrite(a3,w);
      digitalWrite(aOutput, hl);
//      Serial.print("light ");
//      Serial.println(dec);
      
    } else if (dec > 15) {
      digitalWrite(bLatch, HIGH);
      digitalWrite(aLatch, LOW);
      digitalWrite(b0,z);
      digitalWrite(b1,y);
      digitalWrite(b2,x);
      digitalWrite(b3,w);
      digitalWrite(bOutput, hl);
//      Serial.print("light ");
//      Serial.println(dec);
    }
    dec = 0;   
}

void decToBinary( byte dec ){
    bin[3] = dec%2;
    bin[2] = (dec>>1)%2;
    bin[1] = (dec>>2)%2;
    bin[0] = (dec>>3)%2;
}


