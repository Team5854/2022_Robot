#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <iostream>

class Climber : public frc2::SubsystemBase {
  public:
    Climber(int leadClimb, int followClimb, int rotate, std::initializer_list<bool> motorConfigs);
    void rotate(double rate);
    void climb(double rate);
    int getClimbLimit();
    int getRotateLimit();
  
  private:
    TalonSRX m_leadClimb;
    TalonSRX m_followClimb;
    TalonSRX m_rotate;
};