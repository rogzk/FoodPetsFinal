//Definicion de pines sensor distancia.
const int Trigger = 13;
const int Echo = 12;

void setupDistancia() {
  Serial.begin(115200);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
}

  
long sensorDistancia() {

     long t, d;
  
     digitalWrite(Trigger, HIGH);
     delayMicroseconds(10);
     digitalWrite(Trigger, LOW);
  
     t = pulseIn(Echo, HIGH);
     d = t/59;
  
     Serial.print("Distancia: ");
     Serial.print(d);
     Serial.print(" cm");
     Serial.println();
     delay(100);
      
     return d;
}
