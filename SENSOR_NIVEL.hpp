//Sendor nivel (datos erroneos para ESP32).
const int portPin = 34;
int potValor = 0;

void setupNivel() {
  Serial.begin(115200);
  delay(200);
}

int sensorNivel() {
  potValor = analogRead(portPin);
  Serial.println(potValor);
  delay(200);
  return potValor;
}
