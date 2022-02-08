// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include "Drivetrain.h"
#include <frc/GenericHID.h>
#include <frc/SerialPort.h>
#include <rev/CANSparkMax.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include <ctime>

const double accelMod = -.5;
const double turnMod = .6;
const double boost = 3.5;
enum gamePadConfig {
  port = 0,
  accelerationAxis = 1,
  steeringAxis = 2,
  leftDriveAxis = 1,
  rightDriveAxis = 3,
  boostButton = 3,
  shootButton = 4,
  sendT = 1,
  sendF = 2,
  piston = 7
};


class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  bool arduino = false;
  TankDrive driveTrain{{3,4},{1,2}};
  frc::GenericHID driverPad1{port};
  frc::SerialPort usbSensorHub{230400,frc::SerialPort::Port::kUSB};
  frc::Compressor Compressor{6,frc::PneumaticsModuleType::CTREPCM};
  frc::DoubleSolenoid DoubleSolenoid{6,frc::PneumaticsModuleType::CTREPCM,2,3};
  rev::CANSparkMax shooterMotor1{9,rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  TalonFX shooterMotor{8};
  std::clock_t time;
};