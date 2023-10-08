#include <Servo.h>

//joystick settings
//#define x A0
//#define y A1
#define Speed 128 //max 255

//L293D shield settings
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8

#define MOTOR1_A 2
#define MOTOR1_B 3

#define MOTOR2_A 9
#define MOTOR2_B 4

#define MOTOR3_A 5
#define MOTOR3_B 7

#define MOTOR4_A 10
#define MOTOR4_B 6

#define MOTOR1_PWM 11
#define MOTOR2_PWM 3
#define MOTOR3_PWM 6
#define MOTOR4_PWM 5

//#define SERVO1_PWM 10
//#define SERVO2_PWM 9

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4


Servo servo_1;
Servo servo_2;

void setup() {
  Serial.begin(9600);
  //servo_1.attach(SERVO1_PWM);
  //servo_2.attach(SERVO2_PWM);
}
void loop() {

  Serial.println("RC Car's Arduino is listening.");
  if (Serial.available() > 0) {
    int piCommand = Serial.read() - '0'; //zero trick converts to int
    Serial.println(piCommand);
    if(piCommand == 1){
      motor(2, RELEASE, 0);
      motor(3, RELEASE, 0);  
    }
    else if(piCommand == 2){
      motor(3, FORWARD, Speed);
        
    }
    else if(piCommand == 3){
      motor(3, BACKWARD, Speed);  
    }
    //else if(Y <= 200){
    //  motor(3, BACKWARD, Speed);  
    //}
    else {
      motor(2, RELEASE, 0);
      motor(3, RELEASE, 0);    
    }
  }
   
   /*
  int X = analogRead(x);
  int Y = analogRead(y);

  Serial.print(X);
  Serial.print("\t");
  Serial.println(Y);

  if(X >= 800){
      motor(4, BACKWARD, Speed);
  }
  else if(X <= 200){
      motor(4, FORWARD, Speed);
  }
  else if(Y >= 800){
    motor(1, FORWARD, Speed);
  }
  else if(Y <= 200){
    motor(1, BACKWARD, Speed);  
  }
  else {
    motor(1, RELEASE, 0);
    motor(4, RELEASE, 0);    
  }

  motor(1, FORWARD, 255);
  //motor(2, FORWARD, 255);
  //motor(3, FORWARD, 255);
  motor(4, FORWARD, 255);
  +
  delay(2000); // stop it before reverse.
  motor(1, RELEASE, 0);
  //motor(2, RELEASE, 0);
  //motor(3, RELEASE, 0);
  motor(4, RELEASE, 0);
  delay(100);
  motor(1, BACKWARD, 128);
  //motor(2, BACKWARD, 128);
  //motor(3, BACKWARD, 128);
  motor(4, BACKWARD, 128);
  delay(2000);
  motor(1, RELEASE, 0);
  //motor(2, RELEASE, 0);
  //motor(3, RELEASE, 0);
  motor(4, RELEASE, 0);
  delay(100);
  */
 }

void motor(int nMotor, int command, int speed) {
  int motorA, motorB;
  if (nMotor >= 1 && nMotor <= 4) {
    switch (nMotor){
      case 1:
        motorA = MOTOR1_A;
        motorB = MOTOR1_B;
        break;
      case 2:
        motorA = MOTOR2_A;
        motorB = MOTOR2_B;
       break;
     case 3:
        motorA = MOTOR3_A;
        motorB = MOTOR3_B;
        break;
     case 4:
        motorA = MOTOR4_A;
        motorB = MOTOR4_B;
        break;
     default:
        break;
    }
   switch (command) {
    case FORWARD:
        motor_output (motorA, HIGH, speed);
        motor_output (motorB, LOW, -1); // -1: no PWM set
        break;
    case BACKWARD:
        motor_output (motorA, LOW, speed);
        motor_output (motorB, HIGH, -1); // -1: no PWM set
        break;
    case BRAKE:
        motor_output (motorA, LOW, 255); // 255: fully on.
        motor_output (motorB, LOW, -1); // -1: no PWM set
        break;
    case RELEASE:
        motor_output (motorA, LOW, 0); // 0: output floating.
        motor_output (motorB, LOW, -1); // -1: no PWM set
        break;
    default:
        break;
    }
  }
}
void motor_output (int output, int high_low, int speed) {
 int motorPWM;
switch (output){
 case MOTOR1_A:
 case MOTOR1_B:
 motorPWM = MOTOR1_PWM;
 break;
 case MOTOR2_A:
 case MOTOR2_B:
 motorPWM = MOTOR2_PWM;
 break;
 case MOTOR3_A:
 case MOTOR3_B:
 motorPWM = MOTOR3_PWM;
 break;
 case MOTOR4_A:
 case MOTOR4_B:
 motorPWM = MOTOR4_PWM;
 break;
 default:
 speed = -3333;
 break;
}
if (speed != -3333) {
 shiftWrite(output, high_low); // set PWM only if it is valid
if (speed >= 0 && speed <= 255) {
 analogWrite(motorPWM, speed);
}
}
}

void shiftWrite(int output, int high_low) {
 static int latch_copy;
 static int shift_register_initialized = false;
// Do the initialization on the fly,
// at the first time it is used.
if (!shift_register_initialized) {
// Set pins for shift register to output
 pinMode(MOTORLATCH, OUTPUT);
 pinMode(MOTORENABLE, OUTPUT);
 pinMode(MOTORDATA, OUTPUT);
 pinMode(MOTORCLK, OUTPUT);
// Set pins for shift register to default value (low);
 digitalWrite(MOTORDATA, LOW);
 digitalWrite(MOTORLATCH, LOW);
 digitalWrite(MOTORCLK, LOW);
// Enable the shift register, set Enable pin Low.
 digitalWrite(MOTORENABLE, LOW);
// start with all outputs (of the shift register) low
 latch_copy = 0;
 shift_register_initialized = true;
}

// The defines HIGH and LOW are 1 and 0.
// So this is valid.
bitWrite(latch_copy, output, high_low);
shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, latch_copy);
delayMicroseconds(5); // For safety, not really needed.
digitalWrite(MOTORLATCH, HIGH);
delayMicroseconds(5); // For safety, not really needed.
digitalWrite(MOTORLATCH, LOW);
}
