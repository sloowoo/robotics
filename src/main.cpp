#include "vex.h"
#include "string.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace vex;
#define MAX 3

//motors
//T/F checked
motor frontLeftMotor = motor(PORT17, ratio18_1, false);
motor frontRightMotor = motor(PORT10, ratio18_1, true);
motor backLeftMotor = motor(PORT1, ratio18_1, false);
motor backRightMotor = motor(PORT20, ratio18_1, true);
motor BackLift1 = motor(PORT7, ratio18_1, true);   
motor ClawMotor = motor(PORT18, ratio18_1, false); 
motor BackLift2 = motor(PORT5, ratio18_1, false);  
motor LiftMotor = motor(PORT16, ratio18_1, false);  


//motor groups
motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);
motor_group backLiftMotors = motor_group(BackLift1, BackLift2);


//drivetrain
drivetrain Drivetrain = drivetrain(leftDrive, rightDrive, 345, 360, 340, mm, 1);
//controller
controller Controller = controller();


#define MAX 8

int i = 0;

float length =  5;
float width  = 10;
float height = 20;
double movement;
double movement2;
double movement3;
double movement4;
double movement5;


// declare Contoller event callbacks


int main() {
  vexcodeInit();

  float speed = 100;
  float driveDistance = 52;
  float turnDegrees = 90;
  float diameter = 4.35;
  float liftSpeed = 180;
  float liftDeg = 675;
  float rotleft = 50;
  float rotright = 50;
  int index = 0;

  // float length =  5;
  // float width  = 10;
  // float height = 20;

  const char* names[MAX];
  float deltas[MAX];
  float* variables[MAX];
    names[0] = "rpm"; variables[0] = &speed;    deltas[0] =  2;
    names[1] = "distance";  variables[1] = &driveDistance; deltas[1] =  2;
    names[2] = "degrees";   variables[2] = &turnDegrees;    deltas[2] =  1;
    names[3] = "diameter";   variables[3] = &diameter;    deltas[3] =  0.05;
    names[4] = "liftSpeed";   variables[4] = &liftSpeed;    deltas[4] =  2;
    names[5] = "liftDeg";   variables[5] = &liftDeg;    deltas[5] =  5;
    names[6] = "rotleft";   variables[6] = &rotleft;    deltas[6] =  5;
    names[7] = "rotright";   variables[7] = &rotright;    deltas[7] =  5;

  while (true) {
    // calibration loop. do until ButtonA is pressing (pressed). this will give
    // a time between execution of following code when the parameters/variables 
    // can be modified.

    // would like to do something similar to solution in RobotC with Mindstorms --
    // have parallel arrays and cycle through them.

    // #define MAX 3 is up above
    //

    do {


    if (Controller.ButtonUp.pressing()) {
      *variables[index] += deltas[index]; wait(200, msec); }
    else if (Controller.ButtonDown.pressing()) {
      *variables[index] -= deltas[index]; wait(200, msec); }
    else if (Controller.ButtonRight.pressing()) {
      index++; if (index == MAX) { index--; }; wait(200, msec); }
    else if (Controller.ButtonLeft.pressing()) {
      index--; if (index == -1) { index++; }; wait(200, msec); }


      Controller.Screen.setCursor(2, 1);
      Controller.Screen.print("   %s = %.2f", names[index], *variables[index]);

      Controller.Screen.setCursor(3, 1);
      Controller.Screen.print("     %.2f", deltas[index]);

      wait(25, msec);

    } while (!Controller.ButtonA.pressing());

    wait(25, msec);

    //distance/circumfrence is the amount of revolutions it needs to travel, and then that times 360 is the amount of degrees
    movement = (driveDistance/(diameter*M_PI))*360;
    movement2 = (32/(diameter*M_PI))*360;
    movement3 = (12/(diameter*M_PI))*360;
    movement4 = (16/(diameter*M_PI))*360;
    movement4 = (10/(diameter*M_PI))*360;

    //for the back lift motors, the motor configuration is 12T against 36T, and the 36T is CONNECTED with a bar to another 12T
    //and that 12T is against a 60T
    //so at the end, when the motor makes 1 revolution, the final gear connected to the lift bars makes 1/15 of a revolution
    
    //for the front lift motors, the motor configuration is 12T against 104T, so each time
    //the motor rotates once, the gear connected to the lift bars rotates 104/12 of a revolution
    Controller.Screen.setCursor(1,1);
    Controller.Screen.print(movement);
    leftDrive.resetRotation();
    rightDrive.resetRotation();
    backLiftMotors.resetRotation();
    wait(25, msec);
// leftDrive.spinToPosition(-movement, deg, speed, rpm, false);
// rightDrive.spinToPosition(-movement, deg, speed, rpm, false);
// backLiftMotors.spinToPosition(1870, deg, liftSpeed, rpm, true);
// wait(200, msec);
// backLiftMotors.resetRotation();
// backLiftMotors.spinToPosition(-liftDeg, deg, liftSpeed, rpm, true);
// wait(200, msec);
// leftDrive.resetRotation();
// rightDrive.resetRotation();
// leftDrive.spinToPosition(movement2, deg, speed, rpm, false);
// rightDrive.spinToPosition(movement2, deg, speed, rpm, true);
// wait(200, msec);
// backLiftMotors.resetRotation();
// backLiftMotors.spinToPosition(liftDeg, deg, liftSpeed, rpm, true);
// leftDrive.resetRotation();
// rightDrive.resetRotation();
// leftDrive.spinToPosition(movement3, deg, speed, rpm, false);
// rightDrive.spinToPosition(movement3, deg, speed, rpm, true);

// leftDrive.resetRotation();
// rightDrive.resetRotation();
//   leftDrive.spinToPosition(165, deg, speed, rpm, false);
//   rightDrive.spinToPosition(-165, deg, speed, rpm, true);
  
// leftDrive.resetRotation();
// rightDrive.resetRotation();

// leftDrive.spinToPosition(-movement4, deg, speed, rpm, false);
// rightDrive.spinToPosition(-movement4, deg, speed, rpm, true);
// wait(200, msec);
// backLiftMotors.resetRotation();
// backLiftMotors.spinToPosition(-liftDeg, deg, liftSpeed, rpm, true);
// wait(100, msec);

// leftDrive.resetRotation();
// rightDrive.resetRotation();

// leftDrive.spinToPosition(movement4, deg, speed, rpm, false);
// rightDrive.spinToPosition(movement4, deg, speed, rpm, true);

// backLiftMotors.resetRotation();
// backLiftMotors.spinToPosition(liftDeg, deg, liftSpeed, rpm, true);
// wait(100, msec);


backLiftMotors.spinToPosition(1870, deg, 200, rpm, false);
leftDrive.spinToPosition(-movement3, deg, 150, rpm, false);
rightDrive.spinToPosition(-movement3, deg, 150, rpm, true);
    leftDrive.resetRotation();
    rightDrive.resetRotation();
leftDrive.spinToPosition(36, deg, 150, rpm, false);
rightDrive.spinToPosition(-36, deg, 150, rpm, false);
wait(100, msec);
    leftDrive.resetRotation();
    rightDrive.resetRotation();
    leftDrive.spinToPosition(-movement2*1.25, deg, 150, rpm, false);
rightDrive.spinToPosition(-movement2*1.25, deg, 150, rpm, true);
backLiftMotors.resetRotation();
wait(200, msec);
backLiftMotors.spinToPosition(-liftDeg, deg, 200, rpm, true);

wait(200, msec);
leftDrive.spinToPosition(movement5, deg, 150, rpm, false);
rightDrive.spinToPosition(movement5, deg, 150, rpm, true);

backLiftMotors.resetRotation();
backLiftMotors.spinToPosition(liftDeg, deg, 200, rpm, true);
wait(100, msec);
  
    backLiftMotors.stop();
    leftDrive.stop();
    rightDrive.stop();





    wait(25, msec);
  }
}
