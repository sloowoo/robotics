/*
#include "vex.h"
#include "robot-config.h"
using namespace vex;

//cannot declare array with a variable dictating the size of array
//just a weird C++ thing
#define MAX 7

int i = 0;
int deadband = 15;

float length =  5;
float width  = 10;
float height = 20;
float driveTime = 2000;
float driveVelocity = 48.0;
float turnDegrees = 90;
float liftTime = 100;
float drive_time = 500; //msec
float number = 0;
float number2 = 0;

//autonomous function - uses parameters set in calibration
void autonomousDrive(){
  // Drivetrain.drive(reverse);
  // wait(driveTime, msec);
  //decelerate(driveVelocity, drive_time);
  // //LiftMotors.spinToPosition(-300, deg, true);
  Drivetrain.drive(forward);
  // //wait(driveTime, msec);
  // //Drivetrain.turnFor(left, turnDegrees, deg);
  }


int main() {
  vexcodeInit();
  // LiftMotors.resetPosition();
  int index = 0;


  
  const char* names[MAX];
  float deltas[MAX];
  float* variables[MAX];
  // delta is how much you change it by each time you press
    names[0] = "Driving time"; variables[0] = &driveTime;    deltas[0] =  100;
    names[1] = "Driving velocity";  variables[1] = &driveVelocity; deltas[1] =  4;
    names[2] = "Turn degrees";   variables[2] = &turnDegrees;    deltas[2] =  5;
    names[3] = "Lift time";   variables[3] = &liftTime;    deltas[3] =  5;
    
    
  // calibration loop
  // #define MAX is up above


  while(true){
    do {
   
      if (Controller1.ButtonUp.pressing()) {
        *variables[index] += deltas[index]; wait(200, msec); }
      else if (Controller1.ButtonDown.pressing()) {
        *variables[index] -= deltas[index]; wait(200, msec); }
      else if (Controller1.ButtonRight.pressing()) {
        index++; if (index == MAX) { index--; }; wait(200, msec); }
      else if (Controller1.ButtonLeft.pressing()) {
        index--; if (index == -1) { index++; }; wait(200, msec); }

      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("   %s = %.2f", names[index], *variables[index]);

      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("  %.2f", deltas[index]);

      wait(20, msec);


      //runs arcade drive unless button A is pressed
    }while (!Controller1.ButtonA.pressing());

    autonomousDrive();

}
}

*/


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Tue Oct 01 2019                                           */
/*    Description:  Clawbot Control                                           */
/*                  This program uses Controller events to drive the arm and  */
/*                  claw of the V5 Clawbot.                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LeftMotor            motor         1
// RightMotor           motor         10
// ClawMotor            motor         3
// ArmMotor             motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <string>

using namespace vex;

#define MAX 3

int i = 0;

float length =  5;
float width  = 10;
float height = 20;

// declare Contoller event callbacks


int main() {
  vexcodeInit();

  float v = 30;
  float driveDistance = 24.0;
  float turnDegrees = 90;

  int index = 0;

  // float length =  5;
  // float width  = 10;
  // float height = 20;

  const char* names[MAX];
  float deltas[MAX];
  float* variables[MAX];
    names[0] = "velocity"; variables[0] = &v;    deltas[0] =  2;
    names[1] = "distance";  variables[1] = &driveDistance; deltas[1] =  1;
    names[2] = "degrees";   variables[2] = &turnDegrees;    deltas[2] =  1;

    // names[2] = "height"; variables[2] = &height; deltas[2] = 10;



  while (true) {
    // calibration loop. do until ButtonA is pressing (pressed). this will give
    // a time between execution of following code when the parameters/variables
    // can be modified.

    // would like to do something similar to solution in RobotC with Mindstorms --
    // have parallel arrays and cycle through them.

    // #define MAX 3 is up above

    do {


    if (Controller1.ButtonUp.pressing()) {
      *variables[index] += deltas[index]; wait(200, msec); }
    else if (Controller1.ButtonDown.pressing()) {
      *variables[index] -= deltas[index]; wait(200, msec); }
    else if (Controller1.ButtonRight.pressing()) {
      index++; if (index == MAX) { index--; }; wait(200, msec); }
    else if (Controller1.ButtonLeft.pressing()) {
      index--; if (index == -1) { index++; }; wait(200, msec); }


      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("   %s = %.2f", names[index], *variables[index]);

      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("     %.2f", deltas[index]);

      wait(25, msec);

    } while (!Controller1.ButtonA.pressing());

    Drivetrain.setDriveVelocity(v, pct);

    Drivetrain.driveFor(reverse, driveDistance, inches, true);
    wait(200, msec);

    wait(25, msec);
  }
}


