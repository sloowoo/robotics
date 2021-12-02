using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftMotor;
extern motor RightMotor;
extern motor ClawMotor;
extern motor ArmMotor;
extern motor_group LeftDrive;
extern motor_group RightDrive;
extern drivetrain Drivetrain;
/**
* Used to initialize code/tasks/devices added using tools in VEXcode Pro.
*
* This should be called at the start of your int main function.
*/
void vexcodeInit(void);
