// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <iostream>

void Robot::RobotInit() {
  std::cout << "starting" << std::endl;
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit() {
  shootButtonTrigger.WhenPressed(nullptr);
  intakeButtonTrigger.WhenPressed(nullptr);
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  m_commandUserDrive.Schedule();
  shootButtonTrigger.WhenPressed(&m_shootCommand,false);
  intakeButtonTrigger.WhenPressed(&m_intakeCommand,false);
  std::cout << "Telopinit" << std::endl;
}

void Robot::TeleopPeriodic() {
  std::cout << "Telopinit schedule: " << frc2::CommandScheduler::GetInstance().IsScheduled(&m_intakeCommand) << std::endl;
}

void Robot::TeleopExit(){
  m_commandUserDrive.Cancel();
  shootButtonTrigger.WhenPressed(nullptr);
  intakeButtonTrigger.WhenPressed(nullptr);
}

void Robot::TestInit() {
  shootButtonTrigger.WhenPressed([this](){
    std::cout << m_shooterIntake.getBreakBeam1() << std::endl;
  });
  intakeButtonTrigger.WhenPressed([this](){
    std::cout << m_shooterIntake.getBreakBeam2() << std::endl;
  });
}
  
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif