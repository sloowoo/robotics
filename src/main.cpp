#include "vex.h"
#include "string.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace vex;


//motors
//T/F checked
motor frontLeftMotor = motor(PORT10, ratio18_1, true);
motor frontRightMotor = motor(PORT1, ratio18_1, false);
motor backLeftMotor = motor(PORT17, ratio18_1, true);
motor backRightMotor = motor(PORT16, ratio18_1, false);
motor LiftMotor1 = motor(PORT19, ratio18_1, true);   
motor LiftMotor2 = motor(PORT8, ratio18_1, false);  



//motor groups
motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);
motor_group liftMotors = motor_group(LiftMotor1, LiftMotor2);


//drivetrain
drivetrain Drivetrain = drivetrain(leftDrive, rightDrive, 320, 320, 130, mm, 1);


//controller
controller Controller = controller();

float speedFactor = 0.5;
float turnFactor = 0.8;

int speedDeadZone = 15;
int turnDeadZone = 5;
int speedDeadZoneNeg = speedDeadZone * -1;
int turnDeadZoneNeg = turnDeadZone * -1;
int runLoc = 0;
int runLocCheck = 0;
int recordNum = 0;

//defining functions

void LiftUp() {
  LiftMotor1.spin(forward);
  LiftMotor2.spin(forward);
  waitUntil(!Controller.ButtonL1.pressing());
  LiftMotor1.stop();
  LiftMotor2.stop();
}

void LiftDown() {
  LiftMotor1.spin(reverse);
  LiftMotor2.spin(reverse);
  waitUntil(!Controller.ButtonL2.pressing());
  LiftMotor1.stop();
  LiftMotor2.stop();
}

//main
int main() {

  vexcodeInit();
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("Driver Control");

  while(true) {

    float speed = Controller.Axis3.position();
    float turn = Controller.Axis1.position();

    speed = speedFactor * speed;
    turn = turnFactor * turn;

    float right = speed - turn;
    float left = speed + turn;

    leftDrive.spin(directionType::rev, left, velocityUnits::pct);
    rightDrive.spin(directionType::rev, right, velocityUnits::pct);

    Controller.ButtonL1.pressed(LiftUp);
    Controller.ButtonL2.pressed(LiftDown);

  }
}

