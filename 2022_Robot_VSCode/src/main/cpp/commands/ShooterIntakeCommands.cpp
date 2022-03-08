# include "commands/ShooterIntakeCommands.h"

IntakeCommand::IntakeCommand(ShooterIntake* shooterIntake, frc::GenericHID& controller):
    m_shooterIntake{shooterIntake}, m_controller{controller} {
        AddRequirements(shooterIntake);
}

void IntakeCommand::Execute(){
    if(m_controller.GetRawButton(intakeButton)){
        m_shooterIntake->setIntake(true);
        timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(intakeTimeout);
    }
    else{
        m_shooterIntake->setIntake(false);
    }
    if(!m_shooterIntake->getBreakBeam2()||!m_shooterIntake->m_balls[1]){
        m_shooterIntake->stage2Run(intakeBeltSpeed);
        m_shooterIntake->stage1Run(intakeBeltSpeed);
        m_shooterIntake->m_balls[1] = m_shooterIntake->getBreakBeam2();
    }
    else if(!m_shooterIntake->getBreakBeam1()||!m_shooterIntake->m_balls[0]){
        m_shooterIntake->stage2Run(0);
        m_shooterIntake->stage1Run(intakeBeltSpeed);
        m_shooterIntake->m_balls[0] = m_shooterIntake->getBreakBeam1();
    }
    else{
        m_shooterIntake->stage2Run(0);
        m_shooterIntake->stage1Run(0);
    }
}

void IntakeCommand::End(bool interrupted){
    m_shooterIntake->setIntake(false);
    m_shooterIntake->stage1Run(0);
    m_shooterIntake->stage2Run(0);
    std::cout << "Stopping" << std::endl;
}

bool IntakeCommand::IsFinished(){
    if(m_shooterIntake->m_balls[0]&&m_shooterIntake->m_balls[1]) return true;
    else if(std::chrono::steady_clock::now() > timeout) return true;
    return false;
}

ShootCommand::ShootCommand(ShooterIntake* shooterIntake, frc::GenericHID& controller):
    m_shooterIntake{shooterIntake}, m_controller{controller} {
        AddRequirements(shooterIntake);
}

void ShootCommand::Initialize(){
    startup = std::chrono::steady_clock::now() + std::chrono::milliseconds(shootStartTime);
}

void ShootCommand::Execute(){
    if(m_controller.GetRawButton(shootButton)){
        m_shooterIntake->shootRun(shootSpeed);
        timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(shootTimeout);
        if(std::chrono::steady_clock::now() > startup){
            m_shooterIntake->stage1Run(shootBeltSpeed);
            m_shooterIntake->stage2Run(shootBeltSpeed);
        }
        else{
            m_shooterIntake->stage1Run(0);
            m_shooterIntake->stage2Run(0);
        }
    }
    else{
        m_shooterIntake->shootRun(0);
        if(!m_shooterIntake->getBreakBeam2()){
            m_shooterIntake->stage2Run(intakeBeltSpeed);
            m_shooterIntake->stage1Run(intakeBeltSpeed);
        }
        else if(!m_shooterIntake->getBreakBeam1()){
            m_shooterIntake->m_balls[1] = true;
            m_shooterIntake->stage2Run(0);
            m_shooterIntake->stage1Run(intakeBeltSpeed);
        }
        else{
            m_shooterIntake->m_balls[1] = true;
            m_shooterIntake->m_balls[0] = true;
            m_shooterIntake->stage2Run(0);
            m_shooterIntake->stage1Run(0);
        }
    }
}

void ShootCommand::End(bool interrupted){
    m_shooterIntake->stage1Run(0);
    m_shooterIntake->stage2Run(0);
}

bool ShootCommand::IsFinished(){
    if(std::chrono::steady_clock::now() > timeout) return true; 
    else return false;
}