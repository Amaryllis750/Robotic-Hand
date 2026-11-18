#include <Servo.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "my_servo.h"

// ------- GLOBAL VARIABLES -------------
SoftwareSerial BTSerial(2, 3);

Servo gripperServo;
Servo shoulderServo;
Servo elbowServo;
Servo waistServo;

ServoMotor gripper = {&gripperServo, 0, GRIPPER_SERVO_PIN, "GRIPPER"};
ServoMotor shoulder = {&shoulderServo, 0, SHOULDER_SERVO_PIN, "SHOULDER"};
ServoMotor elbow = {&elbowServo, 0, ELBOW_SERVO_PIN, "ELBOW"};
ServoMotor waist = {&waistServo, 0, WAIST_SERVO_PIN, "WAIST"};

ServoMotor *currentMotor = NULL;
String currentCommand = "";

int value = -1;

void setup()
{
  greetMessage();
  BTSerial.begin(9600);
  Serial.println("Bluetooth module has been initialized");
  setupServo(&gripper);
  setupServo(&shoulder);
  setupServo(&elbow);
  setupServo(&waist);
}

void loop()
{
  if (BTSerial.available())
  {
    String input = BTSerial.readStringUntil('\n');
    input.trim();
    int servopin = getDestinationMotorpin(input);
    switch (servopin)
    {
    case GRIPPER_SERVO_PIN:
      currentMotor = &gripper;
      break;
    case SHOULDER_SERVO_PIN:
      currentMotor = &shoulder;
      break;
    case ELBOW_SERVO_PIN:
      currentMotor = &elbow;
      break;
    case WAIST_SERVO_PIN:
      currentMotor = &waist;
      break;
    default:
      Serial.println("Invalid command was sent");
      currentMotor = NULL;
      currentCommand = "";
      return;
    }
    
    String angle = input.substring(1);
    bool valid = validateAngle(angle, &value);
    if(!valid){
      Serial.println(value);
      Serial.println("Invalid angle was sent");
      return ;
    }

    if(currentCommand && currentMotor){
    moveServo(currentMotor, value);
  }
  }
}