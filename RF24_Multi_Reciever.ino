#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo Servo1;
Servo Servo2;

unsigned long previousMillis = 0;
const long interval = 10;

struct RECEIVE_DATA_STRUCTURE{
  int16_t XVal;
  int16_t YVal;
};

RECEIVE_DATA_STRUCTURE mydata_remote;

RF24 radio(7, 8); // CSN, CE
const byte address[6] = "00001";

int intXVal;
int intYVal;
unsigned long currentMillis;

void setup() {
  Serial.begin(115200);
  
  radio.begin();
  radio.openReadingPipe(1, address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Servo1.attach(10);
  Servo2.attach(9);
  
  Servo1.write(90);
  Servo2.write(90); 
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {
    previousMillis = currentMillis;
    if (radio.available()) {
      radio.read(&mydata_remote, sizeof(RECEIVE_DATA_STRUCTURE));   
    } else {
      Serial.println("no data");
    }
    intXVal = mydata_remote.XVal;
    intYVal = mydata_remote.YVal;
  }

  int Servo1Val = map(intXVal, 0, 1024, 0, 180);
  int Servo2Val = map(intYVal, 0, 1024, 0, 180);
  Servo1.write(Servo1Val);
  Servo2.write(Servo2Val);
  
  Serial.print("X: ");
  Serial.println(intXVal);
  Serial.print("Y: ");
  Serial.println(intYVal);
}
