#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN

#define joybtn1 2  // Joystick button 1

const byte address[6] = "00001";

struct Data_Package {
  byte joy1_X;
  byte joy1_Y;
  byte j1Button;
};

Data_Package data;

void setup() {

  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();

  pinMode(joybtn1, INPUT_PULLUP);
  
}

void loop() {

//  data.joy1_X = map(analogRead(A1), 0, 1023, 0, 1023);
//  data.joy1_Y = map(analogRead(A0), 0, 1023, 0, 1023);

  data.joy1_X = analogRead(A1);
  data.joy1_Y = analogRead(A0);
  data.j1Button = digitalRead(joybtn1);
  radio.write(&data, sizeof(Data_Package));
}
