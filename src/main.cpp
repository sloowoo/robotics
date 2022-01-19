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
motor LiftMotor2 = motor(PORT8, ratio18_1, false);  
motor ClawMotor = motor(PORT18, ratio18_1, false); 


//motor groups
motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);
motor_group liftMotors = motor_group(LiftMotor1, LiftMotor2);


//drivetrain
drivetrain Drivetrain = drivetrain(leftDrive, rightDrive, 345, 360, 340, mm, 1);
//controller
controller Controller = controller();

float perct = 0.6;

void liftUp(){
  liftMotors.spin(reverse);
  waitUntil(!Controller.ButtonL1.pressing());
  liftMotors.stop();
}

void liftDown(){
  liftMotors.spin(forward);
  waitUntil(!Controller.ButtonL2.pressing());
  liftMotors.stop();
}

void clawUp(){
  ClawMotor.spin(forward);
  waitUntil(!Controller.ButtonR1.pressing());
  ClawMotor.stop();
}

void clawDown(){
  ClawMotor.spin(reverse);
  waitUntil(!Controller.ButtonR2.pressing());
  ClawMotor.stop();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Deadband stops the motors when Axis values are close to zero.
  int deadband = 15;

  while (true) {
    // Get the velocity percentage of the left motor. (Axis3)
    int LeftDriveSpeed = Controller.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int RightDriveSpeed = Controller.Axis2.position();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(LeftDriveSpeed) < deadband) {
      // Set the speed to zero.
      leftDrive.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      leftDrive.setVelocity(LeftDriveSpeed*perct, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(RightDriveSpeed) < deadband) {
      // Set the speed to zero
      rightDrive.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      rightDrive.setVelocity(RightDriveSpeed*perct, percent);
    }

    // Spin both motors in the forward direction.
    leftDrive.spin(forward);
    rightDrive.spin(forward);

    Controller.ButtonL1.pressed(liftUp);
    Controller.ButtonL2.pressed(liftDown);
    Controller.ButtonR1.pressed(clawUp);
    Controller.ButtonR2.pressed(clawDown);

    if (Controller.ButtonUp.pressing()) {
      perct += 0.05;
      wait(150, msec);
    }
    
     if (Controller.ButtonDown.pressing()) {
      perct -= 0.05;
      wait(150, msec);
    }
    
    wait(25, msec);

    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("    %.2f", perct);



    wait(25, msec);

  }
} 
