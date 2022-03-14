#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/GenericHID.h>
#include "Constants.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/ShooterIntake.h"


class AutoCommand
    : public frc2::CommandHelper<frc2::CommandBase, AutoCommand> {
 public:
    explicit AutoCommand(Drivetrain* drivetrain, ShooterIntake* shooterIntake,frc::GenericHID& controller);

    //void Initialize();
    void Execute();
    void End(bool interrupted);
    bool IsFinished();
    
private:
  ShooterIntake* m_shooterIntake;     
  Drivetrain* m_drivetrain;
  frc::GenericHID& m_controller;
};