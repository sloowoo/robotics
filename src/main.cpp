
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

void autonomousRoutine(){

}



void whenC1L1Pressed() {
  LiftMotors.spin(forward);
  waitUntil(!Controller1.ButtonL1.pressing());
  LiftMotors.stop();
}

void whenC1L2Pressed() {
  LiftMotors.spin(reverse);
  waitUntil(!Controller1.ButtonL2.pressing());
  LiftMotors.stop();
}



int main() {
  vexcodeInit();
  LiftMotors.setStopping(hold);

  // Controller1.ButtonL1.pressed(whenC1L1Pressed);
  // Controller1.ButtonL2.pressed(whenC1L2Pressed);


  //this is arcade drive
  while (true){

    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    int LeftDriveSpeed =
        Controller1.Axis3.position() + Controller1.Axis4.position();
    // Get the velocity percentage of the right motor. (Axis3 - Axis4)
    int RightDriveSpeed =
        Controller1.Axis3.position() - Controller1.Axis4.position();

    LeftDriveSpeed = LeftDriveSpeed*0.8;
    RightDriveSpeed = RightDriveSpeed*0.8;

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
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
  
    // Spin both motors in the forward direction.
    LeftDrive.spin(forward);
    RightDrive.spin(forward);

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
    