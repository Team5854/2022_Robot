# include "commands/AutoCommand.h"
#include "Robot.h"

// #include "commands/ShooterIntakeCommands.cpp"

AutoCommand::AutoCommand(Drivetrain* drivetrain, ShooterIntake* shooterIntake,frc::GenericHID& controller):
    m_shooterIntake{shooterIntake}, m_controller{controller}, m_drivetrain{drivetrain}{

    AddRequirements(shooterIntake);
    AddRequirements(drivetrain);
}

void AutoCommand::Initialize(){
    movementDistance = std::chrono::steady_clock::now() + std::chrono::milliseconds(initialMovement);

}

void AutoCommand::Execute(double speed){
    while(std::chrono::steady_clock::now() < movementDistance){
    m_drivetrain->Set(speed,speed);
    }
    if (movementDistance == std::chrono::steady_clock::now())
    {
    movementBack = std::chrono::steady_clock::now() + std::chrono::milliseconds(initialMovement);
    }
    
    


}

void AutoCommand::End(bool interrupted){
    
}

bool AutoCommand::IsFinished(){

}
