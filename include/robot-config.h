using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller DriverController;
extern controller OperatorController;
extern motor BackLeftDriveMotor;
extern motor FrontLeftDriveMotor;
extern motor BackRightDriveMotor;
extern motor FrontRightDriveMotor;
extern motor RightIntakeRoller;
extern motor LeftIntakeRoller;
extern motor IntakeRollerUpDown;
extern motor RallUpDown;
extern gyro Gyro;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );