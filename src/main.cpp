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
motor BackLift1 = motor(PORT20, ratio18_1, true);   
motor ClawMotor = motor(PORT6, ratio18_1, false); 
motor BackLift2 = motor(PORT10, ratio18_1, false);  
motor LiftMotor = motor(PORT8, ratio18_1, false);  


//motor groups
motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);
motor_group backLiftMotors = motor_group(BackLift1, BackLift2);

//controller
controller Controller = controller();


int count = 0;
int axis4;

float perct = 0.55;
double multiplier = Controller.Axis4.position()*(-1);


void twerk();
void liftUp();
void liftDown();
void clawUp();
void clawDown();

int deadband = 25;  

int b = 0;

float speedarr[3] = {0.55, 0.40, 0.20};


int main() {
  vexcodeInit();



  while (true) {


    // if (Controller.Axis3.position() <0){
    //   axis4 = Controller.Axis4.position()*-1;
    // }
    // else{
    //   axis4 = Controller.Axis4.position();
    // }

    // Get the velocity percentage of the left motor. (Axis3 + Axis4)
    int LeftDriveSpeed =
        Controller.Axis3.position() + axis4;
    // Get the velocity percentage of the right motor. (Axis3 - Axis4)
    int RightDriveSpeed =
        Controller.Axis3.position() - axis4;

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



    // ClawMotor.setVelocity(50, pct);
    //liftMotors.setVelocity(50, pct);
    backLiftMotors.setVelocity(BackLiftSpeed*0.7, pct);
    BackLift1.spin(reverse);
    BackLift2.spin(reverse);
        LiftMotor.setStopping(hold);
    ClawMotor.setStopping(hold);
    backLiftMotors.setStopping(hold);


  while (Controller.ButtonY.pressing()){

      rightDrive.spin(forward, 10, pct);
  leftDrive.spin(reverse, 10, pct);
  wait(200, msec);
  rightDrive.stop();
  leftDrive.stop();
  }

  while (Controller.ButtonA.pressing()){

  rightDrive.spin(reverse, 10, pct);
  leftDrive.spin(forward, 10, pct);
  wait(200, msec);
  rightDrive.stop();
  leftDrive.stop();
  }



  while (Controller.ButtonX.pressing()){
    twerk();
    wait(25, msec);
  }


    Controller.ButtonL1.pressed(liftUp);
    Controller.ButtonL2.pressed(liftDown);

    Controller.ButtonR1.pressed(clawUp);
    Controller.ButtonR2.pressed(clawDown);

    if (Controller.ButtonDown.pressing()) {
      if (b>=2) {
        wait(100, msec);
        b = 0;
      }
      
      else {
        wait(100, msec);
        b += 1;
      }
      perct = speedarr[b];


    }
    
     if (Controller.ButtonUp.pressing()) {
    
          if (b<=0) {
            wait(100, msec);
        b = 2;
      }
                                                                    //
                                                                    else {
                         b -= 1;
                  wait(100, msec);
                       }

    ///////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  ////////////////                                                       /////
///////////////                                                           /////
//////////////                              amooga awooga                   ////
/////////////                                                               ////
//////////////                                                              ////
///////////////                                                            ////
////////////////                                                         /////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////          ///////////////////
//////////////////////////////////////////////////////////////////////////////        ////////             //
//////////////////////////////////////////////////////////////////////////////        ///////     awoo      //
///////////////////////////////             /////////////////////////////////         ////////             //
///////////////////////////////             ////////////////////////////////          //////////////////////
///////////////////////////////              ///////////////////////////////          //////////////////////
///////////////////////////////             ////////////////////////////////          //////////////////////
///////////////////////////////             ///////////////////////////////            ////////////////////
///////////////////////////////             ///////////////////////////////             ///////////////////
 //////////////////////////////              ////////////////////////////               ////////  ////////
  ///////////////////////////                  /////////////////////////                 //////    //////


      perct = speedarr[b];
    }

    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("     %.2f", perct);

    wait(25, msec);
  }
  

  
}


void twerk(){

  //a for loop to make the robot shake back and forth 2 times
  for (int i = 0; i<2; i++ ){
    leftDrive.resetRotation();
    rightDrive.resetRotation();
    leftDrive.spinToPosition(80, deg, 200, rpm, false);
    rightDrive.spinToPosition(80, deg, 200, rpm, true);
    leftDrive.resetRotation();
    rightDrive.resetRotation();
    leftDrive.spinToPosition(-80, deg, 200, rpm, false);
    rightDrive.spinToPosition(-80, deg, 200, rpm, true);
  }
  return;

}


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
  ClawMotor.spin(reverse, 20, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonR1.pressing());
  ClawMotor.stop();
}

void clawDown(){
  ClawMotor.spin(forward, 20, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonR2.pressing());
  ClawMotor.stop();
}
