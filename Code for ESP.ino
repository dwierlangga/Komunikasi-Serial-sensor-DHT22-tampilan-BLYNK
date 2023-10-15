#define BLYNK_TEMPLATE_ID "TMPL66b17SIk_"
#define BLYNK_TEMPLATE_NAME "seral com"
#define BLYNK_AUTH_TOKEN "kNmOE3Te_wFaqI4TvemjXn5qNnq8QE3H"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include<SoftwareSerial.h>

SoftwareSerial dataSerial(12, 13);

unsigned long previousMillis = 0;
const long interval = 3000;

String arrData[2];

#define LED_PIN D2

float temp, hum;

char auth [] = BLYNK_AUTH_TOKEN;
char ssid [] = "0000";
char pass [] = "gantilagi";

void setup() {
  Serial.begin(9600);
  dataSerial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  Blynk.begin (auth, ssid, pass);
  WiFi.begin (ssid, pass);
  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    digitalWrite(LED_PIN, LOW);
  }
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;

    String data = "";
    while(dataSerial.available()>0){
      data += char(dataSerial.read());
    }
    data.trim();

    if(data != ""){
      int index = 0;
      for(int i=0; i<= data.length(); i++){
        char delimiter = '#';
        if(data[i] != delimiter){
          arrData[index] += data[i];
        }
        else{
          index++;
        }
      }

      if(index == 1){
        Serial.println("Temperature : " + arrData[0]);
        Serial.println("Humidity    : " + arrData[1]);
        Serial.println();
      }

      temp = arrData[0].toFloat();
      hum  = arrData[1].toFloat();
      
      arrData[0] = "";
      arrData[1] = "";

      Blynk.run();
      Blynk.virtualWrite(V0, temp);
      Blynk.virtualWrite(V1, hum);
    }

    dataSerial.println("Yes");
  }
}
