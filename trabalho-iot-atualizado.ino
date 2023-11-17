#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> //biblioteca que estabelece conexão com um servidor HTTP 


#define led  13 //constante led
#define sensor  0 //constante sensor


const char* ssid = "sidinei"; // Nome da rede Wi-Fi
const char* password = "#sdn7and7slv5"; // Senha da rede Wi-Fi
String serverURL = "http://api-jabs.nettools.com.br/v1/detector/1"; // URL do servidor para backup

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(led, LOW);

  // Conectar ao Wi-Fi
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conexão Wi-Fi estabelecida");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
 
}

void mensagem() {
  
  // Enviar sinal para o servidor fazer backup
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverURL);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("Sinal de mensagem enviado. Código de resposta HTTP: %d\n", httpCode);
  } else {
    Serial.println("Falha ao enviar o sinal de backup.");
  }
  http.end();
  delay(5);
}

void loop() {
 
    int sensorPorta = analogRead(sensor); //armazena a porta do sensor
  	int sensorTensao = map(sensorPorta, 0, 1023, 0, 500); // Ajuste para 0.00V - 0.60V

  	if (sensorTensao < 60) { // se a tensão for <0.60 ele chama a função
        mensagem();
       for(int i =0; i <50; i++){
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
       }
      
    	delay(60000);
  	} else {
    	digitalWrite(led, LOW);
      delay(5);
  	}
    if (WiFi.status() != WL_CONNECTED) {
   	Serial.begin(115200);
  	delay(10);

 	  Serial.println();
  	Serial.print("Reconectando a ");
  	Serial.println(ssid);

  	WiFi.begin(ssid, password);

  	while (WiFi.status() != WL_CONNECTED) {
    		delay(500);
    		Serial.print(".");
 	 }

  	Serial.println("");
	  Serial.println("Conexão Wi-Fi restabelecida");
  	Serial.print("Endereço IP: ");
  	Serial.println(WiFi.localIP());
 
}
    
  	delay(5);
    
   
}