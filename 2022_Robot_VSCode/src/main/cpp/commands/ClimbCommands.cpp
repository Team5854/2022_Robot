# include "commands/ClimbCommands.h"

ClimbCommand::ClimbCommand(Climber* climber, Drivetrain* drivetrain, ShooterIntake* shooterIntake, frc::GenericHID& controller):
    m_climber{climber}, m_drivetrain{drivetrain}, m_shooterIntake{shooterIntake}, m_controller{controller} {
        AddRequirements({climber, drivetrain, shooterIntake});
    }

void ClimbCommand::Initialize(){
    m_shooterIntake->setIntake(true);
}

void ClimbCommand::Execute(){
    m_climber->climb(-1*climbSpeed*m_controller.GetRawAxis(climbAxis));
    m_climber->rotate(rotateSpeed*m_controller.GetRawAxis(rotateAxis));

    if(m_controller.GetPOV() == 0){
        m_drivetrain->Set(-climbDriveSpeed,0);
    }
    else if(m_controller.GetPOV() == 90){
        m_drivetrain->Set(0,climbRotateSpeed);
    }
    else if(m_controller.GetPOV() == 180){
        m_drivetrain->Set(climbDriveSpeed,0);
    }
    else if(m_controller.GetPOV() == 270){
        m_drivetrain->Set(0,-climbRotateSpeed);
    }
    else{
        m_drivetrain->Set(0,0);
    }
}

void ClimbCommand::End(bool interrupted){
    m_drivetrain->Set(0,0);
    m_climber->climb(0);
    m_climber->rotate(0);

    m_shooterIntake->setIntake(false);
}

bool ClimbCommand::IsFinished(){
    if(m_controller.GetRawButton(climbFinishedButton)) return true;
    else return false;
}