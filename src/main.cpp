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

/*
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
}*/

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

  double Liftkp = 0.7;//Mecanum Wheel val:0.75
  double Liftki = 0.0001;//Mecanum Wheel val:0.0001
  double Liftkd = 5;//Mecanum Wheel val:5
  int Lifterror;
  int Liftintegral;
  int Liftderivative;
  int LiftPIDOut;
  int LiftLastError;

  //bool operatorDisable = false;
  //bool driverDisable = false;

  //task arms = task(arm);
  
  // User control code here, inside the loop
  while (1) {
    //Dead zone check
    //Driver Joystick Axis 1
    if (abs (driverController.Axis1.value()) > 5) {
      driverJoystickAxis1Disable = false;
      driverJoystickAxis1 = driverController.Axis1.value();
    }
    else {
      driverJoystickAxis1 = 0;
      driverJoystickAxis1Disable = true;
    }

    //Driver Joystick Axis 2
    if (abs (driverController.Axis2.value()) > 5) {
      driverJoystickAxis2Disable = false;
      driverJoystickAxis2 = driverController.Axis2.value();
    }
    else {
      driverJoystickAxis2 = 0;
      driverJoystickAxis2Disable = true;
    }

    //Driver Joystick Axis 3
    if (abs (driverController.Axis3.value()) > 5) {
      driverJoystickAxis3Disable = false;
      driverJoystickAxis3 = driverController.Axis3.value();
    }
    else {
      driverJoystickAxis3 = 0;
      driverJoystickAxis3Disable = true;
    }

    //Driver Joystick Axis 4
    if (abs (driverController.Axis4.value()) > 5) {
      driverJoystickAxis4Disable = false;
      driverJoystickAxis4 = driverController.Axis4.value();
    }
    else {
      driverJoystickAxis4 = 0;
      driverJoystickAxis4Disable = true;
    }

    //Operator Joystick Axis 1
    if (abs (operatorController.Axis1.value()) > 5) {
      operatorJoystickAxis1Disable = false;
      operatorJoystickAxis1 = operatorController.Axis1.value();
    }
    else {
      operatorJoystickAxis1 = 0;
      operatorJoystickAxis1Disable = true;
    }

    //Operator Joystick Axis 2
    if (abs (operatorController.Axis2.value()) > 5) {
      operatorJoystickAxis2Disable = false;
      operatorJoystickAxis2 = operatorController.Axis2.value();
    }
    else {
      operatorJoystickAxis2 = 0;
      operatorJoystickAxis2Disable = true;
    }

    //Operator Joystick Axis 3
    if (abs (operatorController.Axis3.value()) > 5) {
      operatorJoystickAxis3Disable = false;
      operatorJoystickAxis3 = operatorController.Axis3.value();
    }
    else {
      operatorJoystickAxis3 = 0;
      operatorJoystickAxis3Disable = true;
    }

    //Operator Joystick Axis 4
    if (abs (operatorController.Axis4.value()) > 5) {
      operatorJoystickAxis4Disable = false;
      operatorJoystickAxis4 = operatorController.Axis4.value();
    }
    else {
      operatorJoystickAxis4 = 0;
      operatorJoystickAxis4Disable = true;
    }

    //Drive
    leftDriveMotor1.spin(forward, (driverJoystickAxis3 + driverJoystickAxis1), percent);
    leftDriveMotor2.spin(forward, (driverJoystickAxis3 + driverJoystickAxis1), percent);
    rightDriveMotor1.spin(forward, (driverJoystickAxis3 - driverJoystickAxis1), percent);
    rightDriveMotor1.spin(forward, (driverJoystickAxis3 - driverJoystickAxis1), percent);

    //Rollers
    if (driverController.ButtonR1.pressing()) {
      leftIntakeRoller.spin(forward, 200, rpm);
      rightIntakeRoller.spin(reverse, 200, rpm);
    }
    else if (driverController.ButtonR2.pressing()) {
      leftIntakeRoller.spin(reverse, 200, rpm);
      rightIntakeRoller.spin(forward, 200, rpm);
    }
    else {
      leftIntakeRoller.stop();
      rightIntakeRoller.stop();
    }

    //Lift
    if (operatorController.ButtonL2.pressing()) {
      leftLiftMotor.spin(forward, operatorJoystickAxis2, percent);
      rightLiftMotor.spin(forward, operatorJoystickAxis2, percent);
    }
    else {
      Liftintegral = Liftintegral + Lifterror;
      Liftderivative = Lifterror - LiftLastError;
      LiftPIDOut = (Liftkp * Lifterror) + (Liftki * Liftintegral) + (Liftkd * Liftderivative);
      LiftLastError = Lifterror;
    }

    wait(5, msec);
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
