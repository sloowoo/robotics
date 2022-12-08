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
motor frontLeftMotor = motor(PORT12, ratio18_1, false);
motor frontRightMotor = motor(PORT2, ratio18_1, false);
motor backLeftMotor = motor(PORT19, ratio18_1, false);
motor backRightMotor = motor(PORT9, ratio18_1, false);
motor LiftMotor = motor(PORT14, ratio18_1, true);


//motor groups
// motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
// motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);

//controller
controller Controller = controller();

bool intakeIsRunning = false;

void whenControllerIntakeButtonPressed() {
  if (intakeIsRunning) {
    LiftMotor.stop();

    intakeIsRunning = false;
  }
  else {
    LiftMotor.spin(forward, 100, pct);
    intakeIsRunning = true;
  }
}

int main(void) {

    Controller.ButtonR1.pressed(whenControllerIntakeButtonPressed);

    float turnFactor = 1.0;
    float speedFactor = 1.0;
    int temp = 0;
    while(true) {
      int ySpeed = speedFactor * Controller.Axis3.value();
      int xSpeed = turnFactor * Controller.Axis4.value();
      int rotationSpeed = turnFactor * Controller.Axis1.value();
        // right joystick is direction
        // left joystick is turning
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

   if(Controller.ButtonUp.pressing()){
          speedFactor += .1;
        }

        if(Controller.ButtonDown.pressing()){
          speedFactor -= .1;
        }

        if(Controller.ButtonRight.pressing()){
          turnFactor += .1;
        }

        if(Controller.ButtonLeft.pressing()){
          turnFactor -= .1;
        }

        Controller.Screen.setCursor(2, 1);
        Controller.Screen.print("turnfactor = %.2f", turnFactor);
        Controller.Screen.setCursor(3, 1);
        Controller.Screen.print("speedfactor = %.2f", speedFactor);
        
        if (ySpeed < 0){
            temp = -rotationSpeed;
        }
        else{
            temp = rotationSpeed;
        
        }
      
    }

}
