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
#include <VirtualWire.h>


#define default_level 0

int motor_1_pin = 5; // 9 no va
int led_1_pin = 3;
int motor_2_pin = 10;
int led_2_pin = 5;
int motor_3_pin = 11;
int led_3_pin = 6;

int transmit_pin = 12;
int receive_pin = 2;
int transmit_en_pin = 4;

void setup() {
  DMXSerial.init(DMXReceiver);
  DMXSerial.maxChannel( 6 );

  vw_set_tx_pin( transmit_pin );
  vw_set_rx_pin( receive_pin );
//  vx_set_ptt_pin( transmit_en_pin );
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);   // Bits per sec

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

  char buff_A[4], buff_B[4], buffer[8];
  myitoa( chn_2, buff_A, 4 );
  myitoa( chn_3, buff_B, 4 );
  append_buffers( buff_A, buff_B, buffer);
  vw_send((uint8_t *)buffer, strlen(buffer));
  vw_wait_tx(); // Wait until the whole message is gone


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

  myitoa( chn_2, buff_A, 4 );
  myitoa( chn_3, buff_B, 4 );
  append_buffers( buff_A, buff_B, buffer);
  vw_send((uint8_t *)buffer, strlen(buffer));
  vw_wait_tx(); // Wait until the whole message is gone


  delay( 1000 );
}

void loop() {
  int chn_1, chn_2, chn_3; 
  unsigned long lastPacket = DMXSerial.noDataSince();
  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels 
    chn_1 = DMXSerial.read(1);
    chn_2 = DMXSerial.read(2);
    chn_3 = DMXSerial.read(3);
  } else {
    chn_1 = default_level;
    chn_2 = default_level;
    chn_3 = default_level;
  }
  analogWrite(motor_1_pin, chn_1 );
  analogWrite( led_1_pin, chn_1 );
  analogWrite( motor_2_pin, chn_2 );
  analogWrite( led_2_pin, chn_2 );
  analogWrite( motor_3_pin, chn_3 );
  analogWrite( led_3_pin, chn_3 );

  char buff_A[4], buff_B[4], buffer[8];
  myitoa( chn_2, buff_A, 4 );
  myitoa( chn_3, buff_B, 4 );
  append_buffers( buff_A, buff_B, buffer);
  vw_send((uint8_t *)buffer, strlen(buffer));
  vw_wait_tx(); // Wait until the whole message is gone
}

void append_buffers( char bA[4], char bB[4], char b[8] ) {
  for( int i = 0; i < 4; i++ ) {
    b[i] = bA[i];
  }
  for( int i = 4; i < 8; i++ ) {
    b[i] = bB[i-4];
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


