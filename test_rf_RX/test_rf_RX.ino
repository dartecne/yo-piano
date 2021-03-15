// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#define INPUT_BUFFER_SIZE 3

RH_ASK driver;

void setup() {
  pinMode( 3, OUTPUT );
    Serial.begin(9600);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {// Non-blocking 
  	int i;
    i = buffer2number( buf );
	// Message with a good checksum received, dump it.
	//  driver.printBuffer("Got:", buf, buflen);
    Serial.println( i );
    analogWrite(3, i);
  }
}

int buffer2number( const char buffer[]  ) {
  unsigned char dig[3];
  unsigned int temp;

  dig[0] = buffer[3] - 48; 
  dig[1] = buffer[2] - 48;
  dig[2] = buffer[1] - 48;


  temp = 100 * dig[2] + 10 * dig[1] + dig[0];
  
  return temp;  
}

