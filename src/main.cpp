#include "vex.h"
#include "string.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace vex;


//motors
motor frontLeftMotor = motor(PORT10, ratio18_1, true);
motor frontRightMotor = motor(PORT1, ratio18_1, false);
motor backLeftMotor = motor(PORT17, ratio18_1, true);
motor backRightMotor = motor(PORT16, ratio18_1, false);
motor ArmMotor1 = motor(PORT19, ratio18_1, true);   
motor ArmMotor2 = motor(PORT8, ratio18_1, false);        // T/F not checked
motor ClawMotor = motor(PORT18, ratio18_1, false);       // T/F not checked


//motor groups
motor_group leftDrive = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightDrive = motor_group(frontRightMotor,backRightMotor);
motor_group armMotors = motor_group(ArmMotor1, ArmMotor2);


//drivetrain
drivetrain Drivetrain = drivetrain(leftDrive, rightDrive, 320, 320, 130, mm, 1);


//controller
controller Controller = controller();


//global variables
bool menu = true;
bool record = false;
bool startRecord = false;
bool deadZoneCheck = true;
bool hasStarted = false;
bool shouldEndFirst = false;
bool driveCancel = false;
bool replayFinished = false;
bool replayEnd = false;
bool stopLoop = true;

float speedFactor = 0.5;
float turnFactor = 0.8;

int speedDeadZone = 15;
int turnDeadZone = 5;
int speedDeadZoneNeg = speedDeadZone * -1;
int turnDeadZoneNeg = turnDeadZone * -1;
int runLoc = 0;
int runLocCheck = 0;

//vectors
std::vector<double> leftSide;
std::vector<double> rightSide;
std::vector<double> claw;
std::vector<double> arm;


// Define Function
void recordSystem();
void replaySystem();
void driverSystem();
void recordCheck();
void checkReplay();


// Main
int main() {
  vexcodeInit();

  //menu is defined as true above (we have no idea why we couldn't just do while (true))
  while (menu) {
    shouldEndFirst = false;

    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("Menu:");

    if (Controller.ButtonUp.pressing()) {
      task::sleep(250);
      recordCheck();
    }

    else if (Controller.ButtonRight.pressing()) {
      task::sleep(250);
      checkReplay();
    }

    else if (Controller.ButtonLeft.pressing()) {
      task::sleep(250);
      driverSystem();
    }

    task::sleep(20);

  }
  
}



// ACTUAL FUNCTIONS START

void recordCheck() {
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("Are you sure you");
  Controller.Screen.setCursor(2, 1);
  Controller.Screen.print("want to record?");

  task::sleep(250);

  while (true) {

    //basically, if this proccess is already done then return the control to the calling function
    if (shouldEndFirst) {
      return;
    }

    //start recording
    if (Controller.ButtonUp.pressing()) {
      startRecord = true;
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Recording Started");
      task::sleep(250);
    }
    
    //cancel recording
    else if (Controller.ButtonDown.pressing()) {
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Recording Canceled");
      startRecord = false;
      task::sleep(1000);
      return;
    }

    //if startRecord = true then starts the recording proccess
    if (startRecord) {
      //records the controller positions
      int controller3Pos = Controller.Axis3.position();
      int controller1Pos = Controller.Axis1.position();

      int test3Pos = abs(controller3Pos);
      int test1Pos = abs(controller1Pos);

      //these deadzone lines make it so that the controller doesn't record until the driver actually leaves the deadzone
      if (test3Pos > speedDeadZone) {
        startRecord = false;
        recordSystem();
      }

      else if (test1Pos > turnDeadZone) {
        startRecord = false;
        recordSystem();
      }
    }
  }
}

//recording code
void recordSystem() {
  //put in timer so that the timing is exact in the recording
  timer::event(recordSystem, 40);

  //used double variables for more accurate numbers
  double speed, turn;
  double left, right;

  //driving code
  while (true) {
    speed = Controller.Axis3.position();
    turn = Controller.Axis1.position();
    double armPos = Controller.Axis2.position();
    double clawOpen = Controller.ButtonR1.pressing();
    double clawClose = Controller.ButtonR2.pressing();
    clawClose = clawClose * -1;
    double clawFull = clawClose + clawOpen;

    if (deadZoneCheck == true) {
      

      if (speed > 0 && speed < speedDeadZone) {
        speed = 0;
      }

      else if (speed < 0 && speed > speedDeadZoneNeg) {
        speed = 0;
      }


      if (turn > 0 && turn < turnDeadZone) {
        turn = 0;
      }

      else if (turn < 0 && turn > turnDeadZoneNeg) {
        turn = 0;
      }

    }


    speed = speedFactor * speed;
    turn = turnFactor * turn;

    left = speed + turn;
    right = speed - turn;

    leftSide.push_back(left);
    rightSide.push_back(right);
    claw.push_back(clawFull);
    arm.push_back(armPos);

    leftDrive.spin(directionType::rev, left, velocityUnits::pct);
    rightDrive.spin(directionType::rev, right, velocityUnits::pct);
    //basically saying that there is a recording that's created
    hasStarted = true;

    //ends recording
    if (Controller.ButtonDown.pressing()) {
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Recording Ended");
      shouldEndFirst = true;
      task::sleep(1000);
      return;
    }

    task::sleep(100);

  }

}

//replays the recording
void checkReplay() {
  //error test
  while (true) {
    Controller.Screen.setCursor(3, 1);
    Controller.Screen.print("tests");

    if (replayFinished) {
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(3 ,1);
      Controller.Screen.print("Exiting");
      hasStarted = false;
      task::sleep(1000);
      return;
    }
    
    //check if theres a recording that exists, if so, play the recording
    else if (hasStarted) {
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Replaying Recording");
      vex::task::sleep(500);
      replaySystem();
    }

    //if not, then tell the user there is nothing to replay
    else if (hasStarted == false) {
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("Nothing to Replay");
      vex::task::sleep(1000);
      return;
    }
  }
}

//replaying code
void replaySystem() {
  //if (stopLoop) {
  timer::event(replaySystem, 40);
  //}


  while (true) {
    double & left = leftSide.at(runLoc);
    double & right = rightSide.at(runLoc);
    double & armPos = arm.at(runLoc);
    double & clawFull = claw.at(runLoc);

    leftDrive.spin(directionType::rev, left, velocityUnits::pct);
    rightDrive.spin(directionType::rev, right, velocityUnits::pct);
    ClawMotor.spin(directionType::rev, clawFull, velocityUnits::pct);
    ArmMotor1.spin(directionType::rev, armPos, velocityUnits::pct);
    ArmMotor2.spin(directionType::rev, armPos, velocityUnits::pct);

    //adds 1 per time to the array/vector/whatever so that it can retreive the correct things from the list
    runLoc += 1;

    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print(runLoc);

    runLocCheck = runLoc + 2;

    if (Controller.ButtonDown.pressing()) {
      replayFinished = true;
      return;
    }

    task::sleep(100);

  }

}

//normal driving
void driverSystem() {
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("Driver Control");

  while(true) {

    float speed = Controller.Axis3.position();
    float turn = Controller.Axis1.position();

    
    if (deadZoneCheck == true) {

      if (speed > 0 && speed < speedDeadZone) {
        speed = 0;
      }

      else if (speed < 0 && speed > speedDeadZoneNeg) {
        speed = 0;
      }


      if (turn > 0 && turn < turnDeadZone) {
        turn = 0;
      }

      else if (turn < 0 && turn > turnDeadZoneNeg) {
        turn = 0;
      }

    }

    speed = speedFactor * speed;
    turn = turnFactor * turn;

    float right = speed - turn;
    float left = speed + turn;

    leftDrive.spin(directionType::rev, left, velocityUnits::pct);
    rightDrive.spin(directionType::rev, right, velocityUnits::pct);

    if (Controller.ButtonDown.pressing()) {
      //driveCancel = true;
      Controller.Screen.clearScreen();
      Controller.Screen.setCursor(1 ,1);
      Controller.Screen.print("Ending Driver Control");
      task::sleep(1000);
      return;
    }

  }
}

// ACTUAL FUNCTIONS END
