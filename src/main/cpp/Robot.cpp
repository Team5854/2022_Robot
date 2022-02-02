#include <iostream>

#include "Robot.h"
#include "Drivetrain.h"


void Robot::RobotInit() {
  std::cout << "Starting" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  if(driverPad1.GetRawButton(boostButton)) driveTrain.Set(Drivetrain::PercentRange(boost*accelMod*driverPad1.GetRawAxis(accelerationAxis)),Drivetrain::PercentRange(turnMod*driverPad1.GetRawAxis(steeringAxis)));
  else driveTrain.Set(accelMod*driverPad1.GetRawAxis(accelerationAxis),turnMod*driverPad1.GetRawAxis(steeringAxis));
}

void Robot::DisabledInit() {
  usbSensorHub.Write("f");
  std::cout << "I just ran write oppeartion with f" << std::endl;
}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {
  usbSensorHub.Write("t");
  std::cout << "I just ran write opperation with t" << std::endl;
}

void Robot::TestPeriodic() {
  if(driverPad1.GetRawButton(shootButton)) shooterMotor.Set(1);
  else shooterMotor.Set(0);
}

#ifndef RUNNING_FRC_TESTS

int main() {
  return frc::StartRobot<Robot>();
}
#endif
