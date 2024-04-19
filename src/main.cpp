#include "string.h"
#include "vex.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iostream>

using namespace vex;
#define MAX 3

//motors
//T/F checked1
motor frontLeftMotor = motor(PORT7, ratio18_1, true);
motor frontRightMotor = motor(PORT9, ratio18_1, false);
motor backLeftMotor = motor(PORT18, ratio18_1, true);
motor backRightMotor = motor(PORT20, ratio18_1, false);

motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor, backRightMotor);
motor_group leftDiagonalDrive = motor_group(frontLeftMotor, backRightMotor);
motor_group rightDiagonalDrive = motor_group(frontRightMotor, backLeftMotor);

controller Controller = controller();

int num = 200;
int speed = 30;

// char orders[5] = {'l', 'r', 'f', 'b', 'l'};

 void f(){
   leftDrive.resetPosition();
  rightDrive.resetPosition();
  leftDiagonalDrive.resetPosition();
  rightDiagonalDrive.resetPosition();
  wait(25, msec);
    leftDrive.spinToPosition(num, deg, speed, rpm, false);
    rightDrive.spinToPosition(num, deg, speed, rpm, true);
    
  }

  void b(){
    leftDrive.resetPosition();
  rightDrive.resetPosition();
  leftDiagonalDrive.resetPosition();
  rightDiagonalDrive.resetPosition();
  wait(25, msec);
    leftDrive.spinToPosition(-num, deg, speed, rpm, false);
    rightDrive.spinToPosition(-num, deg, speed, rpm, true);
  }

  void l(){
    leftDrive.resetPosition();
  rightDrive.resetPosition();
  leftDiagonalDrive.resetPosition();
  rightDiagonalDrive.resetPosition();
  wait(25, msec);
    leftDiagonalDrive.spinToPosition(-num, deg, speed, rpm, false);
    rightDiagonalDrive.spinToPosition(num, deg, speed, rpm, true);
  }

  void r(){
    leftDrive.resetPosition();
  rightDrive.resetPosition();
  leftDiagonalDrive.resetPosition();
  rightDiagonalDrive.resetPosition();
  wait(25, msec);
    leftDiagonalDrive.spinToPosition(num, deg, speed, rpm, false);
    rightDiagonalDrive.spinToPosition(-num, deg, speed, rpm, true);
  }



int main(void) {
  std::string str = "lrfblrlrfbfb";
  std::list<char> orders;
  for (char c : str) {
        orders.push_back(c);
    }

  while (true) {

     while (Controller.ButtonX.pressing()) {
     for (char c : orders){
        switch (c) {
            case 'l':
                l();
                break;
            case 'r':
                r();
                break;
            case 'f':
                f();
                break;
            case 'b':
                b();
                break;
      }
      
    }
     }
  }
}
  
      
  
