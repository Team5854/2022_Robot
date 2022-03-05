// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/GenericHID.h>
#include <frc2/command/button/JoystickButton.h>

#include "Constants.h"
#include "subsystems/Drivetrain.h"
#include "commands/DrivetrainCommands.h"
#include "subsystems/ShooterIntake.h"
#include "commands/ShooterIntakeCommands.h"

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
  void TeleopExit() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  frc::GenericHID m_driverPad1{port};
  frc::Compressor m_compressor{compressorId, frc::PneumaticsModuleType::CTREPCM};

  Drivetrain m_drivetrain{leftFalconLeadId, leftFalconFollowId, rightFalconLeadId, rightFalconFollowId};
  ShooterIntake m_shooterIntake{stage3SparkId, stage2TalonId, stage1TalonId, m_compressor, solenoidPort, 0, 1,{0,0,0}};

  CommandUserDrive m_commandUserDrive{&m_drivetrain, m_driverPad1};
  IntakeCommand m_intakeCommand{&m_shooterIntake, m_driverPad1};
  ShootCommand m_shootCommand{&m_shooterIntake, m_driverPad1};

  frc2::JoystickButton shootButtonTrigger{&m_driverPad1, shootButton};
  frc2::JoystickButton intakeButtonTrigger{&m_driverPad1, intakeButton};
};