// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/GenericHID.h>
#include "Constants.h"
#include "subsystems/Drivetrain.h"
#include "commands/DrivetrainCommands.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  frc::GenericHID driverPad1{port};
  Drivetrain m_drivetrain{leftMotor1 ,leftMotor2 ,rightMotor1 ,rightMotor2};
  CommandUserDrive m_commandUserDrive{&m_drivetrain,driverPad1};
};