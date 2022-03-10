#include <DHTStable.h>
#include <DHT.h>
#define DHT11_PIN 19
#define DHTTYPE DHT11 

int TEMPERATURA;
DHT dht(DHT11_PIN, DHTTYPE);

void setupTemperatura(){
    Serial.begin(115200);
    dht.begin();
}

int sensorTemperatura(){ 
      TEMPERATURA = dht.readTemperature();
      delay(2000);
      return TEMPERATURA;
}
