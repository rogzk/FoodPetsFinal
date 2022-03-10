//RELOJ RTC
#include <Wire.h>   // incluye libreria para interfaz I2C
#include <RTClib.h>   // incluye libreria para el manejo del modulo RTC

RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231

void setupRTC() {
  Serial.begin(115200);    // inicializa comunicacion serie a 9600 bps

  if (! rtc.begin()) {       // si falla la inicializacion del modulo
    Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error
    while (1);         // bucle infinito que detiene ejecucion del programa
  }
  rtc.adjust(DateTime(__DATE__, __TIME__));  // funcion que permite establecer fecha y horario
  //rtc.adjust(DateTime(2021,03,1,10,10,00));  
            // al momento de la compilacion. Comentar esta linea
}

int horaAct(){  
      DateTime fecha = rtc.now(); 
      int horaActual = (fecha.hour());
       return horaActual;
}

int minutoAct(){
      DateTime fecha = rtc.now(); 
      int minutoActual = (fecha.minute());
      return minutoActual;
}


String sensorRTC() { 
      DateTime fecha = rtc.now();      // funcion que devuelve fecha y horario en formato
    
      String fechaActual = String(fecha.day())+"/"+ String(fecha.month()) +"/"+ String(fecha.year()) +" "+ String(fecha.hour()) +":"+ String(fecha.minute()) +":"+ String(fecha.second());
      //String horaActual = String(fecha.hour());
      //String minutoActual = String(fecha.minute());
      delay(1000);         // demora de 1 segundo
    
      return fechaActual;
}
