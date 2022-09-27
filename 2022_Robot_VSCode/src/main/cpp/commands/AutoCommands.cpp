#include "commands/AutoCommands.h"
#include "Robot.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "commands/ShooterIntakeCommands.h"
#include "commands/DrivetrainCommands.h"


TwoBallAutoLeft::TwoBallAutoLeft(Drivetrain* drivetrain, ShooterIntake* shooterIntake){
    AddCommands(
        AutoShootCommand(shooterIntake),
        autoDrive(drivetrain, -40),
        autoTurn(drivetrain, 140),
        frc2::ParallelCommandGroup{autoDrive(drivetrain, 58.5), AutoIntakeCommand(shooterIntake)},
        autoDrive(drivetrain, -58),
        autoTurn(drivetrain, -190),
        autoDrive(drivetrain, 35),
        AutoShootCommand(shooterIntake)
    );
}

OneBallAutoLeft::OneBallAutoLeft(Drivetrain* drivetrain, ShooterIntake* shooterIntake){
    AddCommands(
        AutoShootCommand(shooterIntake),
        autoDrive(drivetrain, -100)
    );
}