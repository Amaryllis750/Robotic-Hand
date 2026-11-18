#ifndef CUSTOM_SERVO_LIB
#define CUSTOM_SERVO_LIB

#define GRIPPER_SERVO_PIN  7
#define ELBOW_SERVO_PIN 4
#define SHOULDER_SERVO_PIN 5
#define WAIST_SERVO_PIN 6

#include <Servo.h>

typedef struct ServoMotor
{
    Servo *servo;
    int angle;
    int pin;
    String name;
} ServoMotor;

void greetMessage();
void setupServo(ServoMotor *motor);
int getDestinationMotorpin(String input);

bool validateAngle(String input, int *d);
void moveServo(ServoMotor *s, int value);

#endif