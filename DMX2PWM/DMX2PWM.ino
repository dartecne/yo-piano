/*
*/

#include <DMXSerial.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int motorPin = 3;      
int sensorValue = 0;  

void setup() {
  DMXSerial.init(DMXReceiver);
  DMXSerial.write(1, 80);
  DMXSerial.write(2, 0);
  DMXSerial.write(3, 0);

  pinMode(motorPin, OUTPUT);
}

void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();
  
  if (lastPacket < 5000) {
    analogWrite(motorPin,   DMXSerial.read(1));
  } else {
    sensorValue = analogRead(sensorPin);
    int v = map( sensorValue, 0, 1024, 0, 255 );  
    analogWrite(motorPin, v);
  }
  delay(6);
}
