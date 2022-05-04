#include "commands/AutoCommands.h"
#include "Robot.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "commands/ShooterIntakeCommands.h"
#include "commands/DrivetrainCommands.h"


TwoBallAutoLeft::TwoBallAutoLeft(Drivetrain* drivetrain, ShooterIntake* shooterIntake){
    AddCommands(
        AutoShootCommand(shooterIntake),
        autoDrive(drivetrain, -49),
        autoTurn(drivetrain, 125),
        frc2::ParallelCommandGroup{autoDrive(drivetrain, 22.5), AutoIntakeCommand(shooterIntake)},
        autoDrive(drivetrain, -18),
        autoTurn(drivetrain, -200),
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