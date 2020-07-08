#include <AdafruitIO_Feed.h>
#include "config.h"
#include "AdafruitIO_WiFi.h"
#include <AdafruitIO_WiFi.h>

#define IO_USERNAME "WildeBeast1"
#define IO_KEY "c237917102c44d868020217958eff9ec"
#define WIFI_SSID "Aniket"
#define WIFI_PASS "Paluani98"

const int Alcohol= 16;
 int zc1 = 5; // IR Sensor at Zebra Crossing
 int IR_zc2 = 4; // IR Sensor at Zebra Crossing
const int MQ2_Gas = 0;
const int Flame = 2;
const int SOS = 14; // Emergency Button
const int LED_ZC = 12; // Zebra Crossing
  


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(zc1, INPUT);
  pinMode(IR_zc2, INPUT);
  pinMode(MQ2_Gas, INPUT);
  pinMode(Flame , INPUT);
  pinMode(Alcohol, INPUT);  
  pinMode(SOS, INPUT);
  pinMode(LED_ZC, OUTPUT);

  // connect to io.adafruit.com
 while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
}
}
void loop()
{
  // put your main code here, to run repeatedly:
   io.run();

   // IR ZC Code
   
int varZC= digitalRead(4);

if(digitalRead(5)== 0 || digitalRead(4)== 0)
{
  digitalWrite(LED_ZC,HIGH);
 delay(3000);
}
else
{
  digitalWrite(LED_ZC,LOW);
}
// Flame Sensor
AdafruitIO_Feed *Flame = io.feed("Flame");
String currentF="Flame Detected";
  int varF = digitalRead(2);
if(digitalRead(2)== 0)
{
  digitalWrite(8,HIGH);
  Flame->save(currentF);
  Serial.println(currentF);
}
else
{
  digitalWrite(8,LOW);
}

//mq2code
AdafruitIO_Feed *MQ2 = io.feed("MQ2");
String currentM="Gas Detected";
int varM = analogRead(0);
  delay(200);

if(analogRead(0)>300)
{
  digitalWrite(8,HIGH);
    Serial.println(currentM);
  delay(1000);
  MQ2->save(currentM);
}
else
{
  digitalWrite(8,LOW);
  Serial.println(varM);
  delay(1000);
  
}
//alcoholcode
AdafruitIO_Feed *Alcohol = io.feed("Alcohol");
String currentA= "Alcohol Detected in the vehicle";
 int varA = digitalRead(16);
  delay(200);
if(digitalRead(16)<1)
{
  digitalWrite(8,HIGH);
  Serial.println(varA);
  delay(1000);
  Alcohol->save(currentA);
    Serial.println(currentA);
}
else
{
  digitalWrite(8,LOW);
  Serial.println(varA);
  delay(1000);
  
}

//LDR

/*if(analogRead(A0)>1020)
{
  digitalWrite(10, HIGH);
  Serial.println(analogRead(A0));
}
else
{
  digitalWrite(10, LOW);
  Serial.println(analogRead(A0));
}
*/

}
