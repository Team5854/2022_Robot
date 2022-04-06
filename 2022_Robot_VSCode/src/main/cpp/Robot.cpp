// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "Constants.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <iostream>

void Robot::RobotInit() {
  std::cout << "starting" << std::endl;
  frc::CameraServer::StartAutomaticCapture();
  theSideCar.initComms();
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
  if(!m_climber.climbFinished){
    if(!frc2::CommandScheduler::GetInstance().IsScheduled(&m_climbCommand)
      &&!frc2::CommandScheduler::GetInstance().IsScheduled(&m_intakeCommandIndex)
      &&!frc2::CommandScheduler::GetInstance().IsScheduled(&m_shootCommand))
      {
      if(m_driverPad1.GetRawButton(boostButton)) theSideCar.sendState('b');
      else{
        if(m_shooterIntake.m_balls[0]&&m_shooterIntake.m_balls[1]) m_shooterIntake.setLeds(2);
        else if (!m_shooterIntake.m_balls[0]&&m_shooterIntake.m_balls[1]) theSideCar.sendState('o');
        else theSideCar.sendState('N');
      }
    }
  }
  else theSideCar.sendState('F');
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
  /*autodrive = std::chrono::steady_clock::now() + std::chrono::milliseconds(k_shootStartTime + 4000);
  m_shooterIntake.setPid(shooter_kF, shooter_kP, shooter_kI, shooter_kD);*/
  m_autoIntake.Schedule();
} 

void Robot::AutonomousPeriodic() {
  if(!frc2::CommandScheduler::GetInstance().IsScheduled(&m_autoIntake)) m_autoShoot.Schedule();
  /*double motorSpeed = m_shooterIntake.setPoint.GetDouble(k_shootSpeed);
  if(m_shooterIntake.highLow.GetBoolean(false)) motorSpeed = m_shooterIntake.setPointHigh.GetDouble(k_shootSpeed);
  else motorSpeed = m_shooterIntake.setPoint.GetDouble(k_shootSpeed);
  if((autodrive - std::chrono::milliseconds(4000)) > std::chrono::steady_clock::now()){
    m_shooterIntake.setMotorPoint(motorSpeed);
  }
  else if((autodrive - std::chrono::milliseconds(2000)) > std::chrono::steady_clock::now()){
    m_shooterIntake.stage1Run(shootBeltSpeed);
    m_shooterIntake.stage2Run(shootBeltSpeed);
  }
  else if(autodrive > std::chrono::steady_clock::now()){
    m_drivetrain.Set(-.2,0);
    m_shooterIntake.shootRun(0);
    m_shooterIntake.stage1Run(0);
    m_shooterIntake.stage2Run(0);
  }
  else m_drivetrain.Set(0,0);*/
}

void Robot::TeleopInit() {
  m_commandUserDrive.Schedule();
  shootButtonTrigger.WhenPressed(&m_shootCommand,false);
  intakeButtonTrigger = new frc2::JoystickButton{&m_driverPad1, intakeButton};
  intakeButtonTrigger->WhenPressed(&m_intakeCommandIndex);
  if(m_shooterIntake.defaultSensors.GetBoolean(false) != lastDefault){
    lastDefault = m_shooterIntake.defaultSensors.GetBoolean(false);
    delete intakeButtonTrigger;
    if(m_shooterIntake.defaultSensors.GetBoolean(false)){
      intakeButtonTrigger = new frc2::JoystickButton{&m_driverPad1, intakeButton};
      intakeButtonTrigger->WhenPressed(&m_intakeCommand,false);
    }
    else{
      intakeButtonTrigger = new frc2::JoystickButton{&m_driverPad1, intakeButton};
      intakeButtonTrigger->WhenPressed(&m_intakeCommandIndex,false);
    }
  }
  climberButtonTrigger.ToggleWhenPressed(&m_climbCommand);
  std::cout << "Telopinit" << std::endl;
}

void Robot::TeleopPeriodic() {
  if(m_shooterIntake.defaultSensors.GetBoolean(false) != lastDefault){
    lastDefault = m_shooterIntake.defaultSensors.GetBoolean(false);
    delete intakeButtonTrigger;
    if(m_shooterIntake.defaultSensors.GetBoolean(false)){
      intakeButtonTrigger = new frc2::JoystickButton{&m_driverPad1, intakeButton};
      intakeButtonTrigger->WhenPressed(&m_intakeCommand,false);
      std::cout << "Changed to default" << std::endl;
    }
    else{
      intakeButtonTrigger = new frc2::JoystickButton{&m_driverPad1, intakeButton};
      intakeButtonTrigger->WhenPressed(&m_intakeCommandIndex,false);
      std::cout << "Changed to index" << std::endl;
    }
    std::cout << "Change made                                                              a;lskdjf;lkasjdf;lkasjdf;lkajsdf;;lkj" << std::endl;
  }
  if(!frc2::CommandScheduler::GetInstance().IsScheduled(&m_climbCommand)
    &&!frc2::CommandScheduler::GetInstance().IsScheduled(&m_commandUserDrive)) m_commandUserDrive.Schedule();
}

void Robot::TeleopExit() {}

void Robot::TestInit() {
}

void Robot::TestPeriodic(){}


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif