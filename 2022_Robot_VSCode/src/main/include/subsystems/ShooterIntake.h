#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <iostream>
#include <rev/CANSparkMax.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <ctime>

class ShooterIntake : public frc2::SubsystemBase {
 public:
  ShooterIntake(int shooter, int stage2, int stage1, frc::Compressor& compressor, int solenoid, int breakbeam1, int breakbeam2,std::initializer_list<bool> motorConfigs);
  void setIntake(bool upDown);
  void stage1Run(double speed);
  void stage2Run(double speed);
  void shootRun(double speed);
  bool getBreakBeam1();
  bool getBreakBeam2();
  bool m_balls[2] = {false,false};
  
 private:
  rev::CANSparkMax m_shooter;
  TalonSRX m_stage2;
  TalonSRX m_stage1;
  frc::Compressor& m_compressor;
  frc::Solenoid m_solenoid;
  frc::DigitalInput m_breakBeam1;
  frc::DigitalInput m_breakBeam2;
};
