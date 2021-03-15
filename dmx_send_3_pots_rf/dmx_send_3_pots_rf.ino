// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DmxSerialSend.ino: Sample DMX application for sending 3 DMX values.
// There colors in the 3 lists (RedList, GreenList and BlueList) are placed into the DMX buffer with a slow fade.
// DMXSerial works in the background and constantly sends the actual values over the DMX interface.
// The actual values are also available on the built in PWM ports:
// address 1 (red) -> also available on PWM Port 9
// address 2 (green) -> also available on PWM Port 6
// address 3 (blue) -> also available on PWM Port 5
// 
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// 
// Documentation and samples are available at http://www.mathertel.de/Arduino
// The repository is on github : https://github.com/mathertel/DMXSerial
// The repository on github is made available in the Arduino Library Manager.
//
// 25.07.2011 creation of the DmxSerial library.
// 10.09.2011 fully control the serial hardware register
//            without using the Arduino Serial (HardwareSerial) class to avoid ISR implementation conflicts.
// 01.12.2011 include file and extension changed to work with the Arduino 1.0 environment
// - - - - -

#include <DMXSerial.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

const int led_1_pin =    9;  // PWM output pin 
const int led_2_pin =  6;  // PWM output pin 
const int led_3_pin =   5;  // PWM output pin

int led_1_level, led_2_level, led_3_level;

void setup() {
  DMXSerial.init( DMXController );
  driver.init();
  pinMode( led_1_pin, OUTPUT ); 
  pinMode( led_2_pin, OUTPUT );
  pinMode( led_3_pin, OUTPUT );
} 

void loop() {
  led_1_level = map( analogRead( A0 ), 1023, 0, 0, 255 );
  led_2_level = map( analogRead( A1 ), 1023, 0, 0, 255 );
  led_3_level = map( analogRead( A2 ), 1023, 0, 0, 255 );
  
  DMXSerial.write( 1, led_1_level );
  analogWrite( led_1_pin, led_1_level ); 
  DMXSerial.write( 2, led_2_level );
  analogWrite( led_2_pin, led_2_level ); 
  DMXSerial.write( 3, led_3_level );
  analogWrite( led_3_pin, led_3_level ); 

  delayMicroseconds( 40 );
} 

void myitoa(int number, char *mystring, int n_bytes  ) {
  boolean negative = number>0;

  mystring[0] = number<0? '-' : '+';
  number = number<0 ? -number : number;
  for (int n = n_bytes - 1; n>0; n--) {
     mystring[n] = ' ';
     if(number >= 0) mystring[n] = number%10 + 48;
     number /= 10;
  }  
}


