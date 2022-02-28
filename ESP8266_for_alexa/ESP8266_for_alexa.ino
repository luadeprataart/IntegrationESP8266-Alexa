/* Interface de comunicação ESP8266 com rede Wi-fi:
   Código para comunicação entre a placa ESP e a rede Wi-fi. O objetivo é estabelecer comunicação com o aparelho alexa da empresa amazon.

   Desenvolvido por Ana Julia Moraes.
   08/02/2022

*/


#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#define RELAY_PIN_1 12
#define RELAY_PIN_2 14


#else
#include <ESP8266WiFi.h>
#define RELAY_PIN_1 D1
#define RELAY_PIN_2 D2


#endif
#include <Espalexa.h>


#define WIFI_NAME  " " //Nome da rede Wifi
#define WIFI_PASS " " //Senha da rede Wifi

#define LED LED_BUILTIN

Espalexa espAlexa;

void Funcion_D1(uint8_t brightness); //Define função para alexa

void setup() {

  Serial.begin(115200); //Iniciando a Serial
  Serial.println();


  wifiSetup(); // Chama a função de conexão wi-fi


  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);



  // Nome visivel pela lista de dispositivos alexa
  espAlexa.addDevice("Led", Funcion_D1);

  espAlexa.begin();


}


void loop() {

  espAlexa.loop();
  delay(1);

}


/* *********************************************************************************************
     Estabelece a conexão Wi-Fi com a placa ESP.
 ***********************************************************************************************/

void wifiSetup() {

 

    WiFi.mode(WIFI_STA);// Define o como STA
    //O modo Station (STA) é usado para conectar o ESP8266 a uma rede WiFi estabelecida por um ponto de acesso.

    WiFi.begin(WIFI_NAME, WIFI_PASS);

    Serial.println("");
    Serial.printf("[WIFI] Conectado a %s ", WIFI_NAME);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(150);
    }

    
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());  // Conectado a rede

}


/* *********************************************************************************************
     Função de rotina para os comandos recebidos pela alexa.
 ***********************************************************************************************/

void Funcion_D1(uint8_t brightness) {
  if (brightness) {
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, HIGH);
  }
}
