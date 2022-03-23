#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/GenericHID.h>
#include "Constants.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/ShooterIntake.h"
#include "subsystems/Climber.h"

class ClimbCommand
    : public frc2::CommandHelper<frc2::CommandBase, ClimbCommand> {
 public:
  explicit ClimbCommand(Climber* climber, ShooterIntake* shooterIntake, Drivetrain* drivetrain, frc::GenericHID& controller);

  void Initialize();
  void Execute();
  void End(bool interrupted);
  bool IsFinished();

 private:
  Climber* m_climber;
  Drivetrain* m_drivetrain;
  ShooterIntake* m_shooterIntake;
  frc::GenericHID& m_controller;
};