// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "Constants.h"
#include "commands/DrivetrainCommands.h"
#include "commands/ShooterIntakeCommands.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <iostream>

void Robot::RobotInit() {
  std::cout << "starting" << std::endl;
  frc::CameraServer::StartAutomaticCapture();
  theSideCar.initComms();
  m_chooser.SetDefaultOption("One Ball Auto Left", &m_oneAuto);
  m_chooser.AddOption("Two Ball Left", &m_autoCommand);
  frc::SmartDashboard::PutData(&m_chooser);
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
    if(m_shooterIntake.shooterOnly.GetBoolean(false)) theSideCar.sendState('q');
    else theSideCar.sendState('Q');
    if(m_shooterIntake.disableShoot.GetBoolean(false)) theSideCar.sendState('g');
    else theSideCar.sendState('G');
  }
  else theSideCar.sendState('F');
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
  frc::SmartDashboard::PutData(&m_chooser);
  m_drivetrain.brakeSet(true);
  m_chooser.GetSelected()->Schedule();
} 

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  m_drivetrain.brakeSet(false);
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
    }
    else{
      intakeButtonTrigger = new frc2::JoystickButton{&m_driverPad1, intakeButton};
      intakeButtonTrigger->WhenPressed(&m_intakeCommandIndex,false);
    }
  }
  if(!frc2::CommandScheduler::GetInstance().IsScheduled(&m_climbCommand)
    &&!frc2::CommandScheduler::GetInstance().IsScheduled(&m_commandUserDrive)) m_commandUserDrive.Schedule();
}

void Robot::TeleopExit() {}

void Robot::TestInit() {}

void Robot::TestPeriodic(){
  std::cout << m_drivetrain.GetLeftEncoders() << std::endl;
}


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif