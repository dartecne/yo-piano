/**
 * Control DMX de 3 leds.
 * Basado en el ejemplo:
 * 
 * https://wltd.org/dmx-to-rgbw-led
 * 
 * xlr 1 / gnd
 * xlr 2 white
 * xlr 3 black
*/
#include <DMXSerial.h>

#define default_level 0

int motor_1_pin = 9;
int led_1_pin = 3;
int motor_2_pin = 10;
int led_2_pin = 5;
int motor_3_pin = 11;
int led_3_pin = 6;

void setup() {
  DMXSerial.init(DMXReceiver);
  DMXSerial.maxChannel( 6 );

  DMXSerial.write(1, 80);
  DMXSerial.write(2, 80);
  DMXSerial.write(3, 80);
  
  // enable pwm outputs
  pinMode( motor_1_pin, OUTPUT ); // sets the digital pin as output
  pinMode( motor_2_pin, OUTPUT );
  pinMode( motor_3_pin, OUTPUT );
  pinMode( led_1_pin, OUTPUT ); // sets the digital pin as output
  pinMode( led_2_pin, OUTPUT );
  pinMode( led_3_pin, OUTPUT );
  
  int chn_1 = DMXSerial.read(1);
  analogWrite( motor_1_pin, chn_1 );
  analogWrite( led_1_pin, chn_1 );
  int chn_2 = DMXSerial.read(2);
  analogWrite( motor_2_pin, chn_2 );
  analogWrite( led_2_pin, chn_2 );
  int chn_3 = DMXSerial.read(3);
  analogWrite( motor_3_pin, chn_3 );      
  analogWrite( led_3_pin, chn_3 );

  delay( 1000 );
  
  DMXSerial.write(1, 0);
  DMXSerial.write(2, 0);
  DMXSerial.write(3, 0);
  
  chn_1 = DMXSerial.read(1);
  analogWrite( motor_1_pin, chn_1 );
  analogWrite( led_1_pin, chn_1 );
  chn_2 = DMXSerial.read(2);
  analogWrite( motor_2_pin, chn_2 );
  analogWrite( led_2_pin, chn_2 );
  chn_3 = DMXSerial.read(3);
  analogWrite( motor_3_pin, chn_3 );      
  analogWrite( led_3_pin, chn_3 );

  delay( 1000 );
}

void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();
  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels 
    int chn_1 = DMXSerial.read(1);
    analogWrite(motor_1_pin, chn_1 );
    analogWrite( led_1_pin, chn_1 );

    int chn_2 = DMXSerial.read(2);
    analogWrite( motor_2_pin, chn_2 );
    analogWrite( led_2_pin, chn_2 );

    int chn_3 = DMXSerial.read(3);
    analogWrite( motor_3_pin, chn_3 );
    analogWrite( led_3_pin, chn_3 );
  } else {
    // Show pure red color, when no data was received since 5 seconds or more.
    analogWrite( motor_1_pin, default_level );
    analogWrite( led_1_pin, default_level );
    analogWrite( motor_2_pin, default_level );
    analogWrite( led_2_pin, default_level );
    analogWrite( motor_3_pin, default_level );
    analogWrite( led_3_pin, default_level );
  }
}

