#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>

#define DHT11PIN 2
#define DHTTYPE DHT11

DHT dht(DHT11PIN, DHTTYPE);

RF24 radio(7, 8); // CE, CSN pins
const byte address[6] = "00001";

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
    
    dht.begin();
}

void loop() {
    float temp = dht.readTemperature(); // Lê a temperatura do sensor DHT11
    if (isnan(temp)) {
        Serial.println("Falha na leitura do DHT11!");
        return;
    }

    char tempStr[10]; 
    dtostrf(temp, 4, 2, tempStr); // Converte a temperatura em double para uma string
    radio.write(&tempStr, sizeof(tempStr));
    
    Serial.print("Mensagem Enviada: TEMPERATURA = ");
    Serial.println(tempStr);
    delay(1000);
}
