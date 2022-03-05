#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/GenericHID.h>
#include "Constants.h"

#include "subsystems/Drivetrain.h"

class CommandUserDrive
    : public frc2::CommandHelper<frc2::CommandBase, CommandUserDrive> {
 public:
  explicit CommandUserDrive(Drivetrain* drivetrain, frc::GenericHID& controller);
  void Execute();

 private:
  Drivetrain* m_drivetrain;
  frc::GenericHID& m_controller;
};