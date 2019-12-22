/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  BackLeftDriveMotor.stop(hold);
  FrontLeftDriveMotor.stop(hold);
  BackRightDriveMotor.stop(hold);
  FrontRightDriveMotor.stop(hold);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  RallUpDown.spin(reverse, 100, rpm); //Calibrate and filp out rail
  wait(1800, msec);
  RallUpDown.setRotation(99, degrees);
  
  IntakeRollerUpDown.rotateTo(-900, degrees, 100, rpm); //Filp out arms

  RallUpDown.rotateTo(325, degrees, 50, rpm, false); //Home rall
  IntakeRollerUpDown.rotateTo(-750, degrees, 100, rpm); //Home arms

  RightIntakeRoller.spin(reverse, 200, rpm); //Start rollers
  LeftIntakeRoller.spin(forward, 200, rpm);
  
  BackLeftDriveMotor.rotateTo(666, degrees, 100, rpm, false); //Forward to cubes
  FrontLeftDriveMotor.rotateTo(-666, degrees, 100, rpm, false);
  BackRightDriveMotor.rotateTo(-666, degrees, 100, rpm, false);
  FrontRightDriveMotor.rotateTo(666, degrees, 100, rpm);

  BackLeftDriveMotor.rotateTo(952, degrees, 50, rpm, false); //Forward slow to stacked cubes
  FrontLeftDriveMotor.rotateTo(-952, degrees, 50, rpm, false);
  BackRightDriveMotor.rotateTo(-952, degrees, 50, rpm, false);
  FrontRightDriveMotor.rotateTo(952, degrees, 50, rpm);  
  
  BackLeftDriveMotor.stop(coast); //Stop all motors to prepare for operator control 
  FrontLeftDriveMotor.stop(coast);
  BackRightDriveMotor.stop(coast);
  FrontRightDriveMotor.stop(coast);
  RightIntakeRoller.stop();
  LeftIntakeRoller.stop();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//Tasks

int autoCubePlace() {
  while (true) {
    
    wait(10, msec);
  }
  return 0;
}

int arm() {
  int operatorJoystickAxis2;
  bool operatorJoystickAxis2Disable = true;
  
  while (true) {
    //Operator Joystick Axis 2
    if (abs (OperatorController.Axis2.value()) > 5) {
      operatorJoystickAxis2Disable = false;
      operatorJoystickAxis2 = OperatorController.Axis2.value();
    }
    else {
      operatorJoystickAxis2 = 0;
      operatorJoystickAxis2Disable = true;
    }

    //Arms joystick control
    if (operatorJoystickAxis2Disable == false) {
      IntakeRollerUpDown.spin(forward ,(-operatorJoystickAxis2 / 4), percent);
    }
    else if (OperatorController.ButtonB.pressing()) { //Home
      IntakeRollerUpDown.rotateTo(-750, degrees, 25, rpm, false);
    }
    else if (OperatorController.ButtonA.pressing()) { //Low goal
      IntakeRollerUpDown.rotateTo(-1150, degrees, 25, rpm, false);
    }
    else if (OperatorController.ButtonX.pressing()) { //High goal
      IntakeRollerUpDown.rotateTo(-1275, degrees, 25, rpm, false);
    }
    else {
      IntakeRollerUpDown.stop(hold);
    }
    
    wait(10, msec);
  }
  return 0;
}

bool diverAnalogRollerControl = false;

void  driverRollerToggle() {
  diverAnalogRollerControl = !diverAnalogRollerControl;
}

bool rollerOutOnOff = false;

void  rollerOutToggle() {
  rollerOutOnOff = !rollerOutOnOff;
}

bool rollerInOnOff = false;

void  rollerInToggle() {
  rollerInOnOff = !rollerInOnOff;
}

void usercontrol(void) {

  int driverJoystickAxis1;
  int driverJoystickAxis2;
  int driverJoystickAxis3;
  int driverJoystickAxis4;

  int operatorJoystickAxis1;
  int operatorJoystickAxis2;
  int operatorJoystickAxis3;
  int operatorJoystickAxis4;

  bool driverJoystickAxis1Disable = true;
  bool driverJoystickAxis2Disable = true;
  bool driverJoystickAxis3Disable = true;
  bool driverJoystickAxis4Disable = true;

  bool operatorJoystickAxis1Disable = true;
  bool operatorJoystickAxis2Disable = true;
  bool operatorJoystickAxis3Disable = true;
  bool operatorJoystickAxis4Disable = true;

  //bool operatorDisable = false;
  //bool driverDisable = false;

  task arms = task(arm);
  
  // User control code here, inside the loop
  while (1) {
    //Dead zone check
    //Driver Joystick Axis 1
    if (abs (DriverController.Axis1.value()) > 5) {
      driverJoystickAxis1Disable = false;
      driverJoystickAxis1 = DriverController.Axis1.value();
    }
    else {
      driverJoystickAxis1 = 0;
      driverJoystickAxis1Disable = true;
    }

    //Driver Joystick Axis 2
    if (abs (DriverController.Axis2.value()) > 5) {
      driverJoystickAxis2Disable = false;
      driverJoystickAxis2 = DriverController.Axis2.value();
    }
    else {
      driverJoystickAxis2 = 0;
      driverJoystickAxis2Disable = true;
    }

    //Driver Joystick Axis 3
    if (abs (DriverController.Axis3.value()) > 5) {
      driverJoystickAxis3Disable = false;
      driverJoystickAxis3 = DriverController.Axis3.value();
    }
    else {
      driverJoystickAxis3 = 0;
      driverJoystickAxis3Disable = true;
    }

    //Driver Joystick Axis 4
    if (abs (DriverController.Axis4.value()) > 5) {
      driverJoystickAxis4Disable = false;
      driverJoystickAxis4 = DriverController.Axis4.value();
    }
    else {
      driverJoystickAxis4 = 0;
      driverJoystickAxis4Disable = true;
    }

    //Operator Joystick Axis 1
    if (abs (OperatorController.Axis1.value()) > 5) {
      operatorJoystickAxis1Disable = false;
      operatorJoystickAxis1 = OperatorController.Axis1.value();
    }
    else {
      operatorJoystickAxis1 = 0;
      operatorJoystickAxis1Disable = true;
    }

    //Operator Joystick Axis 2
    if (abs (OperatorController.Axis2.value()) > 5) {
      operatorJoystickAxis2Disable = false;
      operatorJoystickAxis2 = OperatorController.Axis2.value();
    }
    else {
      operatorJoystickAxis2 = 0;
      operatorJoystickAxis2Disable = true;
    }

    //Operator Joystick Axis 3
    if (abs (OperatorController.Axis3.value()) > 5) {
      operatorJoystickAxis3Disable = false;
      operatorJoystickAxis3 = OperatorController.Axis3.value();
    }
    else {
      operatorJoystickAxis3 = 0;
      operatorJoystickAxis3Disable = true;
    }

    //Operator Joystick Axis 4
    if (abs (OperatorController.Axis4.value()) > 5) {
      operatorJoystickAxis4Disable = false;
      operatorJoystickAxis4 = OperatorController.Axis4.value();
    }
    else {
      operatorJoystickAxis4 = 0;
      operatorJoystickAxis4Disable = true;
    }

    //Drive

    DriverController.ButtonA.pressed( driverRollerToggle );

    if (diverAnalogRollerControl == true) {
      FrontLeftDriveMotor.spin(reverse, (driverJoystickAxis3 + driverJoystickAxis4), percent);
      BackLeftDriveMotor.spin(reverse, (-driverJoystickAxis3 + driverJoystickAxis4), percent);
      FrontRightDriveMotor.spin(forward, (driverJoystickAxis3 - driverJoystickAxis4), percent);
      BackRightDriveMotor.spin(forward, (-driverJoystickAxis3 - driverJoystickAxis4), percent);
    }
    else {
      FrontLeftDriveMotor.spin(reverse, (driverJoystickAxis3 + driverJoystickAxis4 + driverJoystickAxis1), percent);
      BackLeftDriveMotor.spin(reverse, (-driverJoystickAxis3 + driverJoystickAxis4 - driverJoystickAxis1), percent);
      FrontRightDriveMotor.spin(forward, (driverJoystickAxis3 - driverJoystickAxis4 - driverJoystickAxis1), percent);
      BackRightDriveMotor.spin(forward, (-driverJoystickAxis3 - driverJoystickAxis4 + driverJoystickAxis1), percent);
    }
    
    //Rail
    if (operatorJoystickAxis3Disable == false) {
      RallUpDown.spin(forward, (-operatorJoystickAxis3 / 4), percent);
    }
    else {
      RallUpDown.stop(hold);
    }

    //Rollers
    if (OperatorController.ButtonR1.pressing()) {
      RightIntakeRoller.spin(forward, 200, rpm);
      LeftIntakeRoller.spin(reverse, 200, rpm);
    }
    else if (OperatorController.ButtonR2.pressing()) {
      RightIntakeRoller.spin(reverse, 200, rpm);
      LeftIntakeRoller.spin(forward, 200, rpm);
    }
    else {
      RightIntakeRoller.stop();
      LeftIntakeRoller.stop();
    }
    /*DriverController.ButtonR1.pressed( rollerInToggle );
    DriverController.ButtonR2.pressed( rollerOutToggle );
    if (rollerOutOnOff == true) {
      RightIntakeRoller.spin(reverse, 200, rpm);
      LeftIntakeRoller.spin(forward, 200, rpm);
    }
    if (rollerInOnOff == true) {
      RightIntakeRoller.spin(forward, 200, rpm);
      LeftIntakeRoller.spin(reverse, 200, rpm);
    }
    else if (diverAnalogRollerControl) {
      RightIntakeRoller.spin(forward, driverJoystickAxis2, percent);
      LeftIntakeRoller.spin(reverse, driverJoystickAxis2, percent);
    }*/


/*
    if (abs (DriverController.Axis2.value()) > 5) {
      driverJoystickAxis2Disable = false;
      driverJoystickAxis2 = DriverController.Axis2.value();
    }
    else {
      driverJoystickAxis2 = 0;
      driverJoystickAxis2Disable = true;
    }
    */

/*    void deadZoneCheck()
{

	if(abs(vexRT[Ch2]) > threshold)
		Channel2 = vexRT[Ch2];
	else
		Channel2 = 0;

	if(abs(vexRT[Ch3]) > threshold)
		Channel3 = vexRT[Ch3];
	else
		Channel3 = 0;
}*/

    /*if(OperatorController.ButtonL2.pressing()){
        IntakeRollerUpDown.spin(directionType::fwd,100,velocityUnits::rpm);
      }else if (OperatorController.ButtonL1.pressing()) {
        IntakeRollerUpDown.spin(directionType::rev,100,velocityUnits::rpm);
      }else{
        IntakeRollerUpDown.stop(brakeType::hold);
      }*/
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(5, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
