#include "string.h"
#include "vex.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

using namespace vex;
#define MAX 3

// motors
// T/F checked
motor frontLeftMotor = motor(PORT18, ratio18_1, false);
motor frontRightMotor = motor(PORT7, ratio18_1, true);
motor backLeftMotor = motor(PORT19, ratio18_1, false);
motor backRightMotor = motor(PORT5, ratio18_1, true);
motor BackLift1 = motor(PORT20, ratio18_1, true);
motor ClawMotor = motor(PORT8, ratio18_1, false);
motor BackLift2 = motor(PORT10, ratio18_1, false);
motor LiftMotor = motor(PORT6, ratio18_1, false);

// motor groups
motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor, backRightMotor);
motor_group backLiftMotors = motor_group(BackLift1, BackLift2);

// controller
controller Controller = controller();

// A global instance of competition
competition Competition;

//axis4 will later be set to the Axis4 position of the joystick
//because we will set a deadband for the Axis4 position
//but you can't directly change the value of Controller.Axis4.position()
//refer to the start of the usercontrol code
int axis4 = 0;

//perct is a varible that is calibratable
//it sets the velocity of the robot
//refer to the drving code where the speed of the motor groups is multiplied by perct
float perct = 0.55;

//the reason we set two variables for the speed and turning
//is so that the driving speed and turning speed doesn't have to be the same
//makes it 2-dimensional and easily customizable
float speedFactor = 1;
float turnFactor = .5;

void twerk() {
  // a for loop to make the robot shake back and forth 2 times
  for (int i = 0; i < 2; i++) {\
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



//for the back lift
void liftUp() {
  LiftMotor.spin(forward, 50, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonL1.pressing());
  LiftMotor.stop();
}

void liftDown() {
  LiftMotor.spin(reverse, 50, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonL2.pressing());
  LiftMotor.stop();
}

//for the claw
void clawUp() {
  ClawMotor.spin(reverse, 20, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonR1.pressing());
  ClawMotor.stop();
}

void clawDown() {
  ClawMotor.spin(forward, 20, pct);
  wait(25, msec);
  waitUntil(!Controller.ButtonR2.pressing());
  ClawMotor.stop();
}

int deadband = 15;
//used for the speedarr to loop through the array at lines around 300
int b = 0;
//the array of percentages you can set the robot's velocity at
float speedarr[4] = {0.95, .55, 0.40, 0.20};

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

void autonomous(void) {
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  backLiftMotors.resetRotation();
  wait(25, msec);

  // simple
  /*
  //goes forward while puttin the lift down
  leftDrive.spinToPosition(-1369.83, deg, 125, rpm, false);
  rightDrive.spinToPosition(-1369.83, deg, 125, rpm, false);
  backLiftMotors.spinToPosition(1870, deg, 200, rpm, true);
  wait(100, msec);
  //lifts up
  backLiftMotors.resetRotation();
  backLiftMotors.spinToPosition(-675, deg, 200, rpm, true);
  wait(100, msec);
  //goes back
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  leftDrive.spinToPosition(849.97, deg, 125, rpm, false);
  rightDrive.spinToPosition(849.97, deg, 125, rpm, true);
  wait(100, msec);
  //puts lift down
  backLiftMotors.resetRotation();
  backLiftMotors.spinToPosition(675, deg, 200, rpm, true);
  //goes down more
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  leftDrive.spinToPosition(316.11, deg, 125, rpm, false);
  rightDrive.spinToPosition(316.11, deg, 125, rpm, true);
  wait(100, msec);
  //turns a bit
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  leftDrive.spinToPosition(170, deg, 125, rpm, false);
  rightDrive.spinToPosition(-170, deg, 125, rpm, true);
  //goes forward
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  leftDrive.spinToPosition(-440.49, deg, 125, rpm, false);
  rightDrive.spinToPosition(-440.49, deg, 125, rpm, true);
  wait(100, msec);
  //lift up
  backLiftMotors.resetRotation();
  backLiftMotors.spinToPosition(-675, deg, 200, rpm, true);
  wait(100, msec);
  //goes back
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  leftDrive.spinToPosition(440.49, deg, 125, rpm, false);
  rightDrive.spinToPosition(440.49, deg, 125, rpm, true);
  //puts lift down
  backLiftMotors.resetRotation();
  backLiftMotors.spinToPosition(675, deg, 200, rpm, true);
*/
  // complicated
  
  //puts lift down and goes forward
  backLiftMotors.spinToPosition(1870, deg, 200, rpm, false);
  leftDrive.spinToPosition(-316.11, deg, 150, rpm, false);
  rightDrive.spinToPosition(-316.11, deg, 150, rpm, true);
  //turns a bit
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  leftDrive.spinToPosition(31, deg, 150, rpm, false);
  rightDrive.spinToPosition(-31, deg, 150, rpm, false);
  wait(100, msec);
  //goes forward a bit
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  leftDrive.spinToPosition(-849.97*1.25, deg, 150, rpm, false);
  rightDrive.spinToPosition(-849.97*1.25, deg, 150, rpm, true);
  //lifts up
  backLiftMotors.resetRotation();
  backLiftMotors.spinToPosition(-675, deg, 200, rpm, true);
  wait(100, msec);
  //goes back
  leftDrive.spinToPosition(200, deg, 150, rpm, false);
  rightDrive.spinToPosition(200, deg, 150, rpm, true);
  //puts lift down
  backLiftMotors.resetRotation();
  backLiftMotors.spinToPosition(675, deg, 200, rpm, true);
  

  wait(100, msec);
  backLiftMotors.stop(); 
  leftDrive.stop();
  rightDrive.stop();
}

void usercontrol(void) {
  while (true) {
    float speed = Controller.Axis3.position();
    axis4 = Controller.Axis4.position();
    float turnn = axis4;

    //set above
    speed = speed * speedFactor;
    //it's turn with two n's because turn is a pre built vex variable
    turnn = turnn * turnFactor;

    int LeftDriveSpeed = speed + turnn;
    int RightDriveSpeed = speed - turnn;
    int BackLiftSpeed = Controller.Axis2.position();

    if (abs(LeftDriveSpeed) < deadband) {
      leftDrive.setVelocity(0, percent);
    }
    else {
      //perct is set above as changable velocity
      leftDrive.setVelocity(LeftDriveSpeed * perct, percent);
    }

    if (abs(RightDriveSpeed) < deadband) {
      rightDrive.setVelocity(0, percent);
    }
    else {
      rightDrive.setVelocity(RightDriveSpeed * perct, percent);
    }

    //deadband for moving the joystick left and right so it doesn't turn
    //if you just twitch a tiny bit
    if (abs(Controller.Axis4.position()) < 2) {
      axis4 = 0;
    }
    else {
      axis4 = Controller.Axis4.position();
    }
    
    leftDrive.spin(forward);
    rightDrive.spin(forward);

    backLiftMotors.setVelocity(BackLiftSpeed * 0.7, pct);
    BackLift1.setVelocity(BackLiftSpeed * 0.7, pct);
    BackLift1.setVelocity(BackLiftSpeed * 0.7, pct);
    BackLift1.spin(reverse);
    BackLift2.spin(reverse);

    LiftMotor.setStopping(hold);
    ClawMotor.setStopping(hold);
    // backLiftMotors.setStopping(hold);
    BackLift1.setStopping(hold);
    BackLift2.setStopping(hold);

    //nudge right
    while (Controller.ButtonY.pressing()) {
      rightDrive.spin(forward, 10, pct);
      leftDrive.spin(reverse, 10, pct);
      wait(200, msec);
      rightDrive.stop();
      leftDrive.stop();
    }

    //nudge left
    while (Controller.ButtonA.pressing()) {
      rightDrive.spin(reverse, 10, pct);
      leftDrive.spin(forward, 10, pct);
      wait(200, msec);
      rightDrive.stop();
      leftDrive.stop();
    }

    //goes straight back so it's easier to go up the ramp
    while (Controller.ButtonB.pressing()) {
      rightDrive.spin(reverse, 40, pct);
      leftDrive.spin(reverse, 40, pct);
      int BackLiftSpeed = Controller.Axis2.position();
      backLiftMotors.setVelocity(BackLiftSpeed * 0.7, pct); 
      backLiftMotors.setStopping(hold);
      wait(50, msec);
      rightDrive.stop();
      leftDrive.stop();
      
    }


    while (Controller.ButtonX.pressing()) {
      //defined above
      twerk();
      wait(25, msec);
    }

    Controller.ButtonL1.pressed(liftUp);
    Controller.ButtonL2.pressed(liftDown);

    Controller.ButtonR1.pressed(clawUp);
    Controller.ButtonR2.pressed(clawDown);


    //b is used to loop through the speedarr[]
    //and speedarr[] contains percentages which will be multiplied to the driving velocity
    //so the driver can change the robot's speed in real time
    if (Controller.ButtonDown.pressing()) {
      if (b >= 3) {
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
      if (b <= 0) {
        wait(100, msec);
        b = 3;
      }
      else {
        b -= 1;
        wait(100, msec);
      }
      perct = speedarr[b];
    }

    //prints what percentage the driving speed is at
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("     %.2f", perct);
    wait(25, msec);
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function
  pre_auton();

  while (true) {
    wait(100, msec);
  }
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
////////////////////////////////////////////////////////////////////////////                        ______                _____                 _____              
////////////////////////////////////////////////////////////////////////////         |         |   |      |    |\    /|  /     \  |\    /|     /             /\     \   /
/////////////////////////////////////////////////////////////////////////////        |         |   |______|    | \  / | |       | | \  / |    |             /  \     \ /
//////////////////////////////////////////////////////////////////////////////       |         |   |  \        |  \/  | |       | |  \/  |    |    ___     /____\     |
//////////////////////////////////////////////////////////////////////////////       |         |   |   \       |      | |       | |      |    |       |   /      \    |
//////////////////////////////////////////////////////////////////////////////        \_______/    |    \      |      |  \_____/  |      |     \_____/   /        \   |
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
///////////////////////////////             ////////////////////////////////          //////////////////////
///////////////////////////////             ////////////////////////////////          //////////////////////
///////////////////////////////             ///////////////////////////////            ////////////////////
///////////////////////////////             ///////////////////////////////             ///////////////////
 //////////////////////////////              ////////////////////////////               ////////  ////////
  ///////////////////////////                  /////////////////////////                 //////    //////

