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
    startup = std::chrono::steady_clock::now() + std::chrono::milliseconds(int(m_shooterIntake->shooterStartTime.GetDouble(k_shootStartTime)));
    m_shooterIntake->m_balls[0] = false;
    m_shooterIntake->m_balls[1] = false;
    m_shooterIntake->setPid(shooter_kF, shooter_kP, shooter_kI, shooter_kD);
    m_shooterIntake->setLeds(-1);
    trigger = 0;
}

void ShootCommand::Execute(){
    if(!m_shooterIntake->getBreakBeam2() && trigger == 0){
        trigger = 1;
        shootDelay = std::chrono::steady_clock::now() + std::chrono::milliseconds(int(m_shooterIntake->shooterStartTime.GetDouble(k_shotDelay)));
    }
    if(m_shooterIntake->getBreakBeam2() && trigger == 1){
         trigger = 2;
    }
    if(m_controller.GetRawButton(shootButton)){
        if(pidEnabled){
            if(!m_shooterIntake->highLow.GetBoolean(false)){
                m_shooterIntake->setMotorPoint(m_shooterIntake->setPoint.GetDouble(k_shootSpeed));
            }
            else{
                m_shooterIntake->setMotorPoint(m_shooterIntake->setPointHigh.GetDouble(k_shootSpeedHigh));
            }
        }
        else{
            m_shooterIntake->shootRun(k_shootNoPid);
        }
        timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(shootTimeout);
        if(std::chrono::steady_clock::now() > startup){
            if(m_shooterIntake->highLow.GetBoolean(false)){
                if(trigger == 0 || trigger == 1){
                    m_shooterIntake->stage1Run(shootBeltSpeed);
                    m_shooterIntake->stage2Run(shootBeltSpeed);
                }
                else if(trigger == 2 && shootDelay > std::chrono::steady_clock::now()){
                    m_shooterIntake->stage1Run(0);
                    m_shooterIntake->stage2Run(0);
                }
                else if(shootDelay < std::chrono::steady_clock::now()){
                    m_shooterIntake->stage1Run(shootBeltSpeed);
                    m_shooterIntake->stage2Run(shootBeltSpeed);
                }
                else{
                    m_shooterIntake->stage1Run(0);
                    m_shooterIntake->stage2Run(0);
                }
            }
            else{
                m_shooterIntake->stage1Run(shootBeltSpeed);
                m_shooterIntake->stage2Run(shootBeltSpeed);
            }
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

AutoShootCommand::AutoShootCommand(ShooterIntake* shooterIntake):
    m_shooterIntake{shooterIntake}{}

void AutoShootCommand::Initialize(){
    startup = std::chrono::steady_clock::now() + std::chrono::milliseconds(int(m_shooterIntake->shooterStartTime.GetDouble(k_shootStartTime)));
    m_shooterIntake->m_balls[0] = false;
    m_shooterIntake->m_balls[1] = false;
    m_shooterIntake->setPid(shooter_kF, shooter_kP, shooter_kI, shooter_kD);
    m_shooterIntake->setLeds(-1);
}

void AutoShootCommand::Execute(){
    if(!m_shooterIntake->highLow.GetBoolean(false)){
        m_shooterIntake->setMotorPoint(m_shooterIntake->setPoint.GetDouble(k_shootSpeed));
    }
    else{
        m_shooterIntake->setMotorPoint(m_shooterIntake->setPointHigh.GetDouble(k_shootSpeedHigh));
    }
    if(startup < std::chrono::steady_clock::now()){
        m_shooterIntake->stage2Run(shootBeltSpeed);
        m_shooterIntake->stage1Run(shootBeltSpeed);
    }
}

void AutoShootCommand::End(bool interrupted){
    m_shooterIntake->stage2Run(0);
    m_shooterIntake->stage1Run(0);
    m_shooterIntake->setMotorPoint(0);
}

bool AutoShootCommand::IsFinished(){
    if((startup + std::chrono::milliseconds(autoShootTime)) < std::chrono::steady_clock::now()) return true;
    else return false;
}

AutoIntakeCommand::AutoIntakeCommand(ShooterIntake* shooterIntake):
    m_shooterIntake{shooterIntake}{}

void AutoIntakeCommand::Initialize(){
    engaged = true;
    endTime =  std::chrono::steady_clock::now() + std::chrono::milliseconds(autoIntakeTimeout);
}

void AutoIntakeCommand::Execute(){
    if(!m_shooterIntake->m_balls[1]&&m_shooterIntake->getBreakBeam2()) m_shooterIntake->m_balls[1] = true;
    if(m_shooterIntake->m_balls[1]&&!m_shooterIntake->m_balls[0]&&m_shooterIntake->getBreakBeam1()) m_shooterIntake->m_balls[0] = true;
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

void AutoIntakeCommand::End(bool interrupted){
    m_shooterIntake->setIntake(false);
    m_shooterIntake->stage1Run(0);
    m_shooterIntake->stage2Run(0);
}

bool AutoIntakeCommand::IsFinished(){
    if(m_shooterIntake->m_balls[0]&&m_shooterIntake->m_balls[1]) return true;
    else if(std::chrono::steady_clock::now() > timeout) return true;
    if(std::chrono::steady_clock::now() > endTime) return true;
    return false;
}