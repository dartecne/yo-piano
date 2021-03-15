// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup() {
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    else Serial.println( "init OK" );
}

void loop() {
  for( int i = 0; i < 256; i++ ) {
    char buff_A[4], buff_B[4], buffer[8];
    myitoa( i, buff_A, 4 );
    myitoa( 256 - i, buff_B, 4 );
    append_buffers( buff_A, buff_B, buffer);
    driver.send((uint8_t *)buffer, strlen(buffer));
    driver.waitPacketSent();
    delay(20);    
  }
}

void append_buffers( char bA[4], char bB[4], char b[8] ) {
  for( int i = 0; i < 4; i++ ) {
    b[i] = bA[i]
  }
  for( int i = 4; i < 8; i++ ) {
    b[i] = bB[i-4]
  }
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

