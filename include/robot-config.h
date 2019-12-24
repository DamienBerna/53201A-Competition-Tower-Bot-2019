using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller driverController;
extern controller operatorController;
extern motor leftDriveMotor1;
extern motor leftDriveMotor2;
extern motor rightDriveMotor1;
extern motor rightDriveMotor2;
extern motor leftIntakeRoller;
extern motor rightIntakeRoller;
extern motor leftLiftMotor;
extern motor rightLiftMotor;
extern pot leftLiftPot;
extern pot rightLiftPot;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );