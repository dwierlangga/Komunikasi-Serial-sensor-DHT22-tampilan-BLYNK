#include <DHT.h>
#define DHTPIN D2
#define DHTTYPE DHT22

DHT dht (DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  String request = "";
  while(Serial.available()>0){
    request +=char(Serial.read());
  }
  request.trim();

  if(request == "Yes"){
    sendData();
  }
  request = "";
  delay(1000);
}

void sendData(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  String dataSend = String(t) + "#" + String(h);
  Serial.println(dataSend);
}
