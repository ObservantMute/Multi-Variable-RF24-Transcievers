#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";
//SErvo control
Servo yaw;
//Servo pitch;
//Servo roll;
Servo thr;
//Joystick ARray
int joystick[6];

void setup()
{
  for(int i = 2; i<=4; i++){
    pinMode(i,OUTPUT);
  }

  
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setAutoAck(false);
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
  //Servo attachments
  thr.attach(2);
  yaw.attach(3);
  //pitch.attach(4);
  //roll.attach(5);
  
  delay(50);
  
}

void loop()
{
  if (radio.available())
  {
    bool done = false;
         while (!done)
        { 
          // Fetching the data payload
          radio.read( joystick, sizeof(joystick) );
         done = true; 
         
              
         int val0=map(joystick[0],0,1024,0,180);
         int val1=map(joystick[1],0,1024,0,180);
         //int val2=map(joystick[2],0,1024,0,180);
         //int val3=map(joystick[3],0,1024,0,180);
        thr.write(val0);
        yaw.write(val1);
        //pitch.write(val2);
        //roll.write(val3);
        //for serial observation
        Serial.println(val0);
        Serial.println(val1);
        //Serial.println(val2);
        //Serial.println(val3);
        }
  }
    else{
      Serial.println("Data not received");
      
    }
  
  delay(50);
}
