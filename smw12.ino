#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
//#include <SimpleTimer.h>
 
char auth[] = "T2E3dAvGh0GSQ2NivcYt2BIhTb6J-xaC";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "virus";
char pass[] = "Password";
 
BlynkTimer timer;

WidgetLED green(V1);
WidgetLED yellow(V2);
WidgetLED orange(V3);
WidgetLED red(V4);

String myString; 
char rdata;

int firstVal, secondVal,thirdVal; 

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
 
    timer.setInterval(1000L,UltrSens); 
    //timer.setInterval(1000L,UltrSens); 
 
}
 
void loop()
{

   if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
   }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {

String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2); 
 
 
firstVal = l.toInt();
secondVal = m.toInt();//No use
thirdVal = n.toInt();//No use
 
  myString = "";
// end new code
    }
  }
 
}
 
void UltrSens()
{
  int sdata = firstVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  Blynk.virtualWrite(V22, sdata); //V22 Pin is for debugging of Ultrasonic Sensor's Data

  if (sdata>=75){
    green.on();
    yellow.off();
    orange.off();
    red.off();
  }
  else if (sdata<75 and sdata>=50){
    green.on();
    yellow.on();
    orange.off();
    red.off();
  }
  else if (sdata<50 and sdata>=25){
    green.on();
    yellow.on();
    orange.on();
    red.off(); 
  }
  else if (sdata<25){
    green.on();
    yellow.on();
    orange.on();
    red.on() ;
  }
  else{
    green.off();
    yellow.off();
    orange.off();
    red.off();
  }
}

/*void sensorvalue2()
{
int sdata = secondVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, sdata);
 
}*/
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
