// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

void Robot::RobotInit() {}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit() {
  m_commandUserDrive.Cancel();
}

void Robot::DisabledPeriodic() {};

void Robot::AutonomousInit() {
  m_commandUserDrive.Cancel();
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  m_commandUserDrive.Schedule();
}

void Robot::TeleopPeriodic() {}

void Robot::TestInit() {
  m_commandUserDrive.Cancel();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
