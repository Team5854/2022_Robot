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
  if (m_driverPad1.GetRawButtonPressed(climbFinishedButton)) climbComplete = !climbComplete;
  if(!climbComplete){
    if(frc2::CommandScheduler::GetInstance().IsScheduled(&m_climbCommand)){
      if(m_climber.getRotateLimit() == 1) theSideCar.serialPortObj->Write("l"); //Limit switch
      else theSideCar.serialPortObj->Write("c"); // Climbing lights
    }
    else if(frc2::CommandScheduler::GetInstance().IsScheduled(&m_intakeCommandIndex)){
      if(m_shooterIntake.m_balls[0]&&m_shooterIntake.m_balls[1]) theSideCar.serialPortObj->Write("n");
      else if (!m_shooterIntake.m_balls[0]&&m_shooterIntake.m_balls[1]) theSideCar.serialPortObj->Write("I");
      else theSideCar.serialPortObj->Write("i");
    }
    else if(frc2::CommandScheduler::GetInstance().IsScheduled(&m_shootCommand)) theSideCar.serialPortObj->Write("s");
    else if(m_driverPad1.GetRawButton(boostButton)) theSideCar.serialPortObj->Write("b");
    else{
      if(m_shooterIntake.m_balls[0]&&m_shooterIntake.m_balls[1]) theSideCar.serialPortObj->Write("n");
      else if (!m_shooterIntake.m_balls[0]&&m_shooterIntake.m_balls[1]) theSideCar.serialPortObj->Write("o");
      else theSideCar.serialPortObj->Write("N");
    }
  }
  else theSideCar.serialPortObj->Write("F");
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
  autodrive = std::chrono::steady_clock::now() + std::chrono::milliseconds(shootStartTime +6000);
} 

void Robot::AutonomousPeriodic() {
  if((autodrive - std::chrono::milliseconds(6000)) > std::chrono::steady_clock::now()){
    m_shooterIntake.shootRun(shootSpeed);
  }
  else if((autodrive - std::chrono::milliseconds(4000)) > std::chrono::steady_clock::now()){
    m_shooterIntake.stage1Run(intakeBeltSpeed);
    m_shooterIntake.stage2Run(shootBeltSpeed);
  }
  if(autodrive > std::chrono::steady_clock::now() && autodrive-std::chrono::milliseconds(shootStartTime+2000) < std::chrono::steady_clock::now()){
    m_drivetrain.Set(-.2,0);
    m_shooterIntake.shootRun(0);
    m_shooterIntake.stage1Run(0);
    m_shooterIntake.stage2Run(0);
  }
  else m_drivetrain.Set(0,0);
}

void Robot::TeleopInit() {
  m_commandUserDrive.Schedule();
  shootButtonTrigger.WhenPressed(&m_shootCommand,false);
  if(sensorDefault)intakeButtonTrigger.WhenPressed(&m_intakeCommand,false);
  else intakeButtonTrigger.WhenPressed(&m_intakeCommandIndex,false);
  climberButtonTrigger.ToggleWhenPressed(&m_climbCommand);
  std::cout << "Telopinit" << std::endl;
}

void Robot::TeleopPeriodic() {
  if(!frc2::CommandScheduler::GetInstance().IsScheduled(&m_commandUserDrive)&&!frc2::CommandScheduler::GetInstance().IsScheduled(&m_climbCommand)){
    m_commandUserDrive.Schedule();
  }
  if(m_driverPad1.GetRawButtonPressed(defaultSensorButton)) sensorDefault = !sensorDefault;
  if(sensorDefault)intakeButtonTrigger.WhenPressed(&m_intakeCommand,false);
  else intakeButtonTrigger.WhenPressed(&m_intakeCommandIndex,false);
  frc::SmartDashboard::PutBoolean("Break beam sensors defaulted",sensorDefault);
}

void Robot::TeleopExit() {}

void Robot::TestInit() {}
  
void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif