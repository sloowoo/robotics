#include "vex.h"
#include "string.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace vex;
#define MAX 3

//motors
//T/F checked
motor frontLeftMotor = motor(PORT17, ratio18_1, false);
motor frontRightMotor = motor(PORT10, ratio18_1, true);
motor backLeftMotor = motor(PORT1, ratio18_1, false);
motor backRightMotor = motor(PORT20, ratio18_1, true);
motor LiftMotor1 = motor(PORT19, ratio18_1, true);   
motor ClawMotor = motor(PORT18, ratio18_1, false); 
motor LiftMotor2 = motor(PORT8, ratio18_1, false);  


//motor groups
motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);
motor_group liftMotors = motor_group(LiftMotor1, LiftMotor2);


//drivetrain
drivetrain Drivetrain = drivetrain(leftDrive, rightDrive, 345, 360, 340, mm, 1);
//controller
controller Controller = controller();


#define MAX 3

int i = 0;

float length =  5;
float width  = 10;
float height = 20;
float movement;

// declare Contoller event callbacks


int main() {
  vexcodeInit();

  float speed = 60;
  float driveDistance = 20;
  float turnDegrees = 90;
  int index = 0;

  // float length =  5;
  // float width  = 10;
  // float height = 20;

  const char* names[MAX];
  float deltas[MAX];
  float* variables[MAX];
    names[0] = "rpm"; variables[0] = &speed;    deltas[0] =  2;
    names[1] = "distance";  variables[1] = &driveDistance; deltas[1] =  1;
    names[2] = "degrees";   variables[2] = &turnDegrees;    deltas[2] =  1;

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

    leftDrive.setVelocity(speed, rpm);
    rightDrive.setVelocity(speed, rpm);
    //distance/circumfrence is the amount of revolutions it needs to travel, and then that times 360 is the amount of degrees
    movement = (driveDistance/(4*M_PI))*360;


    //for the back lift motors, the motor configuration is 12T against 36T, and the 36T is CONNECTED with a bar to another 12T
    //and that 12T is against a 60T
    //so at the end, when the motor makes 1 revolution, the final gear connected to the lift bars makes 1/15 of a revolution
    
    //for the front lift motors, the motor configuration is 12T against 104T, so each time
    //the motor rotates once, the gear connected to the lift bars rotates 104/12 of a revolution

    leftDrive.spinTo(movement, degrees, speed, rpm, false);
    rightDrive.spinTo(movement, degrees, speed, rpm, false);
    leftDrive.stop();
    rightDrive.stop();

    

    wait(25, msec);
  }
}
