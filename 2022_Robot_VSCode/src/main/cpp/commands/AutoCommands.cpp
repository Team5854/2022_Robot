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
        autoTurn(drivetrain, 110),
        frc2::ParallelCommandGroup{autoDrive(drivetrain, 35.5), AutoIntakeCommand(shooterIntake)},
        autoDrive(drivetrain, -30),
        autoTurn(drivetrain, -165),
        autoDrive(drivetrain, 45),
        AutoShootCommand(shooterIntake)
    );
}

OneBallAutoLeft::OneBallAutoLeft(Drivetrain* drivetrain, ShooterIntake* shooterIntake){
    AddCommands(
        AutoShootCommand(shooterIntake),
        autoDrive(drivetrain, -100)
    );
}