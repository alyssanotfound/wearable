#include <Process.h>

int led = 13;
String txt; 
void setup()
{
  Bridge.begin();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
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
  
  String bufferdata;
  
  while (p.available()>0) {
    char c = p.read();
    if (c == '*'){             //astrick will be at the start of the text file
      for(int lth = 0; lth < 3960; lth++){
        for (int ct = 0; ct < 1; ct++){ //don't keep first char bc it is a comma
          char d = p.read();
        }
        for (int ct = 0; ct < 65; ct++){ //length of data for one frame
          char e = p.read();
          bufferdata += e;
        }
        goThruBuffer(bufferdata);
        bufferdata = "";
      }
    }
  }
}

void goThruBuffer(String currentBlock ){
  Serial.println();
  Serial.print(" new section: ");
  Serial.print( currentBlock );
  Serial.flush();
}



