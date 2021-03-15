// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module
// No permite analogWrite en pins 9,
#include <VirtualWire.h>

int motor_2_pin = 5;
int led_2_pin = 3;

int motor_3_pin = 6;
int led_3_pin = 3;


void setup() {
  pinMode( motor_2_pin, OUTPUT );
  pinMode( led_2_pin, OUTPUT );  
  pinMode( motor_3_pin, OUTPUT );
  pinMode( led_3_pin, OUTPUT );

  Serial.begin(9600);	// Debugging only
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);   // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
  delay(1000);
  Serial.println( "setup OK" );
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {  // Non-blocking
  	int i, j;
   /*
    for (i = 0; i < buflen; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    */
    i = buffer2number( buf, 3 );
    j = buffer2number( buf, 7 );

    Serial.print( i ); Serial.print( "  " );
    Serial.println( j );
    // machine 2
    analogWrite( motor_2_pin, map(i, 0, 255, 255, 0) );
    analogWrite( led_2_pin, i );

    /* machine 3
    analogWrite( motor_3_pin, map(j, 0, 255, 255, 0) );
    analogWrite( led_3_pin, j );*/
  }
}

int buffer2number( const char buffer[VW_MAX_MESSAGE_LEN], int pos) {
  unsigned char dig[3];
  unsigned int temp;

  dig[0] = buffer[pos] - 48; 
  dig[1] = buffer[pos-1] - 48;
  dig[2] = buffer[pos-2] - 48;


  temp = 100 * dig[2] + 10 * dig[1] + dig[0];
  
  return temp;  
}

