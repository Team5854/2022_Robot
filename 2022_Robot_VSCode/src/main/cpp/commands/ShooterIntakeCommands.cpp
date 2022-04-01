#include "commands/ShooterIntakeCommands.h"
#include <frc/shuffleboard/Shuffleboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include "Constants.h"

IntakeCommand::IntakeCommand(ShooterIntake* shooterIntake, frc::GenericHID& controller):
    m_shooterIntake{shooterIntake}, m_controller{controller} {
        AddRequirements(shooterIntake);
}

void IntakeCommand::Initialize(){
    engaged = false;
}

void IntakeCommand::Execute(){
    if(!m_shooterIntake->m_balls[1]&&m_shooterIntake->getBreakBeam2()) m_shooterIntake->m_balls[1] = true;
    if(m_shooterIntake->m_balls[1]&&!m_shooterIntake->m_balls[0]&&m_shooterIntake->getBreakBeam1()) m_shooterIntake->m_balls[0] = true;
    if(m_controller.GetRawButtonPressed(intakeButton)) engaged = !engaged;
    if(engaged){
        m_shooterIntake->setIntake(true);
        timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(intakeTimeout);
    }
    else{
        m_shooterIntake->setIntake(false);
    }
    if(!m_shooterIntake->getBreakBeam2()&&!m_shooterIntake->m_balls[1]){
        m_shooterIntake->stage2Run(intakeBeltSpeed);
        m_shooterIntake->stage1Run(intakeBeltSpeed);
        m_shooterIntake->setLeds(0);
    }
    else if(!m_shooterIntake->getBreakBeam1()&&!m_shooterIntake->m_balls[0]){
        m_shooterIntake->stage2Run(0);
        m_shooterIntake->stage1Run(intakeBeltSpeed);
        m_shooterIntake->setLeds(1);
    }
    else{
        m_shooterIntake->stage2Run(0);
        m_shooterIntake->stage1Run(0);
        m_shooterIntake->setLeds(2);
    }
}

void IntakeCommand::End(bool interrupted){
    m_shooterIntake->setIntake(false);
    m_shooterIntake->stage1Run(0);
    m_shooterIntake->stage2Run(0);
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
    m_shooterIntake->m_balls[0] = false;
    m_shooterIntake->m_balls[1] = false;
    m_shooterIntake->setPid(shooter_kF, shooter_kP, shooter_kI, shooter_kD);
    m_shooterIntake->setLeds(-1);
}

void ShootCommand::Execute(){
    if(m_controller.GetRawButton(shootButton)){
        if(pidEnabled){
            m_shooterIntake->setMotorPoint(shootSpeed);
        }
        else{
            m_shooterIntake->shootRun(shootSpeed);
        }
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
        m_shooterIntake->setMotorPoint(0);
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
    m_shooterIntake->shootRun(0);
}

bool ShootCommand::IsFinished(){
    if(std::chrono::steady_clock::now() > timeout) return true; 
    else return false;
}

IntakeCommandDefault::IntakeCommandDefault(ShooterIntake* shooterIntake, frc::GenericHID& controller):
    m_shooterIntake{shooterIntake}, m_controller{controller} {
        AddRequirements(shooterIntake);
}

void IntakeCommandDefault::Initialize(){
    engaged = false;
}

void IntakeCommandDefault::Execute(){
    if(m_controller.GetRawButtonPressed(intakeButton)) engaged = !engaged;
    if(engaged){
        m_shooterIntake->setIntake(true);
        timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(intakeTimeout);
    }
    else{
        m_shooterIntake->setIntake(false);
    }
    m_shooterIntake->stage1Run(intakeBeltSpeed);
}

void IntakeCommandDefault::End(bool interrupted){
    m_shooterIntake->setIntake(false);
    m_shooterIntake->stage1Run(0);
}

bool IntakeCommandDefault::IsFinished(){
    if(std::chrono::steady_clock::now() > timeout) return true;
    return false;
}