#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D1
#define ECHOPIN    D2

char auth[] = " mBXyurjnoLfsnReQpS8YCvnQouemzzDW";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wifi";
char pass[] = "password123";

int thresh[3] = {7, 14, 25};

WidgetLCD lcd(V1);
WidgetLED green(V2);
WidgetLED orange(V3);
WidgetLED red(V4);

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
}

void loop()
{
  lcd.clear();
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm");
  lcd.print(7, 1, distance);
  Blynk.run();
  if(distance<=thresh[0]){
    green.off();
    orange.off();
    red.on();
    }
  else if(distance<=thresh[1] and distance>thresh[0]){
    green.off();
    orange.on();
    red.off();
  }
  else if(distance<=thresh[2] and distance>thresh[1]){
    green.on();
    orange.off();
    red.off();
    
  }
  else{
    green.off();
    orange.off();
    red.off();
  //delay(100);
}

  delay(3500);

}
