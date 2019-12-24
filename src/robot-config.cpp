#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller driverController = controller(primary);
controller operatorController = controller(partner);
motor leftDriveMotor1 = motor(PORT10, ratio18_1, false);
motor leftDriveMotor2 = motor(PORT9, ratio18_1, true);
motor rightDriveMotor1 = motor(PORT1, ratio18_1, true);
motor rightDriveMotor2 = motor(PORT2, ratio18_1, false);
motor leftIntakeRoller = motor(PORT7, ratio18_1, false);
motor rightIntakeRoller = motor(PORT4, ratio18_1, true);
motor leftLiftMotor = motor(PORT8, ratio18_1, false);
motor rightLiftMotor = motor(PORT3, ratio18_1, false);
pot leftLiftPot = pot(Brain.ThreeWirePort.G);
pot rightLiftPot = pot(Brain.ThreeWirePort.H);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}