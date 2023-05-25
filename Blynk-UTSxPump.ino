/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#define BLYNK_TEMPLATE_ID "TMPL6JiVnzXqj"
#define BLYNK_TEMPLATE_NAME "IkanDalamEmber"
#define BLYNK_WIFI_SSID "Yukibara-Hotspot"
#define BLYNK_WIFI_PASS "12345678"


#define BLYNK_AUTH_TOKEN "ri36e-roOPUv3MJ5dbziAJ5oSurKLlk4"


//clone from DHT
#include "BlynkEdgent.h"



// clone from ultrasonic file
#include <Ultrasonic.h>
Ultrasonic ultrasonic(5, 4);
int distance;
const int RELAY_PIN = 12; 
BlynkTimer timer;

void sendSensor(){
  distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  if (distance < 10 ) {digitalWrite(RELAY_PIN, HIGH);
    Blynk.logEvent("pompa", String("Ketinggian air saat ini ") + distance + String("cm"));
    }
  else {digitalWrite(RELAY_PIN, LOW);}
  Blynk.virtualWrite(V0, distance);


}

void setup(){
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  BlynkEdgent.begin();
  delay(500);
  timer.setInterval(500L, sendSensor); 
}



void loop() {
  BlynkEdgent.run();
  timer.run();
}

