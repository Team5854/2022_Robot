#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <iostream>
#include <rev/CANSparkMax.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <ctime>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Constants.h"
#include "subsystems/Arduino.h"

class ShooterIntake : public frc2::SubsystemBase {
 public:
  ShooterIntake(int shooterLead, int shooterFollow, int stage2, int stage1, frc::Compressor& compressor, int solenoid, Arduino& ledController, int breakbeam1, int breakbeam2,std::initializer_list<bool> motorConfigs);
  void setIntake(bool upDown);
  void stage1Run(double speed);
  void stage2Run(double speed);
  void shootRun(double speed);
  int setLeds(int state);
  bool getBreakBeam1();
  bool getBreakBeam2();
  void setPid(double kF, double kP, double kI, double kD);
  void setMotorPoint(double setpoint);
  void Periodic();

  bool m_balls[2] = {false,false};
  frc::ShuffleboardTab& shooterConfigTab = frc::Shuffleboard::GetTab("Shooter Configs");
  nt::NetworkTableEntry setPoint = shooterConfigTab.Add("Low speed", k_shootSpeed).GetEntry();
  nt::NetworkTableEntry setPointHigh = shooterConfigTab.Add("High speed", k_shootSpeedHigh).GetEntry();
  nt::NetworkTableEntry shooterStartTime = shooterConfigTab.Add("Shooter spin-up time:", k_shootStartTime).GetEntry();
  nt::NetworkTableEntry shotsDelay = shooterConfigTab.Add("Shot delay time:", k_shootStartTime).GetEntry();
  nt::NetworkTableEntry defaultSensors = shooterConfigTab.Add("Default sensors: ", sensorsDefaulted).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry();
  nt::NetworkTableEntry highLow = shooterConfigTab.Add("Enable highshot: ", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry();
  
 private:
  rev::CANSparkMax m_shooterLead;
  rev::CANSparkMax m_shooterFollow;
  TalonSRX m_stage2;
  TalonSRX m_stage1;
  frc::Compressor& m_compressor;
  frc::Solenoid m_solenoid;
  Arduino& m_ledController;
  frc::DigitalInput m_breakBeam1;
  frc::DigitalInput m_breakBeam2;
  rev::SparkMaxPIDController m_PIDController;
  rev::SparkMaxRelativeEncoder m_Encoder;
};