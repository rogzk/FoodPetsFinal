//Importacion de librerias
#include <WiFi.h> //libreria per il wifi (meglio non modificare)
#include <WiFiClientSecure.h> //libreria per il wifi (meglio non modificare)
#include <UniversalTelegramBot.h> //libreria per telegram (meglio non modificare)

//Se definen credenciales de la red y el chatbot
#define WIFI_SSID "TP-LINK_DE16" //nome wifi (potete modificarlo) 
#define PASSWORD_WIFI "67743667" //password wifi (potete modificarlo) 
#define BOT_API_TOKEN "5065672666:AAGt8BpeFDJIcE0wJIm9pIhombruJzDhhQI" //token chatbot telegram (potete modificarlo)

//Incluir archivos de los sensores
#include "SENSOR_NIVEL.hpp"
#include "SENSOR_RELOJ.hpp"
#include "sensorTemperatura.h"
#include "SENSOR_DISTANCIA.hpp"
#include "MOTOR.hpp"

const unsigned long intervallo = 1000; //pausa per la ricezione dei messaggi (potete modificarlo)
unsigned long ultima_chiamata = 0; //gestione del millis (meglio non modificare)

WiFiClientSecure s_client; //wifi client (meglio non modificare)
UniversalTelegramBot bot(BOT_API_TOKEN, s_client); //telegram client (meglio non modificare)

void gestisci_messaggi(int num_nuovi_messaggi) { //funzione per la gestione della chat telegram

  for (int i = 0; i < num_nuovi_messaggi; i++) {

    String chat_id = bot.messages[i                                                                                                                                                                                                                      ].chat_id; //id univoco della chat
    String text = bot.messages[i].text; //testo inviato in chat dall'utente
    String from_name = bot.messages[i].from_name; //chi manda il messaggio

    if (from_name == "") {
      from_name = "Desconocido"; //se non possiamo sapere chi ci scrive, allora è uno sconosciuto
    }

    else if (text == "/start") { //se il testo ricevuto è /start allora invia il messaggio di benvenuto
      bot.sendMessage(chat_id, "- Welcome to menu Food Pets - \n 1. /hour - Hora. \n 2. /minute - Minute. \n 3. /time - Fecha y Hora. \n 4. /distance - Distancia. \n 5. /temperature - Temperatura ambiente.");
    }
 
     else if (text == "/hour") {
       bot.sendMessage(chat_id, "La hora es: " + String(horaAct()));
    }
      else if (text == "/minute") {
      bot.sendMessage(chat_id, "El minuto es: " + String(minutoAct()));
    }
    
     else if (text == "/time") {
      bot.sendMessage(chat_id, "La hora actual es: " + String(sensorRTC()));
    }
    
     else if (text == "/distance") {
      bot.sendMessage(chat_id, "La distancia es: " + String(sensorDistancia()) + " cm");
    }
    
    else if (text == "/temperature") {
      bot.sendMessage(chat_id, "La temperatura actual es: " + String(sensorTemperatura()) + " °C");
    }
    
    else {
      bot.sendMessage(chat_id, "Comando no reconocido");
    }

    Serial.println(from_name); //debug su seriale
    Serial.println(chat_id); //debug su seriale
    Serial.println(text); //debug su seriale
  }
}

void setup() {

    Serial.begin(115200); //inizializzo la seriale su 115200 baudrate

    //Inicializacion de sensores.
    setupNivel();
    setupRTC();
    setupTemperatura();
    setupDistancia();
    setupMotor();
   
    Serial.println(); //debug su seriale
    Serial.print("Connetto alla rete wifi "); //debug su seriale
    Serial.println(WIFI_SSID); //debug su seriale
  
    WiFi.begin(WIFI_SSID, PASSWORD_WIFI); //connetto al wifi
  
    s_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); //creo una connessione con Telegram utilizzando un certificato di sicurezza
  
    while (WiFi.status() != WL_CONNECTED) { //finchè il wifi non è connesso attendi e manda dei puntini di sospensione su seriale
      Serial.print("."); //debug su seriale
      delay(500);
    }
  
    Serial.print("Wifi conexion. Direccion IP: "); //debug su seriale
    Serial.println(WiFi.localIP()); //debug su seriale
   
}

void loop() {  
    if (millis() - ultima_chiamata > intervallo) { //se il valore del timer "millis" - l'ultimo valore in millisecondi di quando abbiamo eseguito le istruzioni, è maggiore del tempo di attesa "intervallo", allora esegui le istruzioni
      int num_nuovi_messaggi = bot.getUpdates(bot.last_message_received + 1); //aggiorna la lista dei messaggi in chat
      while (num_nuovi_messaggi) { //finchè ci sono nuovi messaggi, processali
        Serial.println("messaggio ricevuto"); //debug su seriale
        gestisci_messaggi(num_nuovi_messaggi);
        num_nuovi_messaggi = bot.getUpdates(bot.last_message_received + 1);
      }
      ultima_chiamata = millis(); //aggiorna l'ultimo periodo in millisecondi in cui sono state eseguite le istruzioni all'interno del ciclo while
    }

     //Horario de entrada para comida.
     if ((horaAct() == 17 && minutoAct() == 10) && (sensorDistancia() == 14)){
      
           giroMotor();      

        //Se revisa si hay aun alimento en el plato.
      } else if ((horaAct() == 17 && minutoAct() == 11) && (sensorDistancia() < 14)){
        
           apagarMotor();
     
      }
}
