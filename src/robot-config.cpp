#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller DriverController = controller(primary);
controller OperatorController = controller(partner);
motor BackLeftDriveMotor = motor(PORT19, ratio18_1, false);
motor FrontLeftDriveMotor = motor(PORT18, ratio18_1, false);
motor BackRightDriveMotor = motor(PORT11, ratio18_1, false);
motor FrontRightDriveMotor = motor(PORT12, ratio18_1, false);
motor RightIntakeRoller = motor(PORT13, ratio18_1, false);
motor LeftIntakeRoller = motor(PORT16, ratio18_1, false);
motor IntakeRollerUpDown = motor(PORT14, ratio36_1, false);
motor RallUpDown = motor(PORT20, ratio36_1, false);
gyro Gyro = gyro(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}