# include "commands/AutoCommands.h"
#include "Robot.h"

// #include "commands/ShooterIntakeCommands.cpp"

AutoCommand::AutoCommand(Drivetrain* drivetrain, ShooterIntake* shooterIntake,frc::GenericHID& controller):
    m_shooterIntake{shooterIntake}, m_controller{controller}, m_drivetrain{drivetrain}{

    AddRequirements(shooterIntake);
    AddRequirements(drivetrain);
}

void AutoCommand::Initialize(){
    LeftInitial = m_drivetrain->GetLeftEncoders();
    RightInitial = m_drivetrain->GetRightEncoders();
    startup = std::chrono::steady_clock::now() + std::chrono::milliseconds(k_shootStartTime);
    m_shooterIntake->m_balls[0] = false;
    m_shooterIntake->m_balls[1] = false;

}
void AutoCommand::Execute(){
    m_shooterIntake->shootRun(k_shootSpeed);
    timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(shootTimeout);
    if(std::chrono::steady_clock::now() > startup){
        m_shooterIntake->stage1Run(shootBeltSpeed);
        m_shooterIntake->stage2Run(shootBeltSpeed);
    }
    else{
        m_shooterIntake->stage1Run(0);
        m_shooterIntake->stage2Run(0);
    }
    if(std::chrono::steady_clock::now() > startup + std::chrono::milliseconds(500)) firstBall = true;

    if(firstBall){
        if(m_drivetrain->GetLeftEncoders() < LeftInitial+initialMovement){
            m_drivetrain->Set(0.2,0);
            if(!m_shooterIntake->getBreakBeam1()){
                m_shooterIntake->stage1Run(1);
            }
            m_shooterIntake->setIntake(true);
        }
    }
}