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


class ShooterIntake : public frc2::SubsystemBase {
 public:
  ShooterIntake(int shooterLead, int stage2, int stage1, frc::Compressor& compressor, int solenoid, int breakbeam1, int breakbeam2,std::initializer_list<bool> motorConfigs);
  void setIntake(bool upDown);
  void stage1Run(double speed);
  void stage2Run(double speed);
  void shootRun(double speed);
  bool getBreakBeam1();
  bool getBreakBeam2();
  void setPid(double kF, double kP, double kI, double kD);
  void setMotorPoint(double setPoint);
  void Periodic();

  bool m_balls[2] = {false,false};
  frc::ShuffleboardTab& shooterConfigTab = frc::Shuffleboard::GetTab("Shooter Configs");
  nt::NetworkTableEntry setPoint = shooterConfigTab.Add("Set Point", 0).GetEntry();
  
 private:
  rev::CANSparkMax m_shooterLead;
  //rev::CANSparkMax m_shooterFollow;
  //rev::SparkMaxPIDController m_PIDController;
  //rev::SparkMaxRelativeEncoder m_Encoder;
  TalonSRX m_stage2;
  TalonSRX m_stage1;
  frc::Compressor& m_compressor;
  frc::Solenoid m_solenoid;
  frc::DigitalInput m_breakBeam1;
  frc::DigitalInput m_breakBeam2;
};
