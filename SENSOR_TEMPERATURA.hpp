#include <DHTStable.h>
#include <DHT.h>
#define DHT11_PIN 19
#define DHTTYPE DHT11 

int TEMPERATURA;
int HUMEDAD;

DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(TEMPERATURA);
  Serial.print("  Humedad: ");
  Serial.println(HUMEDAD);
  delay(2000);
}
