#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "xxx"
#define BLYNK_TEMPLATE_NAME "xxxx"
#define BLYNK_AUTH_TOKEN "xxx"

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DallasTemperature.h>
#include <OneWire.h>

char ssid[] = "xxx";
char pass[] = "xxx";

#define DHTPIN 14 
#define DHTTYPE DHT11
int sensorPin = A0;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
#define ONE_WIRE_BUS 4 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);  

void sensor_DHT(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (h > 100.0) {
    h = 72.0;
  }

  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
}
void sendSuhuAir(){
  sensors.requestTemperatures();          
  float tempAir = sensors.getTempCByIndex(0);
  Serial.print(F("temperatur air: ")); 
  Serial.print(tempAir);
  Blynk.virtualWrite(V3, tempAir);
}
void Turbidity(){
  int sensorValue =analogRead(sensorPin);
  int tempTurbidity = map(sensorValue, 0,1024, 0, 100);
  int turbidity = 100 - tempTurbidity;
  Serial.print(turbidity);
  Blynk.virtualWrite(V4, turbidity);
}


void setup()
{
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  sensors.begin();
  timer.setInterval(500L, sensor_DHT); 
  timer.setInterval(500L, sendSuhuAir);
  timer.setInterval(500L, Turbidity);
}

void loop()
{
  Blynk.run();
  timer.run();
}
