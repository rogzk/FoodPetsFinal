//Motor paso a paso
int IN1 = 2;      
int IN2 = 4;      
int IN3 = 5;     
int IN4 = 18;    
int demora = 20;      // demora entre pasos, no debe ser menor a 10 ms.

const int ledPin1 = 25; //Verde = OK.
const int ledPin2 = 26; //Azul = DANGER.

int paso [4][4] =   // matriz (array bidimensional) con la secuencia de pasos, maximo torque
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setupMotor() {
  pinMode(IN1, OUTPUT);   
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ledPin1, OUTPUT); //Led Verde
  pinMode(ledPin2, OUTPUT); //Led Azul
}

void giroMotor() {
    
        for (int i = 0; i < 512; i++) 
         {
            for (int i = 0; i < 4; i++)   // bucle recorre la matriz de a una fila por vez
            {         // para obtener los valores logicos a aplicar
              digitalWrite(ledPin1, HIGH);
              digitalWrite(IN1, paso[i][0]);  // a IN1, IN2, IN3 e IN4
              digitalWrite(IN2, paso[i][1]);
              digitalWrite(IN3, paso[i][2]);
              digitalWrite(IN4, paso[i][3]);
              delay(demora);
            }
      }
    
      for (int j = 0; j < 512; j++) 
      { 
         for (int j = 3; j >= 0; j--)
          {
            digitalWrite(ledPin1, HIGH);
            digitalWrite(IN4, paso[j][3]);  // bucle recorre la matriz de a una fila por vez
            digitalWrite(IN3, paso[j][2]);  // en sentido inverso
            digitalWrite(IN2, paso[j][1]);
            digitalWrite(IN1, paso[j][0]);
            delay(demora);
          }
      } 
}

void apagarMotor(){
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin1, LOW);
  digitalWrite(IN1, LOW);  // detiene por 5 seg.
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(5000);
}
