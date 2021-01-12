#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
// Example of data captured by IRrecvDumpV2.ino
uint16_t rawDataOn[] = {496, 388, 488, 380, 488, 376, 496, 372, 500, 360, 512, 24924, 3604, 1612, 468, 1272, 476, 380, 
            484, 384, 488, 380, 488, 1244, 500, 376, 500, 368, 500, 364, 508, 364, 504, 1236, 496, 352, 524, 1232, 496, 1236, 500, 
            372, 504, 1244, 492, 1248, 488, 1228, 512, 1264, 472, 1268, 472, 352, 524, 372, 500, 1256, 476, 340, 536, 380, 496, 
            360, 504, 368, 504, 384, 484, 372, 500, 380, 488, 356, 516, 356, 512, 364, 504, 368, 504, 364, 500, 384, 488, 360, 
            508, 360, 512, 384, 484, 364, 508, 384, 480, 1252, 472, 400, 480, 352, 520, 376, 492, 1260, 484, 1252, 492, 364, 504, 
            368, 500, 380, 492, 1248, 492, 364, 500, 1252, 508, 344, 504, 1256, 488, 356, 512, 380, 484, 384, 492, 376, 496, 360, 
            504, 376, 496, 356, 512, 372, 500, 356, 512, 360, 508, 376, 496, 360, 512, 360, 508, 356, 512, 364, 508, 1244, 496, 356, 
            508, 1244, 500, 356, 512, 360, 508, 356, 516, 356, 512, 352, 520, 348, 520, 360, 512, 348, 520, 356, 516, 348, 520, 352, 
            516, 352, 520, 352, 520, 344, 520, 352, 520, 352, 520, 340, 528, 352, 528, 336, 524, 344, 524, 352, 520, 344, 524, 340, 528, 
            348, 520, 348, 524, 352, 512, 356, 516, 344, 524, 352, 520, 348, 516, 352, 520, 348, 520, 348, 520, 356, 516, 348, 520, 348, 
            520, 352, 516, 352, 520, 356, 512, 352, 520, 348, 516, 360, 516, 344, 520, 360, 512, 348, 520, 360, 512, 348, 520, 348, 520, 
            1244, 488, 368, 508, 1244, 492, 352, 516, 364, 508, 348, 520, 1244, 492, 1244, 492, 364, 512, 1240, 496, 368, 504, 352, 516, 356, 
            516, 352, 516, 356, 516, 356, 512, 348, 520, 352, 520, 352, 512, 356, 520, 348, 516, 356, 516, 352, 516, 352, 520, 356, 508, 356, 516, 
            1244, 492, 356, 512, 1248, 484, 380, 500, 1244, 488, 1244, 492};
uint16_t rawDataOff[] = {536, 372, 488, 388, 480, 384, 496, 384, 480, 364, 504, 24916, 3568, 1648, 500, 1236, 
          508, 380, 484, 384, 488, 368, 500, 1232, 508, 360, 508, 340, 532, 384, 484, 380, 488, 1224, 520, 376, 488, 1236, 
          504, 1232, 508, 380, 484, 1232, 508, 1232, 512, 1252, 500, 1236, 488, 1228, 512, 360, 508, 380, 488, 1256, 488, 376, 488, 
          360, 512, 360, 508, 360, 512, 344, 524, 360, 508, 360, 512, 380, 488, 380, 488, 360, 508, 360, 512, 376, 492, 384, 488, 360,
          508, 380, 488, 360, 508, 380, 492, 380, 488, 380, 488, 360, 512, 360, 508, 376, 476, 1268, 472, 1268, 472, 392, 472, 396, 476, 396, 476, 1268, 
          468, 380, 488, 1272, 472, 388, 476, 1268, 472, 396, 472, 396, 472, 400, 472, 396, 472, 400, 472, 396, 472, 396, 472, 396, 472, 396, 476, 396, 472, 
          396, 476, 392, 476, 396, 472, 396, 472, 400, 472, 1268, 472, 392, 476, 1264, 476, 396, 472, 384, 488, 392, 472, 400, 472, 396, 472, 400, 472, 376, 492, 
          396, 472, 384, 484, 396, 476, 396, 472, 396, 472, 400, 472, 396, 472, 400, 472, 396, 472, 376, 492, 400, 472, 396, 472, 396, 476, 392, 472, 400, 472, 396, 472, 
          396, 472, 400, 472, 392, 476, 380, 492, 392, 472, 400, 476, 392, 472, 400, 472, 396, 472, 396, 476, 396, 468, 400, 472, 396, 472, 400, 472, 396, 472, 400, 472,
          392, 476, 396, 472, 396, 472, 400, 472, 396, 472, 400, 468, 400, 468, 400, 472, 396, 476, 1264, 472, 396, 472, 1272, 472, 396, 472, 396, 472, 396, 472, 1268, 472, 
          1268, 472, 392, 472, 1268, 476, 392, 476, 392, 476, 396, 472, 380, 492, 1268, 472, 376, 488, 400, 472, 396, 472, 396, 472, 400, 472, 396, 472, 400, 468, 400, 468, 
          400, 472, 1268, 472, 1268, 472, 396, 472, 396, 472, 1268, 472, 396, 472, 396, 472, 400, 472};


//wifi
const char* ssid = "Digital_C";
const char* password = "@digital#world";
String ip = "";

WiFiServer server(80);

            
void setup() {
  //ar
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266


  //wifi

  server.begin();
  Serial.println("\nConectando-se em: " + String(ssid));
  WiFi.begin(ssid, password); // PASSANDO AS CREDENCIAIS PARA CONEXÃO NO WI-FI

  while (WiFi.status() != WL_CONNECTED) { // ENQUANTO NÃO CONECTAR
    delay(1000);
    Serial.print(".");
  }

  Serial.print("\nConectado na Rede " + String(ssid) + " | IP => ");
  Serial.println(WiFi.localIP()); // IP DO DISPOSITIVO NA REDE
  ip = WiFi.localIP().toString(); // PEGANDO O IP E COLOCANDO NA VARIÁVEL
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { // VERIFICANDO CONEXÃO WI-FI
    WiFiClient client = server.available(); // DISPONIBILIZANDO PARA RECEBER REQUISIÇÕESs

    if (client) {
      Serial.println("requisição");
      String req = client.readStringUntil('\r'); // RECEBENDO A REQUISIÇÃO
      
      boolean insideArray = false;
      String reqBody;
      char c;

      while(client.available()){
        c = client.read();
          Serial.write(c);
        
        if(insideArray && c != '"'&& c != ']'){
          reqBody += c;
        }
        
        if(c == '"'){
          insideArray = true;
        }
      }
      
      client.flush();
      Serial.println(reqBody);
      
      if (req.indexOf("ativacao") != -1){
        if(reqBody=="true"){
          
          irsend.sendRaw(rawDataOn, sizeof(rawDataOn) / sizeof(rawDataOn[0]), 38);  // Send a raw data capture at 38kHz.
          Serial.println("ligou");
          
        }else if(reqBody == "false"){
          
          irsend.sendRaw(rawDataOff, sizeof(rawDataOff) / sizeof(rawDataOff[0]), 38);  // Send a raw data capture at 38kHz.
          Serial.println("desligou");
          
        }else{
          Serial.println("deu ruim");
        }
      }
      
    }
  }
}
