#include <Arduino.h>
#include <errno.h>
#include <limits.h>

#include <Servo.h>

#include "my_servo.h"

void greetMessage()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Bluetooth Controlled Robot Arm...");
}

void setupServo(ServoMotor *m)
{
  delay(15);
  Serial.print("Setting position to 0 for ");
  Serial.println(m->name);
  delay(15);
  m->servo->attach(m->pin);
  m->angle = 0;
  m->servo->write(m->angle);
}

int getDestinationMotorpin(String input){
  char prefix = input[0];
  if (prefix == 'G') return GRIPPER_SERVO_PIN;
  else if (prefix == 'W') return WAIST_SERVO_PIN;
  else if (prefix == 'E') return ELBOW_SERVO_PIN;
  else if (prefix == 'S') return SHOULDER_SERVO_PIN;
  else return -1;
}

void parseInput(String input){

}

bool validateAngle(String input, int *value)
{
  errno = 0;
  char *endptr = nullptr;
  const char *c_input = input.c_str();
  long result = strtol(c_input, &endptr, 10);

  if (endptr == c_input)
    return false; // nothing was converted

  if (*endptr != '\0')
    return false;
  if (errno == ERANGE || result < INT_MIN || result > INT_MAX)
    return false;

  *value = result;
  return true;
}

void  moveServo(ServoMotor *m, int final_destination){
  int step = m->angle < final_destination ? 1 : -1;
  while((step == 1) ? m->angle < final_destination : m->angle > final_destination){
    m->angle += step;
    m->servo->write(m->angle);
    delay(15);
  }
  Serial.print("Servo is now at: ");
  Serial.println(m->angle);
}