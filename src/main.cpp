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



int count = 0;

float perct = 0.6;


void liftUp(){
  LiftMotor.spin(forward, 50, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonL1.pressing());
  LiftMotor.stop();
}

void liftDown(){
  LiftMotor.spin(reverse, 50, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonL2.pressing());
  LiftMotor.stop();
}

void clawUp(){
  ClawMotor.spin(reverse, 10, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonR1.pressing());
  ClawMotor.stop();
}

void clawDown(){
  ClawMotor.spin(forward, 10, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonR2.pressing());
  ClawMotor.stop();
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

}

void autonomous(void) {

  
}

int main() {
  vexcodeInit();
int deadband = 15;


    
  while (true) {

    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    int LeftDriveSpeed =
        Controller.Axis3.position() + Controller.Axis4.position();
    // Get the velocity percentage of the right motor. (Axis3 - Axis4)
    int RightDriveSpeed =
        Controller.Axis3.position() - Controller.Axis4.position();

    int BackLiftSpeed = Controller.Axis2.position();
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
      rightDrive.setVelocity(0, percent);
    } else {
      rightDrive.setVelocity(RightDriveSpeed*perct, percent);
    }

    leftDrive.spin(forward);
    rightDrive.spin(forward);


    LiftMotor.setStopping(hold);
    ClawMotor.setStopping(hold);
    backLiftMotors.setStopping(hold);

    // ClawMotor.setVelocity(50, pct);
    //liftMotors.setVelocity(50, pct);
    backLiftMotors.setVelocity(BackLiftSpeed*0.7, pct);
    BackLift1.spin(reverse);
    BackLift2.spin(reverse);

  while (Controller.ButtonX.pressing()){

      rightDrive.spin(forward, 10, pct);
  leftDrive.spin(reverse, 10, pct);
  wait(200, msec);
  rightDrive.stop();
  leftDrive.stop();
  }

  while (Controller.ButtonY.pressing()){

      rightDrive.spin(reverse, 10, pct);
  leftDrive.spin(forward, 10, pct);
  wait(200, msec);
  rightDrive.stop();
  leftDrive.stop();
  }

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

    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("     %.2f", perct);

    wait(25, msec);
  }
  

  
}
