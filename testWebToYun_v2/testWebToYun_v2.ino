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
    //Serial.print(c);
    bufferdata += c;
//    if (c == '*'){
//      break;
//    }
  }
  
  Serial.println();
  
  Serial.print(" buffer: ");
  Serial.print( bufferdata );
  Serial.flush();
  
}
