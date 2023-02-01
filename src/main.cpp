#include "string.h"
#include "vex.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

using namespace vex;
#define MAX 3

//motors
//T/F checked1
motor frontLeftMotor = motor(PORT17, ratio18_1, false);
motor frontRightMotor = motor(PORT19, ratio18_1, false);
motor backLeftMotor = motor(PORT6, ratio18_1, false);
motor backRightMotor = motor(PORT3, ratio18_1, false);
motor intakeMotor = motor(PORT13, ratio18_1, false);
motor shooterMotor = motor(PORT18, ratio18_1, true);
motor flickMotor = motor(PORT7, ratio18_1, true);
//booleans for intake and shooter toggle
bool intakeRunning = false;
bool shooterRunning = false;
double shootFactor = 0.8;

motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor, backRightMotor);

controller Controller = controller();

//controls the motor that pushes the disk into the shooter
void flick() {
    flickMotor.setVelocity(30, pct);
    flickMotor.spinTo(15, degrees);
    wait(25, msec);
    flickMotor.spinTo(-15, degrees);
    wait(25, msec);
  }

void whenL1Pressed() {
  if (intakeRunning) {
    intakeMotor.stop();
    intakeRunning = false;
    wait(25, msec);

  } else {
    intakeMotor.setVelocity(100, pct);
    intakeMotor.spin(reverse);
    intakeRunning = true;
    wait(25, msec);
  }
}

void whenR1Pressed() {
  if (shooterRunning) {
    shooterMotor.spin(reverse, 0, volt);
    shooterMotor.setBrake(brake);
    shooterRunning = false;
    wait(25, msec);

  } else {
    shooterMotor.spin(reverse, 12.8*shootFactor, volt);
    //shooterMotor.spin(reverse);
    shooterRunning = true;
    wait(25, msec);
  }
}


int main(void) {
  
  //allows driver to calibrate driving speed
  float turnFactor = 0.5;
  float speedFactor = 0.5;

  //used in y-speed-reverse around line 100
  int temp = 0;
  
  Controller.ButtonL1.pressed(whenL1Pressed);
  Controller.ButtonR1.pressed(whenR1Pressed);
  Controller.ButtonL2.pressed(flick);
  intakeMotor.setStopping(hold);

  while (true) {
    int ySpeed = speedFactor * Controller.Axis3.value();
    int xSpeed = turnFactor * Controller.Axis4.value();
    int rotationSpeed = turnFactor * Controller.Axis1.value();
    double front_left_velocity = temp + ySpeed + xSpeed;
    double back_left_velocity = temp + ySpeed - xSpeed;
    double front_right_velocity = temp - ySpeed + xSpeed;
    double back_right_velocity = temp - ySpeed - xSpeed;

    frontLeftMotor.setVelocity(front_left_velocity, pct);
    backLeftMotor.setVelocity(back_left_velocity, pct);
    frontRightMotor.setVelocity(front_right_velocity, pct);
    backRightMotor.setVelocity(back_right_velocity, pct);
    frontLeftMotor.spin(forward);
    backLeftMotor.spin(forward);
    frontRightMotor.spin(forward);
    backRightMotor.spin(forward);


    if (Controller.ButtonUp.pressing()) {
      speedFactor += .1;
    }

    if (Controller.ButtonDown.pressing()) {
      speedFactor -= .1;
    }

    if (Controller.ButtonRight.pressing()) {
      turnFactor += .1;
    }

    if (Controller.ButtonLeft.pressing()) {
      turnFactor -= .1;
    }

    if (Controller.ButtonB.pressing()) {
      shootFactor -= .1;
      shooterMotor.spin(reverse, 12.8*shootFactor, volt);
    }

    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("turnFactor = %.2f", turnFactor);
    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("speedFactor = %.2f", speedFactor);
    Controller.Screen.setCursor(3, 1);
    Controller.Screen.print("shootFactor = %.2f", shootFactor);

    //y-speed-reverse that depends robots direction
    //makes turning for the driver more intitive
    if (ySpeed < 0) {
      temp = -rotationSpeed;
    } else {
      temp = rotationSpeed;
    }


    //nudge right
    while (Controller.ButtonA.pressing()) {
      rightDrive.spin(forward, 10, pct);
      leftDrive.spin(forward, 10, pct);
      wait(200, msec);
      rightDrive.stop();
      leftDrive.stop();
    }

    //nudge left
    while (Controller.ButtonY.pressing()) {
      rightDrive.spin(reverse, 10, pct);
      leftDrive.spin(reverse, 10, pct);
      wait(200, msec);
      rightDrive.stop();
      leftDrive.stop();
    }

  }
}



