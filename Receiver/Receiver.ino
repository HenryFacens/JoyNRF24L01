#include <SPI.h>
#include <Servo.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN

const byte address[6] = "00001";

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

struct Data_Package {
  byte joy1_X;
  byte joy1_Y;
  byte j1Button;
};

Data_Package data;
Servo ESC;

void setup() {
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

  ESC.attach(10, 1000, 1200);
  ESC.write(0);
  delay(2000);
  
}

void loop() {
if (radio.available()) {
     radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis();
  }


 int valor = map(data.joy1_X,0,255,180,-3);

  Serial.println(valor);

  ESC.write(valor);
  
}
