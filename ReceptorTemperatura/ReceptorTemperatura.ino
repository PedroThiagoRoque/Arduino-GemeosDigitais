#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN pins
const byte address[6] = "00001";

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
}

void loop() {
    if (radio.available()) {
        char tempStr[10]; // Buffer para receber a string da temperatura
        radio.read(&tempStr, sizeof(tempStr));
        float temperature = atof(tempStr); // Convertendo a string recebida de volta para float

        Serial.print("Temperatura Recebida: ");
        Serial.print(temperature);
        Serial.println(" °C");
    }
}
