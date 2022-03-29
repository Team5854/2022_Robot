// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <iostream>

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain(int leftLead, int leftFollow, int rightLead, int rightFollow);
  void Set(double forward, double rotation);// Sets the speed of the motor groups based off of forward and rotational values
  void DiffSet(double leftSpeed, double rightSpeed); // Sets the left and right group motor speeds to the values passed
  static double PercentRange(double in);// Constrains the input to a range of -1 to 1 to prevent errors in motor speed
  static double NonLinear(double in);
  double GetLeftEncoders();
  double GetRightEncoders();

 private:
  TalonFX m_leftLead;
  TalonFX m_leftFollow;
  TalonFX m_rightLead;
  TalonFX m_rightFollow;
};