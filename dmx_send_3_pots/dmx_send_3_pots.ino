
#include <DMXSerial.h>

const int pot_1_pin = 0;  // pot input
const int pot_2_pin = 2;  
const int pot_3_pin = 5;  

const int chn_1_pin = 3;  // PWM output
const int chn_2_pin = 5;  
const int chn_3_pin = 6;  


int chn_1_level, chn_2_level, chn_3_level;

void setup() {
  DMXSerial.init( DMXController );

  pinMode( chn_1_pin, OUTPUT ); 
  pinMode( chn_2_pin, OUTPUT );
  pinMode( chn_3_pin, OUTPUT );
} 

void loop() {
  chn_1_level = map( analogRead( pot_1_pin ), 1023, 0, 255, 0 );
  chn_2_level = map( analogRead( pot_2_pin ), 1023, 0, 255, 0 );
  chn_3_level = map( analogRead( pot_3_pin ), 1023, 0, 255, 0 );
  
  DMXSerial.write( 1, chn_1_level );
  analogWrite( chn_1_pin, chn_1_level ); 
  DMXSerial.write( 2, chn_2_level );
  analogWrite( chn_2_pin, chn_2_level ); 
  DMXSerial.write( 3, chn_3_level );
  analogWrite( chn_3_pin, chn_3_level ); 

  delayMicroseconds( 40 );
} 

