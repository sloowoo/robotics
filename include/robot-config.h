using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftFrontMotor;
extern motor LeftBackMotor;
extern motor RightFrontMotor;
extern motor RightBackMotor;
extern motor_group LeftDrive;
extern motor_group RightDrive;
extern motor LeftLiftMotor;
extern motor RightLiftMotor;
extern motor_group LiftMotors;
extern drivetrain Drivetrain;
/**
* Used to initialize code/tasks/devices added using tools in VEXcode Pro.
*
* This should be called at the start of your int main function.
*/
void vexcodeInit(void);