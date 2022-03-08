#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/GenericHID.h>
#include <chrono>
#include <sys/time.h>

#include "Constants.h"
#include "subsystems/ShooterIntake.h"

class IntakeCommand : public frc2::CommandHelper<frc2::CommandBase, IntakeCommand> {
 public:
  explicit IntakeCommand(ShooterIntake* shooterIntake, frc::GenericHID& controller);

  void Execute();
  void End(bool interrupted);
  bool IsFinished();

 private:
  ShooterIntake* m_shooterIntake;
  frc::GenericHID& m_controller;
  std::chrono::time_point<std::chrono::steady_clock> timeout;
};

class ShootCommand : public frc2::CommandHelper<frc2::CommandBase, ShootCommand> {
 public:
  explicit ShootCommand(ShooterIntake* shooterIntake, frc::GenericHID& controller);
  void Initialize();
  void Execute();
  void End(bool interrupted);
  bool IsFinished();

 private:
  ShooterIntake* m_shooterIntake;
  frc::GenericHID& m_controller;
  std::chrono::time_point<std::chrono::steady_clock> timeout;
  std::chrono::time_point<std::chrono::steady_clock> startup;
};