/*
*/

int sensorPin[3] = {0, 1, 2};
int ledPin = 6;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for( int i = 0; i < 3; i++ ) {
    sensorValue = analogRead(sensorPin[i]);
    Serial.print( sensorValue );
    Serial.print( " " );    
  }
  Serial.println();

  int v = map( sensorValue, 0, 1024, 0, 255 );
  analogWrite(ledPin, v);
  delay(40);
}
