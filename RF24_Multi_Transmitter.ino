/*Transmit POT value through NRF24L01 using Arduino
 * 
 * Pin Conections
 *  CE - 9
    MISO - 12
    MOSI - 11
    SCK - 13
    CS - 10
    POT-A7
*/

#include <SPI.h>  
#include <nRF24L01.h>
#include <RF24.h>

unsigned long previousMillis = 0;
const long interval = 20;

int axis1;
int axis2;

struct SEND_DATA_STRUCTURE{
  int16_t XVal;
  int16_t YVal;
  };

SEND_DATA_STRUCTURE mydata_send;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  radio.begin();  
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN); //MIN power low rage

  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();

  axis1 = analogRead(A0);
  axis2 = analogRead(A1);
  mydata_send.XVal = axis1;
  mydata_send.YVal = axis2;

  radio.write(&mydata_send, sizeof(SEND_DATA_STRUCTURE));       
  previousMillis = currentMillis;  
}
