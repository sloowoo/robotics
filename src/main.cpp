
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

/*
void arcadeDrive(){
    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    int LeftDriveSpeed =
        Controller1.Axis3.position() + Controller1.Axis4.position();
    // Get the velocity percentage of the right motor. (Axis3 - Axis4)
    int RightDriveSpeed =
        Controller1.Axis3.position() - Controller1.Axis4.position();
    int ArmMotorSpeed =
        Controller1.Axis2.position();
        
    //Makes the speed 60% so it's slower
    LeftDriveSpeed = LeftDriveSpeed*0.8;
    RightDriveSpeed = RightDriveSpeed*0.8;
    ArmMotorSpeed = ArmMotorSpeed*0.8;
  

    // Set the speed of the left motor. If the value is less than the deadband, set it to zero.
    if (abs(LeftDriveSpeed) < deadband) {
      // Set the speed to zero.
      LeftDrive.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      LeftDrive.setVelocity(LeftDriveSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(RightDriveSpeed) < deadband) {
      // Set the speed to zero
      RightDrive.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      RightDrive.setVelocity(RightDriveSpeed, percent);
    }

    // Set the speed of the Arm motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(ArmMotorSpeed) < deadband) {
      // Set the speed to zero
      ArmMotor.setVelocity(0, percent);
    } else {
      // Set the speed to Arm motorSpeed
      ArmMotor.setVelocity(ArmMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    LeftDrive.spin(forward);
    RightDrive.spin(forward);
    ArmMotor.spin(forward);
    wait(20, msec);

}

*/

void whenC1R1Pressed() {
  ClawMotor.spin(forward);
  waitUntil(!Controller1.ButtonR1.pressing());
  ClawMotor.stop();
}

void whenC1R2Pressed() {
  ClawMotor.spin(reverse);
  waitUntil(!Controller1.ButtonR2.pressing());
  ClawMotor.stop();
}


void whenC1L1Pressed() {
  LiftMotors.spin(reverse);
  waitUntil(!Controller1.ButtonL1.pressing());
  LiftMotors.stop();
}

void whenC1L2Pressed() {
  LiftMotors.spin(forward);
  waitUntil(!Controller1.ButtonL2.pressing());
  LiftMotors.stop();
}



int main() {
  vexcodeInit();
  LiftMotors.setVelocity(40, pct);

  Controller1.ButtonR1.pressed(whenC1R1Pressed);
  Controller1.ButtonR2.pressed(whenC1R2Pressed);
  Controller1.ButtonL1.pressed(whenC1L1Pressed);
  Controller1.ButtonL2.pressed(whenC1L2Pressed);


  ArmMotor.setStopping(hold);
  ClawMotor.setStopping(hold);
  LiftMotors.setStopping(hold);
  ClawMotor.setVelocity(60, percent);

 

  /*
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
  while (true) {
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

      wait(20, msec);
      //runs arcade drive unless button A is pressed
      arcadeDrive();

    } 
    while (!Controller1.ButtonA.pressing());

    //after button A is pressed, run the autonomous routine
    autonomousDrive();

  */

  //this is arcade drive
  while (true){

    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    int LeftDriveSpeed =
        Controller1.Axis3.position() + Controller1.Axis4.position();
    // Get the velocity percentage of the right motor. (Axis3 - Axis4)
    int RightDriveSpeed =
        Controller1.Axis3.position() - Controller1.Axis4.position();
    int ArmMotorSpeed =
        Controller1.Axis2.position();

    int speed = Controller1.Axis3.position();
    int turn = Controller1.Axis4.position();

    float speedfactor = 0.6;
    float turnfactor = 0.6;
    
    speed = speedfactor * speed;
    turn = turnfactor * turn;

    int right = speed - turn;
    int left = speed + turn;

    LeftDrive.spin(forward, left, pct);
    RightDrive.spin(forward, right, pct);

    LeftDriveSpeed = LeftDriveSpeed*0.6;
    RightDriveSpeed = RightDriveSpeed*0.6;
    ArmMotorSpeed = ArmMotorSpeed*0.6;

    // // Set the speed of the left motor. If the value is less than the deadband,
    // // set it to zero.
    // if (abs(LeftDriveSpeed) < deadband) {
    //   // Set the speed to zero.
    //   LeftDrive.setVelocity(0, percent);
    // } else {
    //   // Set the speed to leftMotorSpeed
    //   LeftDrive.setVelocity(LeftDriveSpeed, percent);
    // }

    // // Set the speed of the right motor. If the value is less than the deadband,
    // // set it to zero.
    // if (abs(RightDriveSpeed) < deadband) {
    //   // Set the speed to zero
    //   RightDrive.setVelocity(0, percent);
    // } else {
    //   // Set the speed to rightMotorSpeed
    //   RightDrive.setVelocity(RightDriveSpeed, percent);
    // }

    // // Set the speed of the Arm motor. If the value is less than the deadband,
    // // set it to zero.
    // if (abs(ArmMotorSpeed) < deadband) {
    //   // Set the speed to zero
    //   ArmMotor.setVelocity(0, percent);
    // } else {
    //   // Set the speed to Arm motorSpeed
    //   ArmMotor.setVelocity(ArmMotorSpeed, percent);
    // }

    // Spin both motors in the forward direction.
    // LeftDrive.spin(forward);
    // RightDrive.spin(forward);
    // ArmMotor.spin(forward);

    // int right = speed - turn;
    // int left = speed + turn;

    // LeftDrive.spin(forward, left, pct);
    // RightDrive.spin(forward, right, pct);

    wait(20, msec);

  if (Controller1.ButtonY.pressing()) {

    LeftDrive.setRotation(0, degrees);
    wait(20, msec);

    LeftDrive.setVelocity(50, percent);
    wait(20, msec);

    RightDrive.setRotation(0, degrees);
    wait(20, msec);

    RightDrive.setVelocity(50, percent);
    wait(20, msec);

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Nudging right!");


    Drivetrain.turnFor(-7, deg);
    waitUntil(!Controller1.ButtonY.pressing());

  }

  
  if (Controller1.ButtonX.pressing()) {

     LeftDrive.setRotation(0, degrees);
    wait(20, msec);

    LeftDrive.setVelocity(50, percent);
    wait(20, msec);

    RightDrive.setRotation(0, degrees);
    wait(20, msec);

    RightDrive.setVelocity(50, percent);
    wait(20, msec);


    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Nudging left!");

    Drivetrain.turnFor(7, deg);
    waitUntil(!Controller1.ButtonX.pressing());

  }


    wait(25, msec);
  }
  

}
