/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

//Instructions for processing: run arduino then run processing, open serial monitor
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)



//black servomin = servomax =
//microservo servomin=150 servomax=600
void setup() {
  Serial.begin(115200);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

// our servo # counter
uint8_t rotate = 0;
uint8_t nearJoint = 1;
uint8_t farJoint = 2;
//uint8_t scoop = 3;

//starting positions of servos
int rotateAngle = 300;
int nearJointAngle = 150;
int farJointAngle = 450;
//int scoopAngle = 150;

//rotating bottom axis
void rotateLeft() {
  if(rotateAngle > 150){
    rotateAngle -= 10;
    }
  pwm.setPWM(rotate, 0, rotateAngle);
}

void rotateRight() {
  if(rotateAngle < 600){
    rotateAngle += 10;
    }
  pwm.setPWM(rotate, 0, rotateAngle);
}


//rotating nearJoint
void nearJointDown() {
  if(nearJointAngle > 150){
    nearJointAngle -= 10;
    }
  pwm.setPWM(nearJoint, 0, nearJointAngle);
}

void nearJointUp() {
  if(nearJointAngle < 600){
    nearJointAngle += 10;
    }
  pwm.setPWM(nearJoint, 0, nearJointAngle);
}

//rotating farJoint
void farJointDown() {
  if(farJointAngle > 150){
    farJointAngle -= 10;
    }
  pwm.setPWM(farJoint, 0, farJointAngle);
}

void farJointUp() {
  if(farJointAngle < 600){
    farJointAngle += 10;
    }
  pwm.setPWM(farJoint, 0, farJointAngle);
}

//rotating scoop



void loop() {
  char incomingChar = 0;   // for incoming serial data
  if (Serial.available() > 0) {
    incomingChar = Serial.read();
    switch (incomingChar) {
      case 'a':
        Serial.write('A');  // Apricot
        rotateLeft();
        break;
      case 'd':
        Serial.write('D');  // Dandelion
        rotateRight();
        break;
      case 'w':
        Serial.write('W');  // White
        nearJointUp();
        break;
      case 's':
        Serial.write('S');  // Scarlet
        nearJointDown();
        break;
      case 'r':
        Serial.write('R');  // Red
        farJointUp();
        break;
      case 'f':
        Serial.write('F');  // Fuchsia
        farJointDown();
        break;
      case 'q':
         Serial.write('B');  // BLACK
        break;
      default:
        Serial.write('B');  // BLACK
        break;
    }
  } else incomingChar = 0; // not really needed but in case you want to do things in the loop upon receiving new chars. if (incomingChar == 0) then no new char was received, otherwise later in the loop you still have the char received
}
