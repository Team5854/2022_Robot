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
  if(m_controller.GetRawButton(boostButton)) m_drivetrain->Set(Drivetrain::PercentRange(boost*accelMod*m_controller.GetRawAxis(accelerationAxis)),Drivetrain::PercentRange(turnMod*m_controller.GetRawAxis(steeringAxis)));
  else m_drivetrain->Set(accelMod*m_controller.GetRawAxis(accelerationAxis),turnMod*m_controller.GetRawAxis(steeringAxis));
}

void CommandUserDrive::End(bool interrupted){
  m_drivetrain->Set(0,0);
}