#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

motor LeftFrontMotor = motor(PORT10, ratio18_1, false);      
motor LeftBackMotor = motor(PORT17, ratio18_1, false);        // T/F not checked
motor_group LeftDrive(LeftFrontMotor, LeftBackMotor);

motor RightFrontMotor = motor(PORT1, ratio18_1, true);
motor RightBackMotor = motor(PORT16, ratio18_1, true);           // T/F not checked
motor_group RightDrive(RightFrontMotor, RightBackMotor);

motor LeftLiftMotor = motor(PORT1, ratio18_1, true);  
motor RightLiftMotor = motor(PORT4, ratio18_1, false);  
motor_group LiftMotors(LeftLiftMotor, RightLiftMotor);

drivetrain Drivetrain = drivetrain(LeftDrive, RightDrive, 319.19, 295, 40, mm, 1);

motor ArmMotor = motor(PORT19, ratio18_1, false);       // T/F not checked
motor ClawMotor = motor(PORT18, ratio18_1, false);       // T/F not checked

controller Controller1 = controller();
// VEXcode generated functions

/**
* Used to initialize code/tasks/devices added using tools in VEXcode Pro.
*
* This should be called at the start of your int main function.
*/
void vexcodeInit(void) {
  // nothing to initialize
}
