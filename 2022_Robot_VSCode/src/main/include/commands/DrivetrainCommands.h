#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/GenericHID.h>
#include <chrono>
#include "Constants.h"

#include "subsystems/Drivetrain.h"

class CommandUserDrive
    : public frc2::CommandHelper<frc2::CommandBase, CommandUserDrive> {
 public:
  explicit CommandUserDrive(Drivetrain* drivetrain, frc::GenericHID& controller);
  void Execute();
  void End(bool interrupted);

 private:
  Drivetrain* m_drivetrain;
  frc::GenericHID& m_controller;
  double accelSpeed = 0;
  double turnSpeed = 0;
};

class autoDrive
    : public frc2::CommandHelper<frc2::CommandBase, autoDrive> {
 public:
  explicit autoDrive(Drivetrain* drivetrain, double distance);
  autoDrive (autoDrive&&) = default;	
  void Initialize();
  void Execute();
  bool IsFinished();
  void End(bool interrupted);
  double getVelocity(double distance, double point);

 private:
  Drivetrain* m_drivetrain;
  double leftStart;
  double rightStart;
  double leftEnd;
  double rightEnd;
  double m_distance;
};

class autoTurn
    : public frc2::CommandHelper<frc2::CommandBase, autoTurn> {
 public:
  explicit autoTurn(Drivetrain* drivetrain, double angle);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End(bool interrupted);
  double getVelocity(double distance, double point);

 private:
  Drivetrain* m_drivetrain;
  double leftStart;
  double rightStart;
  double leftEnd;
  double rightEnd;
  double m_angle;
};