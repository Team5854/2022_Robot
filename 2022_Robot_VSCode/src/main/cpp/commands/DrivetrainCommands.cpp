// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DrivetrainCommands.h"
#include <iostream>

CommandUserDrive::CommandUserDrive(Drivetrain* drivetrain, frc::GenericHID& controller)
    : m_drivetrain{drivetrain}, m_controller{controller}{
      AddRequirements(drivetrain);
    }

void CommandUserDrive::Execute(){
  accelSpeed += (Drivetrain::NonLinear(m_controller.GetRawAxis(accelerationAxis)) - accelSpeed)*accelRamp/100;
  turnSpeed += (Drivetrain::NonLinear(m_controller.GetRawAxis(steeringAxis)) - turnSpeed)*turnRamp/100;

  if(m_controller.GetRawButton(brakeButton)){
    accelSpeed = 0;
    turnSpeed = 0;
  }

  if(m_controller.GetRawButton(boostButton)){
    m_drivetrain->Set(Drivetrain::PercentRange(boost*accelMod*accelSpeed), Drivetrain::PercentRange(turnMod*turnSpeed));
  }
  else{
    m_drivetrain->Set(Drivetrain::PercentRange(accelMod*accelSpeed), Drivetrain::PercentRange(turnMod*turnSpeed));
  }
}

void CommandUserDrive::End(bool interrupted){
  m_drivetrain->Set(0,0);
}