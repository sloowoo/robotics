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
motor frontLeftMotor = motor(PORT18, ratio18_1, false);
motor frontRightMotor = motor(PORT7, ratio18_1, true);
motor backLeftMotor = motor(PORT19, ratio18_1, false);
motor backRightMotor = motor(PORT5, ratio18_1, true);


//motor groups
// motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
// motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);

//controller
controller Controller1 = controller();

int main(void) {
    while(true) {
        // right joystick is direction
        // left joystick is turning
        double front_left_velocity = Controller1.Axis4.value() + Controller1.Axis2.value() + Controller1.Axis1.value();
        double back_left_velocity = Controller1.Axis4.value() + Controller1.Axis2.value() - Controller1.Axis1.value();
        double front_right_velocity = Controller1.Axis4.value() - Controller1.Axis2.value() + Controller1.Axis1.value();
        double back_right_velocity = Controller1.Axis4.value() - Controller1.Axis2.value() + Controller1.Axis1.value();

        frontLeftMotor.setVelocity(front_left_velocity, pct);
        backLeftMotor.setVelocity(back_left_velocity, pct);
        frontRightMotor.setVelocity(front_right_velocity, pct);
        backRightMotor.setVelocity(back_right_velocity, pct);

        frontLeftMotor.spin(forward);
        backLeftMotor.spin(forward);
        frontRightMotor.spin(forward);
        backRightMotor.spin(forward);
        
    }

}
